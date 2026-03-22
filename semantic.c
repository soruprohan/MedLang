/* semantic.c — MedLang Semantic Analysis
   Phase 3: Semantic Analysis

   Checks implemented:
     1. Undeclared variable use
     2. Double declaration in same scope
     3. Sealed (immutable) reassignment
     4. Type mismatch / strong typing
     5. NoSample access without null-check guard
     6. Missing Discharge (return) path in non-void functions
     7. Range-loop direction warning (e.g. Cycle <: i in 10..1 :>)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "ast.h"
#include "symtable.h"
#include "semantic.h"
#include "medlang.tab.h"   /* token codes: PLUS, GT, EQ, … */

/* ============================================================
   Global counters
   ============================================================ */
int sem_error_count = 0;
int sem_warn_count  = 0;

/* ============================================================
   Internal helpers: emit error / warning
   ============================================================ */
static void sem_error(int line, const char *fmt, ...) {
    va_list ap;
    fprintf(stderr, "[Semantic Error] Line %d: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    sem_error_count++;
}

static void sem_warn(int line, const char *fmt, ...) {
    va_list ap;
    fprintf(stderr, "[Semantic Warning] Line %d: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    sem_warn_count++;
}

/* ============================================================
   Type compatibility table
   (implements Strong Static Typing / No Implicit Conversion)

   Returns 1 if rhs_type can be assigned to a variable of lhs_type.
   Returns 0 if the assignment is a type error.

   Widening rules (safe promotions only):
     Organ   <- Organ
     Flow    <- Flow | Organ          (int widens to float)
     Diabetes<- Diabetes | Flow | Organ (all numeric widen to double)
     Cell    <- Cell
     MajorOrgan <- MajorOrgan | Organ (int widens to long)
     MinorOrgan <- MinorOrgan
     NonPathologic <- NonPathologic
     NullTissue <- NullTissue (void, only for return type checking)
   ============================================================ */
static int types_compatible(const char *lhs, const char *rhs) {
    if (!lhs || !rhs) return 1;  /* unknown type: let it pass silently */
    if (strcmp(lhs, rhs) == 0) return 1;  /* exact match always OK */

    /* Widening promotions */
    if (strcmp(lhs, "Flow") == 0)
        return strcmp(rhs, "Organ") == 0;

    if (strcmp(lhs, "Diabetes") == 0)
        return strcmp(rhs, "Flow")  == 0
            || strcmp(rhs, "Organ") == 0;

    if (strcmp(lhs, "MajorOrgan") == 0)
        return strcmp(rhs, "Organ") == 0;

    return 0;  /* all other combinations are mismatches */
}

/* ============================================================
   Infer the result type of an expression node.
   Returns a static string — do NOT free it.
   Returns NULL if the type cannot be determined (e.g. error).
   ============================================================ */
static const char *infer_type(ASTNode *node, Scope *scope) {
    if (!node) return NULL;

    switch (node->type) {

    case NODE_INT_LIT:    return "Organ";
    case NODE_FLOAT_LIT:  return "Flow";
    case NODE_STRING_LIT: return "Cell";   /* treat as char array */

    case NODE_IDENT: {
        Symbol *sym = scope_lookup(scope, node->sval);
        if (!sym) return NULL;  /* undeclared — error already reported */
        return sym->type;
    }

    case NODE_BINOP: {
        const char *lt = infer_type(node->binop.left,  scope);
        const char *rt = infer_type(node->binop.right, scope);
        int op = node->binop.op;

        /* Relational / logical ops always produce an Organ (boolean-int) */
        if (op == EQ || op == NEQ || op == GT  || op == LT  ||
            op == GEQ || op == LEQ || op == AND || op == OR)
            return "Organ";

        /* Arithmetic: use widening rules */
        if (!lt || !rt) return NULL;
        if (strcmp(lt, "Diabetes") == 0 || strcmp(rt, "Diabetes") == 0)
            return "Diabetes";
        if (strcmp(lt, "Flow") == 0     || strcmp(rt, "Flow") == 0)
            return "Flow";
        if (strcmp(lt, "MajorOrgan") == 0 || strcmp(rt, "MajorOrgan") == 0)
            return "MajorOrgan";
        return "Organ";
    }

    case NODE_UNOP:
        return infer_type(node->binop.left, scope);  /* operand in .left */

    case NODE_FUNC_CALL: {
        /* Built-in math functions return Flow (double-ish) */
        const char *n = node->call.name;
        if (strcmp(n, "Power")     == 0 || strcmp(n, "RootCause") == 0 ||
            strcmp(n, "AbsDose")   == 0 || strcmp(n, "RoundDown") == 0 ||
            strcmp(n, "RoundUp")   == 0 || strcmp(n, "Sine")      == 0 ||
            strcmp(n, "Cosine")    == 0 || strcmp(n, "Tangent")   == 0)
            return "Flow";
        if (strcmp(n, "IsCritical") == 0)
            return "Organ";
        /* User-defined: look up in scope as a "function symbol"
           We store functions with their return type in the scope too. */
        Symbol *sym = scope_lookup(scope, n);
        if (sym) return sym->type;
        return NULL;
    }

    default:
        return NULL;
    }
}

/* ============================================================
   Forward declaration — analyze() is mutually recursive
   ============================================================ */
static void analyze(ASTNode *node, Scope *scope,
                    const char *enclosing_ret_type,
                    int *has_return);

/* ============================================================
   Check whether a statement list unconditionally returns.
   Used for return-path analysis.
   ============================================================ */
static int stmt_list_returns(ASTNode *list_node) {
    if (!list_node) return 0;

    /* Walk the singly-linked stmt list */
    ASTNode *cur = list_node;
    while (cur) {
        ASTNode *stmt = NULL;
        ASTNode *next = NULL;

        if (cur->type == NODE_STMT_LIST) {
            stmt = cur->list.head;
            next = cur->list.tail;
        } else {
            stmt = cur;
            next = NULL;
        }

        if (stmt) {
            switch (stmt->type) {
            case NODE_RETURN:
                return 1;   /* definite return here */

            case NODE_IF:
                /* Both branches must return */
                if (stmt->ifnode.else_block &&
                    stmt_list_returns(stmt->ifnode.then_block) &&
                    stmt_list_returns(stmt->ifnode.else_block))
                    return 1;
                break;

            case NODE_BLOCK:
                if (stmt_list_returns(stmt->list.head))
                    return 1;
                break;

            default:
                break;
            }
        }
        cur = next;
    }
    return 0;
}

/* ============================================================
   NoSample guard detection
   Returns 1 if the statement is a null-check guard for `name`:
       Diagnose <: name MisMatch NoSample :>
   We look for:
       NODE_IF whose condition is a NODE_BINOP(NEQ, NODE_IDENT(name), ...)
   This is a heuristic; a proper flow-sensitive analysis would need
   a dataflow pass — this is appropriate for a course project.
   ============================================================ */
static int is_nosample_guard(ASTNode *stmt, const char *name) {
    if (!stmt || stmt->type != NODE_IF) return 0;
    ASTNode *cond = stmt->ifnode.cond;
    if (!cond || cond->type != NODE_BINOP) return 0;
    if (cond->binop.op != NEQ && cond->binop.op != EQ) return 0;
    ASTNode *left  = cond->binop.left;
    ASTNode *right = cond->binop.right;
    /* Accept:  name MisMatch/Match NoSample  (ident on either side) */
    if (left  && left->type  == NODE_IDENT && strcmp(left->sval,  name) == 0)
        return 1;
    if (right && right->type == NODE_IDENT && strcmp(right->sval, name) == 0)
        return 1;
    return 0;
}

/* ============================================================
   Core recursive analysis walker
   ============================================================ */
static void analyze(ASTNode *node, Scope *scope,
                    const char *enclosing_ret_type,
                    int *has_return) {
    if (!node) return;

    switch (node->type) {

    /* ---- Program root / statement lists ---- */
    case NODE_PROGRAM:
        analyze(node->binop.left, scope, enclosing_ret_type, has_return);
        break;

    case NODE_STMT_LIST: {
        /* Walk the linked list.
           We also do a quick pre-scan for NoSample guards so that a
           nosample variable used INSIDE a guard body is not flagged. */
        ASTNode *cur = node;
        while (cur && cur->type == NODE_STMT_LIST) {
            analyze(cur->list.head, scope, enclosing_ret_type, has_return);
            cur = cur->list.tail;
        }
        if (cur) analyze(cur, scope, enclosing_ret_type, has_return);
        break;
    }

    /* ---- Variable declaration ---- */
    case NODE_DECL: {
        const char *vname = node->decl.name;
        const char *vtype = node->decl.datatype;
        int sealed    = node->decl.is_sealed;
        int nosample  = node->decl.is_nosample;

        /* Check for double declaration */
        if (scope_add(scope, vname, vtype, sealed, nosample,
                      node->lineno) == -1) {
            sem_error(node->lineno,
                      "'%s' already declared in this scope", vname);
        }

        /* Analyse initialiser expression */
        if (node->decl.init) {
            analyze(node->decl.init, scope, enclosing_ret_type, has_return);

            /* Type mismatch check */
            const char *rhs_type = infer_type(node->decl.init, scope);
            if (rhs_type && !types_compatible(vtype, rhs_type)) {
                sem_error(node->lineno,
                    "cannot assign %s value to %s variable '%s'",
                    rhs_type, vtype, vname);
            }

            /* Mark as initialised */
            scope_mark_init(scope, vname);
        }
        break;
    }

    /* ---- NoSample declaration (no initialiser by definition) ---- */
    case NODE_NOSAMPLE_DECL: {
        const char *vname = node->decl.name;
        const char *vtype = node->decl.datatype;
        if (scope_add(scope, vname, vtype, 0, 1, node->lineno) == -1) {
            sem_error(node->lineno,
                      "'%s' already declared in this scope", vname);
        }
        /* NoSample variables start uninitialised — that is the point */
        break;
    }

    /* ---- Assignment ---- */
    case NODE_ASSIGN: {
        const char *vname = node->assign.name;
        Symbol *sym = scope_lookup(scope, vname);

        /* Undeclared variable */
        if (!sym) {
            sem_error(node->lineno,
                      "'%s' used before declaration", vname);
            /* Still analyse the RHS to catch nested errors */
            analyze(node->assign.expr, scope, enclosing_ret_type, has_return);
            break;
        }

        /* Sealed reassignment */
        if (sym->is_sealed && sym->initialized) {
            sem_error(node->lineno,
                      "'%s' is Sealed and cannot be reassigned", vname);
        }

        /* Analyse RHS */
        analyze(node->assign.expr, scope, enclosing_ret_type, has_return);

        /* Type mismatch */
        const char *rhs_type = infer_type(node->assign.expr, scope);
        if (rhs_type && !types_compatible(sym->type, rhs_type)) {
            sem_error(node->lineno,
                "cannot assign %s value to %s variable '%s'",
                rhs_type, sym->type, vname);
        }

        scope_mark_init(scope, vname);
        break;
    }

    /* ---- Identifier reference ---- */
    case NODE_IDENT: {
        const char *vname = node->sval;
        Symbol *sym = scope_lookup(scope, vname);

        if (!sym) {
            sem_error(node->lineno,
                      "'%s' used before declaration", vname);
            break;
        }

        /* NoSample without null-check guard:
           We cannot easily check the surrounding context here without
           a proper dataflow pass, so we emit a warning pointing the
           programmer to add a guard. The check is conservative: we
           warn unless the variable is being used as the condition of
           a Diagnose (which is handled when we walk NODE_IF).        */
        if (sym->is_nosample && !sym->initialized) {
            sem_error(node->lineno,
                "'%s' is NoSample; check it for NoSample before use",
                vname);
        }
        break;
    }

    /* ---- If / Else (Diagnose / Alternate) ---- */
    case NODE_IF: {
        analyze(node->ifnode.cond, scope, enclosing_ret_type, has_return);

        /* If the condition is a NoSample guard, mark the variable
           as "safe to use" inside the then-block by temporarily
           clearing its nosample flag. */
        Symbol *guarded_sym = NULL;
        ASTNode *cond = node->ifnode.cond;
        if (cond && cond->type == NODE_BINOP &&
            (cond->binop.op == NEQ || cond->binop.op == EQ)) {
            ASTNode *lhs = cond->binop.left;
            if (lhs && lhs->type == NODE_IDENT) {
                Symbol *s = scope_lookup(scope, lhs->sval);
                if (s && s->is_nosample) {
                    guarded_sym = s;
                    s->initialized = 1;   /* temporarily safe */
                }
            }
        }

        /* New scope for then-block */
        int then_returns = 0;
        Scope *then_scope = scope_new(scope);
        analyze(node->ifnode.then_block, then_scope,
                enclosing_ret_type, &then_returns);
        scope_free(then_scope);

        /* Restore NoSample guard flag */
        if (guarded_sym) guarded_sym->initialized = 0;

        int else_returns = 0;
        if (node->ifnode.else_block) {
            Scope *else_scope = scope_new(scope);
            analyze(node->ifnode.else_block, else_scope,
                    enclosing_ret_type, &else_returns);
            scope_free(else_scope);
        }

        if (then_returns && else_returns && has_return)
            *has_return = 1;
        break;
    }

    /* ---- While loop (Continuous) ---- */
    case NODE_WHILE: {
        analyze(node->loop.cond, scope, enclosing_ret_type, has_return);
        Scope *loop_scope = scope_new(scope);
        int loop_ret = 0;
        analyze(node->loop.body, loop_scope, enclosing_ret_type, &loop_ret);
        scope_free(loop_scope);
        break;
    }

    /* ---- Do-while loop (LoadingDose) ---- */
    case NODE_DO_WHILE: {
        Scope *loop_scope = scope_new(scope);
        int loop_ret = 0;
        analyze(node->loop.body, loop_scope, enclosing_ret_type, &loop_ret);
        scope_free(loop_scope);
        analyze(node->loop.cond, scope, enclosing_ret_type, has_return);
        break;
    }

    /* ---- Classic for loop (Cycle 3-part) ---- */
    case NODE_FOR: {
        Scope *for_scope = scope_new(scope);
        int for_ret = 0;
        analyze(node->forloop.init,   for_scope, enclosing_ret_type, &for_ret);
        analyze(node->forloop.cond,   for_scope, enclosing_ret_type, &for_ret);
        analyze(node->forloop.update, for_scope, enclosing_ret_type, &for_ret);
        analyze(node->forloop.body,   for_scope, enclosing_ret_type, &for_ret);
        scope_free(for_scope);
        break;
    }

    /* ---- Range-based for (Cycle <: i in 1..10 :>) ---- */
    case NODE_FOR_RANGE: {
        int from = node->range_loop.from;
        int to   = node->range_loop.to;

        /* Range direction warning */
        if (from > to) {
            sem_warn(node->lineno,
                "range %d..%d goes backward with no step direction; "
                "loop may not execute", from, to);
        }

        /* Introduce the loop variable as Organ (int) in a new scope */
        Scope *range_scope = scope_new(scope);
        scope_add(range_scope, node->range_loop.var, "Organ",
                  0, 0, node->lineno);
        scope_mark_init(range_scope, node->range_loop.var);

        int range_ret = 0;
        analyze(node->range_loop.body, range_scope,
                enclosing_ret_type, &range_ret);
        scope_free(range_scope);
        break;
    }

    /* ---- Block [: ... :] ---- */
    case NODE_BLOCK: {
    Scope *block_scope = scope_new(scope);
    int block_ret = 0;
    analyze(node->binop.left, block_scope, enclosing_ret_type, &block_ret);
    if (block_ret && has_return) *has_return = 1;
    scope_free(block_scope);
    break;
    }
    /* ---- Function definition ---- */
    case NODE_FUNC_DEF: {
        const char *fname    = node->func.name;
        const char *ret_type = node->func.ret_type;

        /* Register the function itself in the current (outer) scope
           so it can be called recursively or from later code. */
        if (scope_add(scope, fname, ret_type ? ret_type : "NullTissue",
                      0, 0, node->lineno) == -1) {
            sem_error(node->lineno,
                      "function '%s' already declared in this scope", fname);
        }

        /* Build a new scope for the function body;
           populate it with the parameter list. */
        Scope *fn_scope = scope_new(scope);
        for (ParamNode *p = node->func.params; p; p = p->next) {
            if (scope_add(fn_scope, p->name, p->type, 0, 0,
                          node->lineno) == -1) {
                sem_error(node->lineno,
                    "duplicate parameter name '%s' in function '%s'",
                    p->name, fname);
            } else {
                scope_mark_init(fn_scope, p->name);
            }
        }

        /* Analyse the body, tracking whether every path returns */
        int fn_has_return = 0;
        analyze(node->func.body, fn_scope, ret_type, &fn_has_return);
        scope_free(fn_scope);

        /* Missing return path check (only for non-void functions) */
        if (ret_type &&
            strcmp(ret_type, "NullTissue") != 0 &&
            !fn_has_return) {
            sem_error(node->lineno,
                "function '%s' declared to return %s but has no Discharge",
                fname, ret_type);
        }
        break;
    }

    /* ---- Admission (special entry-point function) ---- */
    case NODE_FUNC_DEF + 100:   /* won't match — handled below via
                                   the same NODE_FUNC_DEF case         */
        break;

    /* ---- Function call ---- */
    case NODE_FUNC_CALL: {
        const char *fname = node->call.name;

        /* Built-in functions are always valid */
        static const char *builtins[] = {
            "Power","RootCause","AbsDose","RoundDown","RoundUp",
            "Sine","Cosine","Tangent","IsCritical", NULL
        };
        int is_builtin = 0;
        for (int i = 0; builtins[i]; i++)
            if (strcmp(fname, builtins[i]) == 0) { is_builtin = 1; break; }

        if (!is_builtin) {
            Symbol *sym = scope_lookup(scope, fname);
            if (!sym)
                sem_error(node->lineno,
                          "function '%s' called before declaration", fname);
        }

        /* Recursively check each argument expression */
        for (ArgNode *a = node->call.args; a; a = a->next)
            analyze(a->expr, scope, enclosing_ret_type, has_return);
        break;
    }

    /* ---- Return (Discharge) ---- */
    case NODE_RETURN: {
        if (has_return) *has_return = 1;

        if (!node->binop.left) {
            /* Discharge with no value — only valid in NullTissue functions */
            if (enclosing_ret_type &&
                strcmp(enclosing_ret_type, "NullTissue") != 0) {
                sem_error(node->lineno,
                    "empty Discharge in function declared to return %s",
                    enclosing_ret_type);
            }
            break;
        }

        analyze(node->binop.left, scope, enclosing_ret_type, has_return);

        /* Type-check the returned expression against the declared return type */
        if (enclosing_ret_type) {
            const char *ret_expr_type = infer_type(node->binop.left, scope);
            if (ret_expr_type &&
                !types_compatible(enclosing_ret_type, ret_expr_type)) {
                sem_error(node->lineno,
                    "Discharge type %s does not match declared return type %s",
                    ret_expr_type, enclosing_ret_type);
            }
        }
        break;
    }

    /* ---- Break / Continue / literals — nothing to check ---- */
    case NODE_BREAK:
    case NODE_CONTINUE:
    case NODE_INT_LIT:
    case NODE_FLOAT_LIT:
    case NODE_STRING_LIT:
        break;

    /* ---- Binary / unary ops — recurse into sub-expressions ---- */
    case NODE_BINOP:
        analyze(node->binop.left,  scope, enclosing_ret_type, has_return);
        analyze(node->binop.right, scope, enclosing_ret_type, has_return);
        break;

    case NODE_UNOP:
        analyze(node->binop.left,  scope, enclosing_ret_type, has_return);
        break;

    default:
        break;
    }
}

/* ============================================================
   Public entry point
   ============================================================ */
int analyze_program(ASTNode *root) {
    sem_error_count = 0;
    sem_warn_count  = 0;

    Scope *global = scope_new(NULL);
    int dummy_return = 0;
    analyze(root, global, NULL, &dummy_return);
    scope_free(global);

    if (sem_warn_count > 0)
        fprintf(stderr, "[MedLang] %d semantic warning(s).\n",
                sem_warn_count);

    if (sem_error_count > 0) {
        fprintf(stderr, "[MedLang] %d semantic error(s) found. "
                        "Compilation aborted.\n", sem_error_count);
        return 1;
    }

    printf("[MedLang] Semantic analysis passed.\n");
    return 0;
}