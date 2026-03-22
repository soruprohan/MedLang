/* semantic.h — MedLang Semantic Analysis
*/

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symtable.h"

/* ============================================================
   Error / warning counters (read after analyze_program())
   ============================================================ */
extern int sem_error_count;
extern int sem_warn_count;

/* ============================================================
   Public entry point
   Call this after a successful yyparse() with the AST root.
   Returns 0 if no errors were found, non-zero otherwise.
   ============================================================ */
int analyze_program(ASTNode *root);

#endif /* SEMANTIC_H */