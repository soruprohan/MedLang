/* tac.h — MedLang Three-Address Code (TAC) definitions
   Phase 4: Intermediate Code Generation

   Each TAC instruction has the form:
       result = arg1  op  arg2
   where any field may be NULL when unused.

   The full list of instructions is emitted to stdout and also
   written to  output.tac  so the grader has a tangible artifact.
*/

#ifndef TAC_H
#define TAC_H

#include <stdio.h>
#include "ast.h"

/* ============================================================
   Opcodes — one per TAC instruction kind
   ============================================================ */
typedef enum {
    TAC_ASSIGN,       /*  result = arg1                         */
    TAC_BINOP,        /*  result = arg1  op  arg2               */
    TAC_UNOP,         /*  result = op arg1                      */
    TAC_LABEL,        /*  result:                               */
    TAC_GOTO,         /*  goto arg1                             */
    TAC_IF_GOTO,      /*  if arg1 goto arg2                     */
    TAC_IFNOT_GOTO,   /*  ifnot arg1 goto arg2                  */
    TAC_PARAM,        /*  param arg1                            */
    TAC_CALL,         /*  result = call arg1, arg2(=n_args)     */
    TAC_RETURN,       /*  return arg1   (arg1 may be NULL)      */
    TAC_BEGIN_FUNC,   /*  begin_func arg1                       */
    TAC_END_FUNC      /*  end_func                              */
} TACOp;

/* ============================================================
   A single TAC instruction node (singly-linked list)
   ============================================================ */
typedef struct TACInstr {
    TACOp           op;
    char           *result;   /* destination / label name       */
    char           *arg1;     /* first operand / callee name    */
    char           *arg2;     /* second operand / operator sym  */
    struct TACInstr *next;
} TACInstr;

/* ============================================================
   Public API
   ============================================================ */

/* Allocate a fresh temp name: "t0", "t1", … (heap-allocated) */
char *tac_new_temp(void);

/* Allocate a fresh label name: "L0", "L1", … (heap-allocated) */
char *tac_new_label(void);

/* Append one instruction to the global TAC list.
   All string arguments are strdup'd — caller may free its copy. */
void tac_emit(TACOp op,
              const char *result,
              const char *arg1,
              const char *arg2);

/* Walk the global TAC list and print every instruction.
   Writes to both stdout and the file  output.tac. */
void tac_print_all(void);

/* Free the entire global TAC list (call at program exit). */
void tac_free_all(void);

/* Walk the AST and emit TAC for the entire program.
   Call this after a successful analyze_program(). */
void tac_gen_program(ASTNode *root);

#endif /* TAC_H */