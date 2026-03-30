
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symtable.h"

extern int sem_error_count;
extern int sem_warn_count;


int analyze_program(ASTNode *root);

#endif 