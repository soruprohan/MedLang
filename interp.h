/* interp.h — MedLang Phase 5: AST Interpreter
   Walks the AST produced by Phase 2 and executes the program directly,
   producing real runtime output (printf/scanf, return values, etc.)
*/

#ifndef INTERP_H
#define INTERP_H

#include "ast.h"

/* ============================================================
   Public entry point.
   Call this after tac_free_all() in main().
   Finds the Admission function in the AST and executes it.
   Returns 0 on success, 1 on runtime error.
   ============================================================ */
int interp_run(ASTNode *root);

#endif /* INTERP_H */