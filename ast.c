/* ast.c — AST constructor implementations
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