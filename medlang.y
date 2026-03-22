%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtable.h"
#include "semantic.h"

void yyerror(const char *s);
int  yylex(void);
extern int lineno;

/* The root of the entire AST — set by the program rule */
ASTNode *ast_root = NULL;
%}

/* ============================================================
   Value types
   ============================================================ */
%union {
    int        ival;
    float      fval;
    char      *sval;
    ASTNode   *node;
    ParamNode *param;
    ArgNode   *arg;
}

/* ============================================================
   Token declarations (unchanged from Phase 1)
   ============================================================ */
%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL
%token <sval> STRING_LITERAL IDENTIFIER

%token ORGAN FLOW DIABETES CELL NULLTISSUE MAJORORGAN MINORORGAN NONPATHOLOGIC
%token SEALED NOSAMPLE PROTOCOL
%token DIAGNOSE ALTERNATE SCREENING RESULT IDIOPATHICCASE
%token TERMINATE FOLLOWUP DISCHARGE
%token CYCLE CONTINUOUS LOADINGDOSE
%token ADMISSION
%token PLUS MINUS MULTIPLY DIVIDE MOD
%token EQ NEQ GT LT GEQ LEQ
%token AND OR NOT
%token ASSIGN
%token SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE
%token RANGE_OP
%token PRESCRIBE DEFINE INCLUDE_HEADER
%token RECORD_KW OBSERVE_KW EXIT_KW
%token WARDALLOC FREEWARD SIZESCAN
%token POWER_FN ROOTCAUSE ABSDOSE ROUNDDOWN ROUNDUP
%token SINE COSINE TANGENT ISCRITICAL
%token RECORD_STRUCT INSTRUMENT TYPEALIAS DIAGNOSISLIST
%token SYNAPSE BIOPSY
%token IN_KW   /* "in" keyword for range loops */

/* ============================================================
   Non-terminal types
   ============================================================ */
%type <node>  program top_level_list top_level_item
%type <node>  var_decl sealed_var_decl nosample_decl
%type <node>  admission_func func_def
%type <node>  stmt_list stmt block
%type <node>  assign_stmt discharge_stmt
%type <node>  diagnose_stmt screening_stmt
%type <node>  cycle_stmt continuous_stmt loading_dose_stmt
%type <node>  observe_stmt record_stmt
%type <node>  terminate_stmt followup_stmt expr_stmt
%type <node>  expr
%type <node>  case_body case_item
%type <node>  for_init for_update
%type <node>  builtin_call user_call
%type <sval>  type_spec
%type <param> param_list param_list_ne param
%type <arg>   arg_list arg_list_ne arg named_arg

/* ============================================================
   Operator precedence (lowest → highest)
   ============================================================ */
%right ASSIGN
%left  OR
%left  AND
%left  EQ NEQ
%left  GT LT GEQ LEQ
%left  PLUS MINUS
%left  MULTIPLY DIVIDE MOD
%right NOT
%right UMINUS

%%

/* ============================================================
   Program root
   ============================================================ */

program
    : top_level_list
        {
            $$ = make_program($1);
            ast_root = $$;
            printf("[PARSE] Program parsed successfully.\n");
            print_ast(ast_root, 0);
        }
    | /* empty */
        {
            $$ = make_program(NULL);
            ast_root = $$;
            printf("[PARSE] Empty program.\n");
        }
    ;

top_level_list
    : top_level_item
        { $$ = make_stmt_list($1, NULL); }
    | top_level_list top_level_item
        { $$ = make_stmt_list($1, $2); }
    ;

top_level_item
    : var_decl        { $$ = $1; }
    | sealed_var_decl { $$ = $1; }
    | nosample_decl   { $$ = $1; }
    | admission_func  { $$ = $1; }
    | func_def        { $$ = $1; }
    ;

/* ============================================================
   Data type — returns the keyword string for the decl node
   ============================================================ */

type_spec
    : ORGAN         { $$ = "Organ";         }
    | FLOW          { $$ = "Flow";           }
    | DIABETES      { $$ = "Diabetes";       }
    | CELL          { $$ = "Cell";           }
    | NULLTISSUE    { $$ = "NullTissue";     }
    | MAJORORGAN    { $$ = "MajorOrgan";     }
    | MINORORGAN    { $$ = "MinorOrgan";     }
    | NONPATHOLOGIC { $$ = "NonPathologic";  }
    ;

/* ============================================================
   Variable declarations
   ============================================================ */

var_decl
    : type_spec IDENTIFIER SEMICOLON
        { $$ = make_decl($1, $2, 0, 0, NULL, lineno); }
    | type_spec IDENTIFIER ASSIGN expr SEMICOLON
        { $$ = make_decl($1, $2, 0, 0, $4, lineno); }
    ;

sealed_var_decl
    : SEALED type_spec IDENTIFIER ASSIGN expr SEMICOLON
        { $$ = make_decl($2, $3, 1, 0, $5, lineno); }
    | SEALED type_spec IDENTIFIER SEMICOLON
        { $$ = make_decl($2, $3, 1, 0, NULL, lineno); }
    ;

nosample_decl
    : NOSAMPLE type_spec IDENTIFIER SEMICOLON
        { $$ = make_decl($2, $3, 0, 1, NULL, lineno); }
    | NOSAMPLE type_spec IDENTIFIER ASSIGN expr SEMICOLON
        { $$ = make_decl($2, $3, 0, 1, $5, lineno); }
    ;

/* ============================================================
   Admission() — program entry point
   ============================================================ */

admission_func
    : ADMISSION LPAREN param_list RPAREN LBRACE stmt_list RBRACE
        { $$ = make_func_def("NullTissue", "Admission", $3, $6, lineno); }
    | ADMISSION LPAREN param_list RPAREN LBRACE RBRACE
        { $$ = make_func_def("NullTissue", "Admission", $3, NULL, lineno); }
    ;

/* ============================================================
   User-defined function:  type name <: params :> [: body :]
   ============================================================ */

func_def
    : type_spec IDENTIFIER LPAREN param_list RPAREN LBRACE stmt_list RBRACE
        { $$ = make_func_def($1, $2, $4, $7, lineno); }
    | type_spec IDENTIFIER LPAREN param_list RPAREN LBRACE RBRACE
        { $$ = make_func_def($1, $2, $4, NULL, lineno); }
    ;

/* ============================================================
   Parameter list
   ============================================================ */

param_list
    : /* empty */    { $$ = NULL; }
    | param_list_ne  { $$ = $1; }
    ;

param_list_ne
    : param
        { $$ = $1; }
    | param_list_ne COMMA param
        { /* append $3 to end of $1 */
          ParamNode *p = $1;
          while (p->next) p = p->next;
          p->next = $3;
          $$ = $1;
        }
    ;

param
    : type_spec IDENTIFIER
        { $$ = make_param($1, $2, NULL); }
    ;

/* ============================================================
   Statement list
   ============================================================ */

stmt_list
    : stmt
        { $$ = make_stmt_list($1, NULL); }
    | stmt_list stmt
        { $$ = make_stmt_list($1, $2); }
    ;

stmt
    : assign_stmt       { $$ = $1; }
    | discharge_stmt    { $$ = $1; }
    | diagnose_stmt     { $$ = $1; }
    | screening_stmt    { $$ = $1; }
    | cycle_stmt        { $$ = $1; }
    | continuous_stmt   { $$ = $1; }
    | loading_dose_stmt { $$ = $1; }
    | observe_stmt      { $$ = $1; }
    | record_stmt       { $$ = $1; }
    | terminate_stmt    { $$ = $1; }
    | followup_stmt     { $$ = $1; }
    | var_decl          { $$ = $1; }
    | sealed_var_decl   { $$ = $1; }
    | nosample_decl     { $$ = $1; }
    | block             { $$ = $1; }
    | expr_stmt         { $$ = $1; }
    /* --- error recovery: skip to next | and continue --- */
    | error SEMICOLON
        {
            yyerrok;
            $$ = NULL;
            fprintf(stderr,
                "[MedLang] Syntax error near line %d, resuming after '|'\n",
                lineno);
        }
    ;

/* ============================================================
   Block  [: stmt_list :]
   ============================================================ */

block
    : LBRACE stmt_list RBRACE
        { $$ = make_block($2, lineno); }
    | LBRACE RBRACE
        { $$ = make_block(NULL, lineno); }
    ;

/* ============================================================
   Assignment:  heartRate =: 72 |
   ============================================================ */

assign_stmt
    : IDENTIFIER ASSIGN expr SEMICOLON
        { $$ = make_assign($1, $3, lineno); }
    ;

/* ============================================================
   Discharge (return)
   ============================================================ */

discharge_stmt
    : DISCHARGE expr SEMICOLON
        { $$ = make_return($2, lineno); }
    | DISCHARGE SEMICOLON
        { $$ = make_return(NULL, lineno); }
    ;

/* ============================================================
   Diagnose / Alternate  (if / else)
   ============================================================ */

diagnose_stmt
    : DIAGNOSE LPAREN expr RPAREN block
        { $$ = make_if($3, $5, NULL, lineno); }
    | DIAGNOSE LPAREN expr RPAREN block ALTERNATE block
        { $$ = make_if($3, $5, $7, lineno); }
    | DIAGNOSE LPAREN expr RPAREN block ALTERNATE diagnose_stmt
        { $$ = make_if($3, $5, $7, lineno); }
    ;

/* ============================================================
   Screening / Result / IdiopathicCase  (switch/case/default)
   Uses a plain block node for the body; semantic phase handles cases
   ============================================================ */

screening_stmt
    : SCREENING LPAREN expr RPAREN LBRACE case_body RBRACE
        { $$ = make_if($3, $6, NULL, lineno); /* placeholder */ }
    ;

case_body
    : /* empty */   { $$ = NULL; }
    | case_body case_item { $$ = make_stmt_list($1, $2); }
    ;

case_item
    : RESULT expr SEMICOLON stmt_list
        { $$ = make_stmt_list($2, $4); }
    | IDIOPATHICCASE SEMICOLON stmt_list
        { $$ = $3; }
    ;

/* ============================================================
   Cycle  (for)
   Classic:    Cycle <: init | cond | update :> [: body :]
   Range-based: Cycle <: i in 1..10 :> [: body :]  (Section 6.5)
   ============================================================ */

cycle_stmt
    /* classic 3-part for */
    : CYCLE LPAREN for_init SEMICOLON expr SEMICOLON for_update RPAREN block
        { $$ = make_for($3, $5, $7, $9, lineno); }
    /* range-based: Cycle <: IDENT in INT_LIT .. INT_LIT :> block */
    | CYCLE LPAREN IDENTIFIER IN_KW INT_LITERAL RANGE_OP INT_LITERAL RPAREN block
        { $$ = make_range_loop($3, $5, $7, $9, lineno); }
    ;

for_init
    : /* empty */
        { $$ = NULL; }
    | IDENTIFIER ASSIGN expr
        { $$ = make_assign($1, $3, lineno); }
    | type_spec IDENTIFIER ASSIGN expr
        { $$ = make_decl($1, $2, 0, 0, $4, lineno); }
    | type_spec IDENTIFIER
        { $$ = make_decl($1, $2, 0, 0, NULL, lineno); }
    ;

for_update
    : /* empty */
        { $$ = NULL; }
    | IDENTIFIER ASSIGN expr
        { $$ = make_assign($1, $3, lineno); }
    ;

/* ============================================================
   Continuous (while)
   ============================================================ */

continuous_stmt
    : CONTINUOUS LPAREN expr RPAREN block
        { $$ = make_while($3, $5, lineno); }
    ;

/* ============================================================
   LoadingDose (do-while)
   LoadingDose [: body :] Continuous <: cond :> |
   ============================================================ */

loading_dose_stmt
    : LOADINGDOSE block CONTINUOUS LPAREN expr RPAREN SEMICOLON
        { $$ = make_do_while($2, $5, lineno); }
    ;

/* ============================================================
   Observe (printf) and Record (scanf)
   ============================================================ */

observe_stmt
    : OBSERVE_KW LPAREN arg_list RPAREN SEMICOLON
        { $$ = make_func_call("Observe", $3, lineno); }
    ;

record_stmt
    : RECORD_KW LPAREN arg_list RPAREN SEMICOLON
        { $$ = make_func_call("Record", $3, lineno); }
    ;

/* ============================================================
   Argument lists (positional and named)
   ============================================================ */

arg_list
    : /* empty */    { $$ = NULL; }
    | arg_list_ne    { $$ = $1; }
    ;

arg_list_ne
    : arg
        { $$ = $1; }
    | arg_list_ne COMMA arg
        { /* append $3 */
          ArgNode *a = $1;
          while (a->next) a = a->next;
          a->next = $3;
          $$ = $1;
        }
    ;

arg
    : named_arg  { $$ = $1; }
    ;

named_arg
    /* named:     patient: expr  */
    : IDENTIFIER SEMICOLON expr
        { $$ = make_arg($1, $3, NULL); }
    /* positional */
    | expr
        { $$ = make_arg(NULL, $1, NULL); }
    ;

/* ============================================================
   Terminate (break) and FollowUp (continue)
   ============================================================ */

terminate_stmt
    : TERMINATE SEMICOLON
        { $$ = make_break(lineno); }
    ;

followup_stmt
    : FOLLOWUP SEMICOLON
        { $$ = make_continue(lineno); }
    ;

/* ============================================================
   Expression statement
   ============================================================ */

expr_stmt
    : expr SEMICOLON
        { $$ = $1; }
    ;

/* ============================================================
   Expressions
   ============================================================ */

expr
    : expr PLUS     expr  { $$ = make_binop(PLUS,     $1, $3, lineno); }
    | expr MINUS    expr  { $$ = make_binop(MINUS,    $1, $3, lineno); }
    | expr MULTIPLY expr  { $$ = make_binop(MULTIPLY, $1, $3, lineno); }
    | expr DIVIDE   expr  { $$ = make_binop(DIVIDE,   $1, $3, lineno); }
    | expr MOD      expr  { $$ = make_binop(MOD,      $1, $3, lineno); }
    | expr EQ       expr  { $$ = make_binop(EQ,       $1, $3, lineno); }
    | expr NEQ      expr  { $$ = make_binop(NEQ,      $1, $3, lineno); }
    | expr GT       expr  { $$ = make_binop(GT,       $1, $3, lineno); }
    | expr LT       expr  { $$ = make_binop(LT,       $1, $3, lineno); }
    | expr GEQ      expr  { $$ = make_binop(GEQ,      $1, $3, lineno); }
    | expr LEQ      expr  { $$ = make_binop(LEQ,      $1, $3, lineno); }
    | expr AND      expr  { $$ = make_binop(AND,      $1, $3, lineno); }
    | expr OR       expr  { $$ = make_binop(OR,       $1, $3, lineno); }
    | NOT expr            { $$ = make_unop(NOT,   $2, lineno); }
    | MINUS expr %prec UMINUS
                          { $$ = make_unop(MINUS, $2, lineno); }
    | LPAREN expr RPAREN  { $$ = $2; }
    | INT_LITERAL         { $$ = make_int_lit($1, lineno); }
    | FLOAT_LITERAL       { $$ = make_float_lit($1, lineno); }
    | STRING_LITERAL      { $$ = make_string_lit($1, lineno); }
    | IDENTIFIER          { $$ = make_ident($1, lineno); }
    | builtin_call        { $$ = $1; }
    | user_call           { $$ = $1; }
    | NOSAMPLE            { $$ = make_int_lit(0, lineno); }
    ;

/* ============================================================
   Built-in function calls
   ============================================================ */

builtin_call
    : POWER_FN   LPAREN arg_list RPAREN { $$ = make_func_call("Power",     $3, lineno); }
    | ROOTCAUSE  LPAREN arg_list RPAREN { $$ = make_func_call("RootCause", $3, lineno); }
    | ABSDOSE    LPAREN arg_list RPAREN { $$ = make_func_call("AbsDose",   $3, lineno); }
    | ROUNDDOWN  LPAREN arg_list RPAREN { $$ = make_func_call("RoundDown", $3, lineno); }
    | ROUNDUP    LPAREN arg_list RPAREN { $$ = make_func_call("RoundUp",   $3, lineno); }
    | SINE       LPAREN arg_list RPAREN { $$ = make_func_call("Sine",      $3, lineno); }
    | COSINE     LPAREN arg_list RPAREN { $$ = make_func_call("Cosine",    $3, lineno); }
    | TANGENT    LPAREN arg_list RPAREN { $$ = make_func_call("Tangent",   $3, lineno); }
    | ISCRITICAL LPAREN arg_list RPAREN { $$ = make_func_call("IsCritical",$3, lineno); }
    ;

/* ============================================================
   User-defined function calls
   ============================================================ */

user_call
    : IDENTIFIER LPAREN arg_list RPAREN
        { $$ = make_func_call($1, $3, lineno); }
    ;

%%

/* ============================================================
   Error handler
   ============================================================ */
void yyerror(const char *s) {
    fprintf(stderr, "[MedLang Error] Line %d: %s\n", lineno, s);
}

/* ============================================================
   main
   ============================================================ */
int main(int argc, char **argv) {
    extern FILE *yyin;
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Cannot open file: %s\n", argv[1]);
            return 1;
        }
    }

    int parse_result = yyparse();
    if (parse_result != 0)
        return parse_result;

    printf("[MedLang] Parse completed successfully.\n");

    /* --- Phase 3: Semantic Analysis --- */
    if (ast_root) {
        int sem_result = analyze_program(ast_root);
        if (sem_result != 0)
            return sem_result;
    }

    return 0;
}