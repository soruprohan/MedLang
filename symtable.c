/* symtable.c — MedLang Symbol Table implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"

/* ============================================================
   scope_new — allocate a fresh scope with a given parent
   ============================================================ */
Scope *scope_new(Scope *parent) {
    Scope *s = (Scope *)malloc(sizeof(Scope));
    if (!s) { fprintf(stderr, "[symtable] out of memory\n"); exit(1); }
    s->symbols = NULL;
    s->parent  = parent;
    return s;
}

/* ============================================================
   scope_free — release only this scope's symbols (not parents)
   ============================================================ */
void scope_free(Scope *s) {
    if (!s) return;
    Symbol *cur = s->symbols;
    while (cur) {
        Symbol *nxt = cur->next;
        free(cur->name);
        free(cur->type);
        free(cur);
        cur = nxt;
    }
    free(s);
}

/* ============================================================
   scope_lookup_local — search current scope only
   ============================================================ */
Symbol *scope_lookup_local(Scope *s, const char *name) {
    if (!s) return NULL;
    for (Symbol *sym = s->symbols; sym; sym = sym->next)
        if (strcmp(sym->name, name) == 0)
            return sym;
    return NULL;
}

/* ============================================================
   scope_lookup — walk the scope chain upward
   ============================================================ */
Symbol *scope_lookup(Scope *s, const char *name) {
    for (Scope *cur = s; cur; cur = cur->parent) {
        Symbol *sym = scope_lookup_local(cur, name);
        if (sym) return sym;
    }
    return NULL;
}

/* ============================================================
   scope_add — add a new symbol to THIS scope
   Returns  0  on success
   Returns -1  if the name already exists in THIS scope
   ============================================================ */
int scope_add(Scope *s, const char *name, const char *type,
              int is_sealed, int is_nosample, int lineno) {
    if (scope_lookup_local(s, name))
        return -1;  /* double declaration */

    Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!sym) { fprintf(stderr, "[symtable] out of memory\n"); exit(1); }

    sym->name        = strdup(name);
    sym->type        = strdup(type);
    sym->is_sealed   = is_sealed;
    sym->is_nosample = is_nosample;
    sym->initialized = 0;
    sym->lineno      = lineno;
    sym->next        = s->symbols; //these two lines make sure that the new symbol is added to the front of the linked list of symbols in this scope
    s->symbols       = sym;         //
    return 0;
}

/* ============================================================
   scope_mark_init — flip the initialized flag
   ============================================================ */
void scope_mark_init(Scope *s, const char *name) {
    Symbol *sym = scope_lookup(s, name);
    if (sym) sym->initialized = 1;
}