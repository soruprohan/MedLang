/* semantic.c — MedLang Semantic Analysis
   Phase 3: Semantic Analysis

   Checks implemented:
     1. Double declaration in same scope
     2. Undeclared variable use
     3. Sealed (immutable) reassignment
     4. Type mismatch / strong typing
     5. Missing Discharge (return) path in non-void functions
     6. Range-loop direction warning (e.g. Cycle <: i in 10..1 :>)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "ast.h"
#include "symtable.h"
#include "semantic.h"
#include "medlang.tab.h"

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
   ============================================================ */
static int types_compatible(const char *lhs, const char *rhs) {
    if (!lhs || !rhs) return 1;
    if (strcmp(lhs, rhs) == 0) return 1;

    if (strcmp(lhs, "Flow") == 0)
        return strcmp(rhs, "Organ") == 0;

    if (strcmp(lhs, "Diabetes") == 0)
        return strcmp(rhs, "Flow")  == 0
            || strcmp(rhs, "Organ") == 0;

    if (strcmp(lhs, "MajorOrgan") == 0)
        return strcmp(rhs, "Organ") == 0;

    if (strcmp(lhs, "Cell") == 0)
        return strcmp(rhs, "Organ") == 0;

    if (strcmp(lhs, "Tissue") == 0)
        return strcmp(rhs, "Tissue") == 0;

    if (strcmp(lhs, "MinorOrgan") == 0)
        return strcmp(rhs, "Organ") == 0;

    if (strcmp(lhs, "NonPathologic") == 0)
        return strcmp(rhs, "Organ") == 0;

    return 0;
}

/* ============================================================
   Infer the result type of an expression node.
   ============================================================ */
static const char *infer_type(ASTNode *node, Scope *scope) {
    if (!node) return NULL;

    switch (node->type) {

    case NODE_INT_LIT:    return "Organ";
    case NODE_FLOAT_LIT:  return "Flow";
    case NODE_STRING_LIT: return "Tissue";

    case NODE_IDENT: {
        Symbol *sym = scope_lookup(scope, node->sval);
        if (!sym) return NULL;
        return sym->type;
    }

    case NODE_BINOP: {
        const char *lt = infer_type(node->binop.left,  scope);
        const char *rt = infer_type(node->binop.right, scope);
        int op = node->binop.op;

        if (op == EQ || op == NEQ || op == GT  || op == LT  ||
            op == GEQ || op == LEQ || op == AND || op == OR)
            return "Organ";

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
        return infer_type(node->binop.left, scope);

    case NODE_FUNC_CALL: {
        const char *n = node->call.name;
        if (strcmp(n, "Power")     == 0 || strcmp(n, "RootCause") == 0 ||
            strcmp(n, "AbsDose")   == 0 || strcmp(n, "RoundDown") == 0 ||
            strcmp(n, "RoundUp")   == 0 || strcmp(n, "Sine")      == 0 ||
            strcmp(n, "Cosine")    == 0 || strcmp(n, "Tangent")   == 0)
            return "Flow";
        if (strcmp(n, "IsCritical") == 0)
            return "Organ";
        Symbol *sym = scope_lookup(scope, n);
        if (sym) return sym->type;
        return NULL;
    }

    default:
        return NULL;
    }
}

/* ============================================================
   Forward declaration
   ============================================================ */
static void analyze(ASTNode *node, Scope *scope,
                    const char *enclosing_ret_type,
                    int *has_return);

/* ============================================================
   Core recursive analysis walker
   ============================================================ */
static void analyze(ASTNode *node, Scope *scope,
                    const char *enclosing_ret_type,
                    int *has_return) {
    if (!node) return;

    switch (node->type) {

    /* ---- Program root ---- */
    case NODE_PROGRAM:
        analyze(node->binop.left, scope, enclosing_ret_type, has_return);
        break;

    /* ---- Statement list ---- */
    case NODE_STMT_LIST: {
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
        int sealed   = node->decl.is_sealed;
        int nosample = node->decl.is_nosample;

        if (scope_add(scope, vname, vtype, sealed, nosample,
                      node->lineno) == -1) {
            sem_error(node->lineno,
                      "'%s' already declared in this scope", vname);
        }

        if (node->decl.init) {
            analyze(node->decl.init, scope, enclosing_ret_type, has_return);

            const char *rhs_type = infer_type(node->decl.init, scope);
            if (rhs_type && !types_compatible(vtype, rhs_type)) {
                sem_error(node->lineno,
                    "cannot assign %s value to %s variable '%s'",
                    rhs_type, vtype, vname);
            }

            scope_mark_init(scope, vname);
        }
        break;
    }

    /* ---- NoSample declaration — treated as a plain declaration ---- */
    case NODE_NOSAMPLE_DECL: {
        const char *vname = node->decl.name;
        const char *vtype = node->decl.datatype;
        if (scope_add(scope, vname, vtype, 0, 0, node->lineno) == -1) {
            sem_error(node->lineno,
                      "'%s' already declared in this scope", vname);
        }
        scope_mark_init(scope, vname);
        break;
    }

    /* ---- Assignment ---- */
    case NODE_ASSIGN: {
        const char *vname = node->assign.name;
        Symbol *sym = scope_lookup(scope, vname);

        if (!sym) {
            sem_error(node->lineno,
                      "'%s' used before declaration", vname);
            analyze(node->assign.expr, scope, enclosing_ret_type, has_return);
            break;
        }

        if (sym->is_sealed && sym->initialized) {
            sem_error(node->lineno,
                      "'%s' is Sealed and cannot be reassigned", vname);
        }

        analyze(node->assign.expr, scope, enclosing_ret_type, has_return);

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
        if (!scope_lookup(scope, vname)) {
            sem_error(node->lineno,
                      "'%s' used before declaration", vname);
        }
        break;
    }

    /* ---- If / Else (Diagnose / Alternate) ---- */
    case NODE_IF: {
        analyze(node->ifnode.cond, scope, enclosing_ret_type, has_return);

        int then_returns = 0;
        Scope *then_scope = scope_new(scope);
        analyze(node->ifnode.then_block, then_scope,
                enclosing_ret_type, &then_returns);
        scope_free(then_scope);

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

        if (from > to) {
            sem_warn(node->lineno,
                "range %d..%d goes backward with no step direction; "
                "loop may not execute", from, to);
        }

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

        if (scope_add(scope, fname, ret_type ? ret_type : "NullTissue",
                      0, 0, node->lineno) == -1) {
            sem_error(node->lineno,
                      "function '%s' already declared in this scope", fname);
        }

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

        int fn_has_return = 0;
        analyze(node->func.body, fn_scope, ret_type, &fn_has_return);
        scope_free(fn_scope);

        if (ret_type &&
            strcmp(ret_type, "NullTissue") != 0 &&
            !fn_has_return) {
            sem_error(node->lineno,
                "function '%s' declared to return %s but has no Discharge",
                fname, ret_type);
        }
        break;
    }

    /* ---- Function call ---- */
    case NODE_FUNC_CALL: {
        /* Recurse into arguments only — function existence is guaranteed
           by the interpreter's collect_funcs() pre-pass */
        for (ArgNode *a = node->call.args; a; a = a->next)
            analyze(a->expr, scope, enclosing_ret_type, has_return);
        break;
    }

    /* ---- Return (Discharge) ---- */
    case NODE_RETURN: {
        if (has_return) *has_return = 1;

        if (!node->binop.left) {
            if (enclosing_ret_type &&
                strcmp(enclosing_ret_type, "NullTissue") != 0) {
                sem_error(node->lineno,
                    "empty Discharge in function declared to return %s",
                    enclosing_ret_type);
            }
            break;
        }

        analyze(node->binop.left, scope, enclosing_ret_type, has_return);

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

    /* ---- Break / Continue / literals ---- */
    case NODE_BREAK:
    case NODE_CONTINUE:
    case NODE_INT_LIT:
    case NODE_FLOAT_LIT:
    case NODE_STRING_LIT:
        break;

    /* ---- Binary / unary ops ---- */
    case NODE_BINOP:
        analyze(node->binop.left,  scope, enclosing_ret_type, has_return);
        analyze(node->binop.right, scope, enclosing_ret_type, has_return);
        break;

    case NODE_UNOP:
        analyze(node->binop.left,  scope, enclosing_ret_type, has_return);
        break;

    default:
        break;

    } /* end switch */
} /* end analyze() */

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