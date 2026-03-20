%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(const char *s);
int yylex(void);
%}

%union {
    int    ival;
    float  fval;
    char  *sval;
}

%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL
%token <sval> STRING_LITERAL IDENTIFIER

/* --- Data type tokens --- */
%token ORGAN FLOW DIABETES CELL NULLTISSUE MAJORORGAN MINORORGAN NONPATHOLOGIC

/* --- Unique feature tokens --- */
%token SEALED NOSAMPLE PROTOCOL

/* --- Control flow tokens --- */
%token DIAGNOSE ALTERNATE SCREENING RESULT IDIOPATHICCASE
%token TERMINATE FOLLOWUP DISCHARGE

/* --- Loop tokens --- */
%token CYCLE CONTINUOUS LOADINGDOSE

/* --- Entry point --- */
%token ADMISSION

/* --- Operator tokens --- */
%token PLUS MINUS MULTIPLY DIVIDE MOD
%token EQ NEQ GT LT GEQ LEQ
%token AND OR NOT
%token ASSIGN

/* --- Delimiter tokens --- */
%token SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE
%token RANGE_OP

/* --- Preprocessor tokens --- */
%token PRESCRIBE DEFINE INCLUDE_HEADER

/* --- I/O tokens --- */
%token RECORD_KW OBSERVE_KW EXIT_KW

/* --- Memory tokens --- */
%token WARDALLOC FREEWARD SIZESCAN

/* --- Math function tokens --- */
%token POWER_FN ROOTCAUSE ABSDOSE ROUNDDOWN ROUNDUP
%token SINE COSINE TANGENT ISCRITICAL

/* --- Struct/enum tokens --- */
%token RECORD_STRUCT INSTRUMENT TYPEALIAS DIAGNOSISLIST

/* --- Pointer tokens --- */
%token SYNAPSE BIOPSY

%%

program:
    /* empty */
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "[MedLang Error] %s\n", s);
}