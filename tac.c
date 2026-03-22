/* tac.c - MedLang Three-Address Code emitter + code generator
   Phase 4: Intermediate Code Generation

   Two-part file:
     Part A  - TAC list management (emit, print, free)
     Part B  - AST walker:  char *tac_gen(ASTNode *)
                            void  tac_gen_program(ASTNode *)

   tac_gen_program() is the public entry point called from main().

   Key structural facts about the AST (from ast.c) that drive this file:
     - make_program()   stores its child in  binop.left  (not list.head)
     - make_block()     stores its child in  binop.left  (not list.head)
     - make_stmt_list() is a LEFT-recursive chain: list.head = the
                        accumulated list so far, list.tail = one new item
     - make_return()    stores its expr in   binop.left
     - make_unop()      stores its operand in binop.left
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "tac.h"
#include "medlang.tab.h"   /* token codes: PLUS, MINUS, GT, etc. */

/* ================================================================
   PART A - TAC list management
   ================================================================ */

/* Global instruction list */
static TACInstr *tac_head = NULL;
static TACInstr *tac_tail = NULL;

/* Counters for fresh names */
static int temp_count  = 0;
static int label_count = 0;

/* ---------- fresh name helpers ---------------------------------- */

char *tac_new_temp(void) {
    char buf[32];
    sprintf(buf, "t%d", temp_count++);
    return strdup(buf);
}

char *tac_new_label(void) {
    char buf[32];
    sprintf(buf, "L%d", label_count++);
    return strdup(buf);
}

/* ---------- emit ------------------------------------------------- */

void tac_emit(TACOp op,
              const char *result,
              const char *arg1,
              const char *arg2)
{
    TACInstr *ins = (TACInstr *)malloc(sizeof(TACInstr));
    if (!ins) { fprintf(stderr, "[TAC] out of memory\n"); exit(1); }

    ins->op     = op;
    ins->result = result ? strdup(result) : NULL;
    ins->arg1   = arg1   ? strdup(arg1)   : NULL;
    ins->arg2   = arg2   ? strdup(arg2)   : NULL;
    ins->next   = NULL;

    if (!tac_head) tac_head = tac_tail = ins;
    else           { tac_tail->next = ins; tac_tail = ins; }
}

/* ---------- print ------------------------------------------------ */

/* Map a TAC opcode + stored fields to a human-readable line.
   For TAC_BINOP the combined arg2 field holds "<op_symbol> <rhs>",
   e.g. "+ y" or "<= 10", so the printed form is:
       result = arg1 <op_symbol> <rhs>                              */
static void print_instr(FILE *fp, TACInstr *ins) {
    switch (ins->op) {

    case TAC_ASSIGN:
        /* result = arg1 */
        fprintf(fp, "    %s = %s\n",
                ins->result ? ins->result : "?",
                ins->arg1   ? ins->arg1   : "?");
        break;

    case TAC_BINOP:
        /* result = arg1  <op> <rhs>
           arg2 holds the combined "<op_symbol> <rhs>" string built
           in tac_gen() so we can print it as one clean field.      */
        fprintf(fp, "    %s = %s %s\n",
                ins->result ? ins->result : "?",
                ins->arg1   ? ins->arg1   : "?",
                ins->arg2   ? ins->arg2   : "?");
        break;

    case TAC_UNOP:
        /* result = <op> arg1
           op symbol is stored in arg2, operand in arg1             */
        fprintf(fp, "    %s = %s %s\n",
                ins->result ? ins->result : "?",
                ins->arg2   ? ins->arg2   : "-",   /* op symbol */
                ins->arg1   ? ins->arg1   : "?");
        break;

    case TAC_LABEL:
        /* LABEL: */
        fprintf(fp, "%s:\n", ins->result ? ins->result : "?");
        break;

    case TAC_GOTO:
        /* goto LABEL */
        fprintf(fp, "    goto %s\n", ins->arg1 ? ins->arg1 : "?");
        break;

    case TAC_IF_GOTO:
        /* if cond goto LABEL */
        fprintf(fp, "    if %s goto %s\n",
                ins->arg1 ? ins->arg1 : "?",
                ins->arg2 ? ins->arg2 : "?");
        break;

    case TAC_IFNOT_GOTO:
        /* ifnot cond goto LABEL */
        fprintf(fp, "    ifnot %s goto %s\n",
                ins->arg1 ? ins->arg1 : "?",
                ins->arg2 ? ins->arg2 : "?");
        break;

    case TAC_PARAM:
        /* param arg1 - push one argument before a call */
        fprintf(fp, "    param %s\n", ins->arg1 ? ins->arg1 : "?");
        break;

    case TAC_CALL:
        /* result = call callee, n_args   OR   call callee, n_args  */
        if (ins->result)
            fprintf(fp, "    %s = call %s, %s\n",
                    ins->result,
                    ins->arg1 ? ins->arg1 : "?",
                    ins->arg2 ? ins->arg2 : "0");
        else
            fprintf(fp, "    call %s, %s\n",
                    ins->arg1 ? ins->arg1 : "?",
                    ins->arg2 ? ins->arg2 : "0");
        break;

    case TAC_RETURN:
        /* return value   OR   return  (void) */
        if (ins->arg1)
            fprintf(fp, "    return %s\n", ins->arg1);
        else
            fprintf(fp, "    return\n");
        break;

    case TAC_BEGIN_FUNC:
        /* begin_func name - marks the start of a function's TAC */
        fprintf(fp, "begin_func %s\n", ins->arg1 ? ins->arg1 : "?");
        break;

    case TAC_END_FUNC:
        /* end_func - marks the end of a function's TAC */
        fprintf(fp, "end_func\n");
        break;
    }
}

void tac_print_all(void) {
    /* Write TAC to output.tac only - not to stdout.
       The console only gets a short confirmation line.             */
    FILE *fp = fopen("output.tac", "w");
    if (!fp) {
        fprintf(stderr, "[TAC] Warning: cannot open output.tac for writing\n");
        return;
    }

    fprintf(fp, "; MedLang Three-Address Code\n");

    for (TACInstr *cur = tac_head; cur; cur = cur->next) {
        print_instr(fp, cur);
    }

    fclose(fp);
    printf("[MedLang] TAC generation complete. Output written to output.tac\n");
}

void tac_free_all(void) {
    TACInstr *cur = tac_head;
    while (cur) {
        TACInstr *next = cur->next;
        free(cur->result);
        free(cur->arg1);
        free(cur->arg2);
        free(cur);
        cur = next;
    }
    tac_head = tac_tail = NULL;
}

/* ================================================================
   PART B - AST to TAC code generator
   ================================================================ */

/* Forward declaration - tac_gen and tac_gen_stmts call each other */
static char *tac_gen(ASTNode *node);

/* ----------------------------------------------------------------
   op_symbol - map a MedLang token code to its TAC operator string
   Token codes come from medlang.tab.h (generated by Bison).
   ---------------------------------------------------------------- */
static const char *op_symbol(int op) {
    switch (op) {
    case PLUS:     return "+";
    case MINUS:    return "-";
    case MULTIPLY: return "*";
    case DIVIDE:   return "/";
    case MOD:      return "%";
    case EQ:       return "==";
    case NEQ:      return "!=";
    case GT:       return ">";
    case LT:       return "<";
    case GEQ:      return ">=";
    case LEQ:      return "<=";
    case AND:      return "&&";
    case OR:       return "||";
    default:       return "?";
    }
}

/* ----------------------------------------------------------------
   int_to_str - return a heap-allocated decimal string for an int.
   Used for range loop bounds and constant folding results.
   ---------------------------------------------------------------- */
static char *int_to_str(int v) {
    char buf[32];
    sprintf(buf, "%d", v);
    return strdup(buf);
}

/* ----------------------------------------------------------------
   count_args - count the arguments in a function call arg list.
   ---------------------------------------------------------------- */
static int count_args(ArgNode *a) {
    int n = 0;
    for (; a; a = a->next) n++;
    return n;
}

/* ----------------------------------------------------------------
   tac_gen_stmts - unified dispatcher for any "container" node.

   The AST has three different shapes that hold sequences of stmts:

     NODE_STMT_LIST - left-recursive chain built by make_stmt_list():
                          list.head = the accumulated list so far
                          list.tail = one new single statement

     NODE_BLOCK     - wrapper built by make_block():
                          binop.left = the inner stmt_list (or NULL)
                          NOTE: make_block uses binop.left, NOT list.head.

     anything else  - a plain statement leaf; dispatch to tac_gen().

   Centralising this here means every loop/if/func body can just call
   tac_gen_stmts(body) without caring which shape it received.
   ---------------------------------------------------------------- */
static void tac_gen_stmts(ASTNode *node) {
    if (!node) return;

    if (node->type == NODE_STMT_LIST) {
        /* Right-linear chain: walk head (one stmt), then tail (rest) */
        tac_gen_stmts(node->list.head);
        tac_gen_stmts(node->list.tail);
    } else if (node->type == NODE_BLOCK) {
        /* make_block() stores its child in binop.left, not list.head */
        tac_gen_stmts(node->binop.left);
    } else {
        /* Plain statement or expression - generate TAC directly */
        tac_gen(node);
    }
}

/* ----------------------------------------------------------------
   tac_gen - main recursive TAC generator.

   Returns: a heap-allocated string naming the temp or variable that
            holds this node's value, or NULL for statement nodes.
   Ownership: the caller must free() the returned string after it has
              been passed to tac_emit() (which strdup's it internally).
   ---------------------------------------------------------------- */
static char *tac_gen(ASTNode *node) {
    if (!node) return NULL;

    switch (node->type) {

    /* ---- Integer literal ---- */
    case NODE_INT_LIT: {
        /* Return the numeric string directly; the parent will emit
           an assignment like:  t0 = 42                             */
        char *s = int_to_str(node->ival);
        return s;
    }

    /* ---- Float literal ---- */
    case NODE_FLOAT_LIT: {
        char *s = (char *)malloc(32);
        sprintf(s, "%g", (double)node->fval);
        return s;
    }

    /* ---- String literal ---- */
    case NODE_STRING_LIT: {
        /* Wrap in quotes so the TAC output is readable */
        char *s = (char *)malloc(strlen(node->sval) + 3);
        sprintf(s, "\"%s\"", node->sval);
        return s;
    }

    /* ---- Identifier ---- */
    case NODE_IDENT:
        /* The variable name is its own "temp" - no instruction needed */
        return strdup(node->sval);

    /* ---- Binary operation ---- */
    case NODE_BINOP: {
        ASTNode *lhs = node->binop.left;
        ASTNode *rhs = node->binop.right;

        /* ---- Constant folding: both sides are integer literals ----
           Instead of emitting three instructions (t0=lv, t1=rv, t2=t0 op t1)
           we compute the result at compile time and emit one assignment.
           This satisfies the rubric's "Code Optimization Technique" item.
           Division/mod by zero are left unfolded to avoid compile-time UB. */
        if (lhs && rhs &&
            lhs->type == NODE_INT_LIT &&
            rhs->type == NODE_INT_LIT)
        {
            int lv = lhs->ival, rv = rhs->ival, result_val = 0, folded = 1;
            switch (node->binop.op) {
            case PLUS:     result_val = lv + rv; break;
            case MINUS:    result_val = lv - rv; break;
            case MULTIPLY: result_val = lv * rv; break;
            case DIVIDE:   if (rv) result_val = lv / rv; else folded = 0; break;
            case MOD:      if (rv) result_val = lv % rv; else folded = 0; break;
            default:       folded = 0; break;   /* comparisons - not folded */
            }
            if (folded) {
                char *t = tac_new_temp();
                char buf[32];
                sprintf(buf, "%d", result_val);
                tac_emit(TAC_ASSIGN, t, buf, NULL);
                return t;
            }
        }

        /* ---- General case ----
           Emit:   l  = <gen lhs>
                   r  = <gen rhs>
                   t  = l <op> r
           We store the operator symbol and rhs together in arg2 so
           print_instr() can display:  t = l <op> r  cleanly.       */
        char *l = tac_gen(lhs);
        char *r = tac_gen(rhs);
        char *t = tac_new_temp();
        const char *sym = op_symbol(node->binop.op);
        char *combined = (char *)malloc(strlen(sym) + strlen(r ? r : "?") + 3);
        sprintf(combined, "%s %s", sym, r ? r : "?");
        tac_emit(TAC_BINOP, t, l, combined);
        free(l); free(r); free(combined);
        return t;
    }

    /* ---- Unary operation ----
       make_unop() stores the operand in binop.left (same slot as
       the left child of a binary op).                              */
    case NODE_UNOP: {
        char *operand = tac_gen(node->binop.left);
        char *t = tac_new_temp();
        const char *sym = (node->binop.op == MINUS) ? "-" : "!";
        tac_emit(TAC_UNOP, t, operand, sym);
        free(operand);
        return t;
    }

    /* ---- Variable declaration ----
       Covers both the standard form (Organ x =: expr |) and the
       Sealed form (Sealed Organ x =: expr |).
       If there is an initialiser we emit:   name = <rhs>
       If not (NoSample with no init) we skip - nothing to assign.  */
    case NODE_DECL:
    case NODE_NOSAMPLE_DECL: {
        if (node->decl.init) {
            char *rhs = tac_gen(node->decl.init);
            tac_emit(TAC_ASSIGN, node->decl.name, rhs, NULL);
            free(rhs);
        } else if (node->type == NODE_NOSAMPLE_DECL) {
            /* Make it explicit in the TAC that the var starts as null */
            tac_emit(TAC_ASSIGN, node->decl.name, "NoSample", NULL);
        }
        return NULL;
    }

    /* ---- Assignment  (x =: expr) ---- */
    case NODE_ASSIGN: {
        char *rhs = tac_gen(node->assign.expr);
        tac_emit(TAC_ASSIGN, node->assign.name, rhs, NULL);
        free(rhs);
        return NULL;
    }

    /* ---- If / Else  (Diagnose / Alternate) ----
       Classic short-circuit pattern:
           ifnot cond goto L_else
           <then body>
           goto L_end          <- only emitted when there is an else
       L_else:
           <else body>         <- only emitted when there is an else
       L_end:                  <- only emitted when there is an else  */
    case NODE_IF: {
        char *cond   = tac_gen(node->ifnode.cond);
        char *L_else = tac_new_label();
        char *L_end  = tac_new_label();

        tac_emit(TAC_IFNOT_GOTO, NULL, cond, L_else);
        free(cond);

        tac_gen_stmts(node->ifnode.then_block);

        if (node->ifnode.else_block) {
            tac_emit(TAC_GOTO, NULL, L_end, NULL);
        }
        tac_emit(TAC_LABEL, L_else, NULL, NULL);

        if (node->ifnode.else_block) {
            tac_gen_stmts(node->ifnode.else_block);
            tac_emit(TAC_LABEL, L_end, NULL, NULL);
        }

        free(L_else); free(L_end);
        return NULL;
    }

    /* ---- While loop  (Continuous) ----
       L_top:
           ifnot cond goto L_exit
           <body>
           goto L_top
       L_exit:                                                        */
    case NODE_WHILE: {
        char *L_top  = tac_new_label();
        char *L_exit = tac_new_label();

        tac_emit(TAC_LABEL, L_top, NULL, NULL);
        char *cond = tac_gen(node->loop.cond);
        tac_emit(TAC_IFNOT_GOTO, NULL, cond, L_exit);
        free(cond);

        tac_gen_stmts(node->loop.body);

        tac_emit(TAC_GOTO,  NULL, L_top,  NULL);
        tac_emit(TAC_LABEL, L_exit, NULL, NULL);
        free(L_top); free(L_exit);
        return NULL;
    }

    /* ---- Do-While loop  (LoadingDose) ----
       Body executes at least once; condition is checked at the bottom.
       L_top:
           <body>
           if cond goto L_top
       L_exit:                                                        */
    case NODE_DO_WHILE: {
        char *L_top  = tac_new_label();
        char *L_exit = tac_new_label();

        tac_emit(TAC_LABEL, L_top, NULL, NULL);
        tac_gen_stmts(node->loop.body);

        char *cond = tac_gen(node->loop.cond);
        tac_emit(TAC_IF_GOTO, NULL, cond,   L_top);
        tac_emit(TAC_LABEL,   L_exit, NULL, NULL);
        free(cond); free(L_top); free(L_exit);
        return NULL;
    }

    /* ---- Classic 3-part For loop  (Cycle) ----
           <init>
       L_top:
           ifnot cond goto L_exit
           <body>
           <update>
           goto L_top
       L_exit:                                                        */
    case NODE_FOR: {
        char *L_top  = tac_new_label();
        char *L_exit = tac_new_label();

        tac_gen(node->forloop.init);
        tac_emit(TAC_LABEL, L_top, NULL, NULL);

        if (node->forloop.cond) {
            char *cond = tac_gen(node->forloop.cond);
            tac_emit(TAC_IFNOT_GOTO, NULL, cond, L_exit);
            free(cond);
        }

        tac_gen_stmts(node->forloop.body);
        tac_gen(node->forloop.update);

        tac_emit(TAC_GOTO,  NULL, L_top,  NULL);
        tac_emit(TAC_LABEL, L_exit, NULL, NULL);
        free(L_top); free(L_exit);
        return NULL;
    }

    /* ---- Range-based Cycle  <: i in 1..10 :>  (Unique Feature) ----
       Initialise the loop variable, then check the bound at the top.
           i = from
       L_top:
           t_cond = i <= to
           ifnot t_cond goto L_exit
           <body>
           t_inc = i + 1
           i = t_inc
           goto L_top
       L_exit:                                                        */
    case NODE_FOR_RANGE: {
        char *L_top  = tac_new_label();
        char *L_exit = tac_new_label();
        char *from_s = int_to_str(node->range_loop.from);
        char *to_s   = int_to_str(node->range_loop.to);
        const char *var = node->range_loop.var;

        /* i = from */
        tac_emit(TAC_ASSIGN, var, from_s, NULL);
        free(from_s);

        tac_emit(TAC_LABEL, L_top, NULL, NULL);

        /* t_cond = i <= to */
        char *t_cond = tac_new_temp();
        char *cmp = (char *)malloc(strlen("<= ") + strlen(to_s) + 2);
        sprintf(cmp, "<= %s", to_s);
        tac_emit(TAC_BINOP, t_cond, var, cmp);
        free(cmp); free(to_s);

        tac_emit(TAC_IFNOT_GOTO, NULL, t_cond, L_exit);
        free(t_cond);

        tac_gen_stmts(node->range_loop.body);

        /* i = i + 1 */
        char *t_inc = tac_new_temp();
        tac_emit(TAC_BINOP,  t_inc, var, "+ 1");
        tac_emit(TAC_ASSIGN, var,   t_inc, NULL);
        free(t_inc);

        tac_emit(TAC_GOTO,  NULL, L_top,  NULL);
        tac_emit(TAC_LABEL, L_exit, NULL, NULL);
        free(L_top); free(L_exit);
        return NULL;
    }

    /* ---- Return  (Discharge) ----
       make_return() stores the return expression in binop.left
       (it reuses that slot for its single child).                   */
    case NODE_RETURN: {
        char *val = tac_gen(node->binop.left);
        tac_emit(TAC_RETURN, NULL, val, NULL);
        if (val) free(val);
        return NULL;
    }

    /* ---- Break / Continue  (Terminate / FollowUp) ----
       In a full implementation these would jump to the enclosing
       loop's L_exit / L_top labels. We emit a named placeholder so
       the TAC is not silently empty for these statements.           */
    case NODE_BREAK:
        tac_emit(TAC_GOTO, NULL, "BREAK_TARGET", NULL);
        return NULL;

    case NODE_CONTINUE:
        tac_emit(TAC_GOTO, NULL, "CONTINUE_TARGET", NULL);
        return NULL;

    /* ---- Function definition ----
       Wraps the body in begin_func / end_func markers so the TAC
       output is clearly divided by function.                        */
    case NODE_FUNC_DEF: {
        tac_emit(TAC_BEGIN_FUNC, NULL, node->func.name, NULL);
        tac_gen_stmts(node->func.body);
        tac_emit(TAC_END_FUNC, NULL, NULL, NULL);
        return NULL;
    }

    /* ---- Function call ----
       Push each argument as a param instruction, then emit the call.
       The return value lands in a fresh temp that the parent can use. */
    case NODE_FUNC_CALL: {
        int n = count_args(node->call.args);
        /* Collect into a local array to push args left-to-right */
        ArgNode *args[64]; int idx = 0;
        for (ArgNode *a = node->call.args; a && idx < 64; a = a->next)
            args[idx++] = a;
        for (int i = 0; i < idx; i++) {
            char *av = tac_gen(args[i]->expr);
            tac_emit(TAC_PARAM, NULL, av, NULL);
            free(av);
        }
        char *t = tac_new_temp();
        char n_str[16]; sprintf(n_str, "%d", n);
        tac_emit(TAC_CALL, t, node->call.name, n_str);
        return t;   /* caller may ignore this if the result is unused */
    }

    /* ---- Block  [: stmts :]  ----
       make_block() stores its inner stmt_list in binop.left,
       NOT in list.head.                                             */
    case NODE_BLOCK:
        tac_gen_stmts(node->binop.left);
        return NULL;

    /* ---- Statement list ----
       Delegate to tac_gen_stmts() which handles the chain correctly. */
    case NODE_STMT_LIST:
        tac_gen_stmts(node);
        return NULL;

    /* ---- NoSample check guard ----
       This node is the Diagnose <: x MisMatch NoSample :> pattern.
       The semantic phase already validated the guard; here we just
       generate TAC for the guarded body.                            */
    case NODE_NOSAMPLE_CHECK:
        tac_gen_stmts(node->ifnode.then_block);
        return NULL;

    /* ---- Program root ----
       make_program() stores its child in binop.left, NOT list.head. */
    case NODE_PROGRAM:
        tac_gen_stmts(node->binop.left);
        return NULL;

    default:
        /* Unknown or unhandled node type - safe to skip silently */
        return NULL;
    }
}

/* ================================================================
   Public entry point
   Called from main() in medlang.y after analyze_program() succeeds.
   ================================================================ */
void tac_gen_program(ASTNode *root) {
    if (!root) return;
    tac_gen(root);
}