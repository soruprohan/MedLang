/* ast.c — AST constructor implementations + pretty-printer
   Phase 2: Syntax Analysis & AST Construction
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* ============================================================
   Internal helper: allocate a zeroed node
   ============================================================ */
static ASTNode *new_node(NodeType t, int line) {
    ASTNode *n = calloc(1, sizeof(ASTNode));
    if (!n) { fprintf(stderr, "Out of memory\n"); exit(1); }
    n->type   = t;
    n->lineno = line;
    return n;
}

/* ============================================================
   Literals
   ============================================================ */
ASTNode *make_int_lit(int v, int line) {
    ASTNode *n = new_node(NODE_INT_LIT, line);
    n->ival = v;
    return n;
}

ASTNode *make_float_lit(float v, int line) {
    ASTNode *n = new_node(NODE_FLOAT_LIT, line);
    n->fval = v;
    return n;
}

ASTNode *make_string_lit(char *s, int line) {
    ASTNode *n = new_node(NODE_STRING_LIT, line);
    n->sval = s;
    return n;
}

ASTNode *make_ident(char *name, int line) {
    ASTNode *n = new_node(NODE_IDENT, line);
    n->sval = name;
    return n;
}

/* ============================================================
   Operators
   ============================================================ */
ASTNode *make_binop(int op, ASTNode *left, ASTNode *right, int line) {
    ASTNode *n = new_node(NODE_BINOP, line);
    n->binop.op    = op;
    n->binop.left  = left;
    n->binop.right = right;
    return n;
}

ASTNode *make_unop(int op, ASTNode *operand, int line) {
    ASTNode *n = new_node(NODE_UNOP, line);
    n->binop.op    = op;
    n->binop.left  = operand;
    n->binop.right = NULL;
    return n;
}

/* ============================================================
   Variable declaration
   ============================================================ */
ASTNode *make_decl(char *type, char *name,
                   int is_sealed, int is_nosample,
                   ASTNode *init, int line) {
    ASTNode *n = new_node(NODE_DECL, line);
    n->decl.datatype   = type;
    n->decl.name       = name;
    n->decl.is_sealed  = is_sealed;
    n->decl.is_nosample= is_nosample;
    n->decl.init       = init;
    return n;
}

/* ============================================================
   Assignment
   ============================================================ */
ASTNode *make_assign(char *name, ASTNode *expr, int line) {
    ASTNode *n = new_node(NODE_ASSIGN, line);
    n->assign.name = name;
    n->assign.expr = expr;
    return n;
}

/* ============================================================
   Control flow
   ============================================================ */
ASTNode *make_if(ASTNode *cond, ASTNode *then_b,
                  ASTNode *else_b, int line) {
    ASTNode *n = new_node(NODE_IF, line);
    n->ifnode.cond       = cond;
    n->ifnode.then_block = then_b;
    n->ifnode.else_block = else_b;
    return n;
}

ASTNode *make_while(ASTNode *cond, ASTNode *body, int line) {
    ASTNode *n = new_node(NODE_WHILE, line);
    n->loop.cond = cond;
    n->loop.body = body;
    return n;
}

ASTNode *make_do_while(ASTNode *body, ASTNode *cond, int line) {
    ASTNode *n = new_node(NODE_DO_WHILE, line);
    n->loop.cond = cond;
    n->loop.body = body;
    return n;
}

ASTNode *make_for(ASTNode *init, ASTNode *cond,
                   ASTNode *update, ASTNode *body, int line) {
    ASTNode *n = new_node(NODE_FOR, line);
    n->forloop.init   = init;
    n->forloop.cond   = cond;
    n->forloop.update = update;
    n->forloop.body   = body;
    return n;
}

ASTNode *make_range_loop(char *var, int from, int to,
                          ASTNode *body, int line) {
    ASTNode *n = new_node(NODE_FOR_RANGE, line);
    n->range_loop.var  = var;
    n->range_loop.from = from;
    n->range_loop.to   = to;
    n->range_loop.body = body;
    return n;
}

/* ============================================================
   Functions
   ============================================================ */
ASTNode *make_func_def(char *ret_type, char *name,
                        ParamNode *params, ASTNode *body, int line) {
    ASTNode *n = new_node(NODE_FUNC_DEF, line);
    n->func.ret_type = ret_type;
    n->func.name     = name;
    n->func.params   = params;
    n->func.body     = body;
    return n;
}

ASTNode *make_func_call(char *name, ArgNode *args, int line) {
    ASTNode *n = new_node(NODE_FUNC_CALL, line);
    n->call.name = name;
    n->call.args = args;
    return n;
}

ParamNode *make_param(char *type, char *name, ParamNode *next) {
    ParamNode *p = calloc(1, sizeof(ParamNode));
    p->type = type;
    p->name = name;
    p->next = next;
    return p;
}

ArgNode *make_arg(char *label, ASTNode *expr, ArgNode *next) {
    ArgNode *a = calloc(1, sizeof(ArgNode));
    a->label = label;
    a->expr  = expr;
    a->next  = next;
    return a;
}

/* ============================================================
   Statements
   ============================================================ */
ASTNode *make_return(ASTNode *expr, int line) {
    ASTNode *n = new_node(NODE_RETURN, line);
    n->binop.left = expr; /* reuse left slot for the single child */
    return n;
}

ASTNode *make_break(int line) {
    return new_node(NODE_BREAK, line);
}

ASTNode *make_continue(int line) {
    return new_node(NODE_CONTINUE, line);
}

ASTNode *make_block(ASTNode *stmts, int line) {
    ASTNode *n = new_node(NODE_BLOCK, line);
    n->binop.left = stmts; /* single child */
    return n;
}

/* ============================================================
   Statement list  (right-linear: head → tail chain)
   append(existing_list, new_stmt) pattern:
     make_stmt_list(existing, new_stmt)
   ============================================================ */
ASTNode *make_stmt_list(ASTNode *head, ASTNode *tail) {
    ASTNode *n = new_node(NODE_STMT_LIST, 0);
    n->list.head = head;
    n->list.tail = tail;
    return n;
}

/* ============================================================
   Program root
   ============================================================ */
ASTNode *make_program(ASTNode *stmts) {
    ASTNode *n = new_node(NODE_PROGRAM, 0);
    n->binop.left = stmts;
    return n;
}

/* ============================================================
   Pretty-printer (bonus visual output — Section 7 of guide)
   ============================================================ */
static const char *op_name(int op) {
    /* token codes from medlang.tab.h */
    switch (op) {
        case 258+14: return "+";   /* adjust if token numbers differ */
        default:     return "op";
    }
}

/* We use a simpler approach: map op int to string via a lookup */
static const char *opstr(int op);  /* forward decl */

void print_ast(ASTNode *n, int indent) {
    if (!n) return;
    for (int i = 0; i < indent; i++) printf("  ");

    switch (n->type) {

        case NODE_PROGRAM:
            printf("Program\n");
            print_ast(n->binop.left, indent + 1);
            break;

        case NODE_STMT_LIST:
            print_ast(n->list.head, indent);
            print_ast(n->list.tail, indent);
            break;

        case NODE_INT_LIT:
            printf("IntLit(%d)\n", n->ival);
            break;

        case NODE_FLOAT_LIT:
            printf("FloatLit(%f)\n", n->fval);
            break;

        case NODE_STRING_LIT:
            printf("StrLit(\"%s\")\n", n->sval);
            break;

        case NODE_IDENT:
            printf("Ident(%s)\n", n->sval);
            break;

        case NODE_BINOP:
            printf("BinOp(%s)\n", opstr(n->binop.op));
            print_ast(n->binop.left,  indent + 1);
            print_ast(n->binop.right, indent + 1);
            break;

        case NODE_UNOP:
            printf("UnOp(%s)\n", opstr(n->binop.op));
            print_ast(n->binop.left, indent + 1);
            break;

        case NODE_DECL:
            printf("Decl(%s %s%s%s)\n",
                n->decl.datatype,
                n->decl.name,
                n->decl.is_sealed   ? " [SEALED]"   : "",
                n->decl.is_nosample ? " [NOSAMPLE]" : "");
            if (n->decl.init) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("Init:\n");
                print_ast(n->decl.init, indent + 2);
            }
            break;

        case NODE_ASSIGN:
            printf("Assign(%s)\n", n->assign.name);
            print_ast(n->assign.expr, indent + 1);
            break;

        case NODE_IF:
            printf("If\n");
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Cond:\n");
            print_ast(n->ifnode.cond,       indent + 2);
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Then:\n");
            print_ast(n->ifnode.then_block, indent + 2);
            if (n->ifnode.else_block) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("Else:\n");
                print_ast(n->ifnode.else_block, indent + 2);
            }
            break;

        case NODE_WHILE:
            printf("While\n");
            print_ast(n->loop.cond, indent + 1);
            print_ast(n->loop.body, indent + 1);
            break;

        case NODE_DO_WHILE:
            printf("DoWhile\n");
            print_ast(n->loop.body, indent + 1);
            print_ast(n->loop.cond, indent + 1);
            break;

        case NODE_FOR:
            printf("For\n");
            print_ast(n->forloop.init,   indent + 1);
            print_ast(n->forloop.cond,   indent + 1);
            print_ast(n->forloop.update, indent + 1);
            print_ast(n->forloop.body,   indent + 1);
            break;

        case NODE_FOR_RANGE:
            printf("RangeCycle(%s in %d..%d)\n",
                n->range_loop.var,
                n->range_loop.from,
                n->range_loop.to);
            print_ast(n->range_loop.body, indent + 1);
            break;

        case NODE_FUNC_DEF:
            printf("FuncDef(%s %s)\n",
                n->func.ret_type, n->func.name);
            for (ParamNode *p = n->func.params; p; p = p->next) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("Param(%s %s)\n", p->type, p->name);
            }
            print_ast(n->func.body, indent + 1);
            break;

        case NODE_FUNC_CALL:
            printf("FuncCall(%s)\n", n->call.name);
            for (ArgNode *a = n->call.args; a; a = a->next) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                if (a->label)
                    printf("NamedArg(%s:)\n", a->label);
                else
                    printf("Arg:\n");
                print_ast(a->expr, indent + 2);
            }
            break;

        case NODE_RETURN:
            printf("Return\n");
            print_ast(n->binop.left, indent + 1);
            break;

        case NODE_BREAK:
            printf("Break\n");
            break;

        case NODE_CONTINUE:
            printf("Continue\n");
            break;

        case NODE_BLOCK:
            printf("Block\n");
            print_ast(n->binop.left, indent + 1);
            break;

        default:
            printf("Node(%d)\n", n->type);
            break;
    }
}

/* Map operator token code to printable string.
   These numeric values match what Bison assigns in medlang.tab.h.
   If they shift, just update here — logic is unchanged. */
static const char *opstr(int op) {
    /* We include medlang.tab.h token values via a switch.
       Using string names is safer across regenerations. */
    static char buf[8];
    /* Common ones spelled out; fallback prints the int */
    switch (op) {
        /* The actual enum values come from medlang.tab.h.
           These names match the %token declarations. */
        default:
            snprintf(buf, sizeof(buf), "<%d>", op);
            return buf;
    }
}