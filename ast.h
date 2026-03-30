#ifndef AST_H
#define AST_H


//   Node type enum — one value per distinct construct
typedef enum {
    NODE_PROGRAM,       // root: list of top-level items
    NODE_STMT_LIST,     // linked list of statements
    NODE_DECL,          // variable declaration (all variants)
    NODE_ASSIGN,        // x =: expr
    NODE_IF,            // Diagnose / Alternate
    NODE_WHILE,         // Continuous
    NODE_DO_WHILE,      // LoadingDose
    NODE_FOR,           // Cycle (classic 3-part)
    NODE_FOR_RANGE,     // Cycle <: i in 1..10 :>
    NODE_BLOCK,         // [: stmt_list :]
    NODE_FUNC_DEF,      // type name <: params :> [: body :]
    NODE_FUNC_CALL,     // name <: args :>
    NODE_RETURN,        // Discharge expr
    NODE_BREAK,         // Terminate
    NODE_CONTINUE,      // FollowUp
    NODE_BINOP,         // expr op expr
    NODE_UNOP,          // op expr
    NODE_IDENT,         // identifier reference
    NODE_INT_LIT,       // integer literal
    NODE_FLOAT_LIT,     // float literal
    NODE_STRING_LIT,    // string literal
    NODE_NOSAMPLE_DECL, // NoSample type name |
    NODE_NOSAMPLE_CHECK // Diagnose <: x MisMatch NoSample :>
} NodeType;

//   Parameter list (for function definitions)
typedef struct ParamNode {
    char            *name;       // parameter name
    char            *type;       // "Organ", "Flow", etc.
    struct ParamNode *next;
} ParamNode;

//   Argument list (for function calls — supports named args)
typedef struct ArgNode {
    char           *label;  // NULL = positional; else named
    struct ASTNode *expr;
    struct ArgNode *next;
} ArgNode;

//   The AST node itself
typedef struct ASTNode {
    NodeType type;      
    int      lineno;   

    union {

        //  literals 
        int   ival;    // NODE_INT_LIT
        float fval;    // NODE_FLOAT_LIT
        char *sval;    // NODE_STRING_LIT, NODE_IDENT

        //  binary / unary ops 
        struct {
            int             op;    // token code: PLUS, GT
            struct ASTNode *left;
            struct ASTNode *right; // NULL for unary
        } binop;

        //  variable declaration 
        struct {
            char           *datatype;   // "Organ", "Flow"
            char           *name;
            int             is_sealed;  // 1 = immutable
            int             is_nosample;// 1 = nullable
            struct ASTNode *init;       // NULL if no init
        } decl;

        //  assignment 
        struct {
            char           *name;
            struct ASTNode *expr;
        } assign;

        //  if / else (Diagnose / Alternate) 
        struct {
            struct ASTNode *cond;
            struct ASTNode *then_block;
            struct ASTNode *else_block; // NULL if no Alternate
        } ifnode;

        //  while / do-while (Continuous / LoadingDose) 
        struct {
            struct ASTNode *cond;
            struct ASTNode *body;
        } loop;

        //  classic for loop (Cycle 3-part) 
        struct {
            struct ASTNode *init;
            struct ASTNode *cond;
            struct ASTNode *update;
            struct ASTNode *body;
        } forloop;

        //  range-based Cycle <: i in 1..10 :> 
        struct {
            char           *var;   // loop variable name
            int             from;
            int             to;
            struct ASTNode *body;
        } range_loop;

        //  function definition 
        struct {
            char           *name;
            char           *ret_type;  // "Organ", "NullTissue"…
            ParamNode      *params;
            struct ASTNode *body;
        } func;

        //  function call 
        struct {
            char    *name;
            ArgNode *args;
        } call;

        //  statement list
        struct {
            struct ASTNode *head;
            struct ASTNode *tail;
        } list;

    };

} ASTNode;


//   Constructor declarations

// Literals
ASTNode *make_int_lit   (int v, int line);
ASTNode *make_float_lit (float v, int line);
ASTNode *make_string_lit(char *s, int line);
ASTNode *make_ident     (char *name, int line);

// Operators
ASTNode *make_binop(int op, ASTNode *left, ASTNode *right, int line);
ASTNode *make_unop (int op, ASTNode *operand, int line);

// Declarations
ASTNode *make_decl(char *type, char *name,
                   int is_sealed, int is_nosample,
                   ASTNode *init, int line);

// Assignment
ASTNode *make_assign(char *name, ASTNode *expr, int line);

// Control flow
ASTNode *make_if       (ASTNode *cond, ASTNode *then_b,
                         ASTNode *else_b, int line);
ASTNode *make_while    (ASTNode *cond, ASTNode *body, int line);
ASTNode *make_do_while (ASTNode *body, ASTNode *cond, int line);
ASTNode *make_for      (ASTNode *init, ASTNode *cond,
                         ASTNode *update, ASTNode *body, int line);
ASTNode *make_range_loop(char *var, int from, int to,
                          ASTNode *body, int line);

/* Functions */
ASTNode  *make_func_def (char *ret_type, char *name,
                          ParamNode *params, ASTNode *body, int line);
ASTNode  *make_func_call(char *name, ArgNode *args, int line);
ParamNode *make_param   (char *type, char *name, ParamNode *next);
ArgNode   *make_arg     (char *label, ASTNode *expr, ArgNode *next);

/* Statements */
ASTNode *make_return  (ASTNode *expr, int line);
ASTNode *make_break   (int line);
ASTNode *make_continue(int line);
ASTNode *make_block   (ASTNode *stmts, int line);

/* Statement list */
ASTNode *make_stmt_list(ASTNode *head, ASTNode *tail);

/* Program root */
ASTNode *make_program(ASTNode *stmts);


#endif