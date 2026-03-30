
#ifndef SYMTABLE_H
#define SYMTABLE_H


  // A single symbol entry
   
typedef struct Symbol {
    char          *name;
    char          *type;        // "Organ", "Flow", "Diabetes",
                                   // "Cell", "NullTissue", etc.
    int            is_sealed;   // 1 = Sealed (immutable)
    int            is_nosample; // 1 = NoSample (nullable)
    int            initialized; // 1 = has been assigned a value
    int            lineno;      // line where declared
    struct Symbol *next;        // next in this scope's chain
} Symbol;


  // A lexical scope (linked stack: child → parent)
   
typedef struct Scope {
    Symbol       *symbols;
    struct Scope *parent;
} Scope;

//  Scope operations 
Scope  *scope_new   (Scope *parent);
void    scope_free  (Scope *s);          // frees only THIS scope

// Add a symbol to the CURRENT scope.
// Returns 0 on success, -1 if already declared in this scope.
int     scope_add   (Scope *s,
                     const char *name, const char *type,
                     int is_sealed, int is_nosample, int lineno);

// Walk the scope chain upward — returns NULL if not found.
Symbol *scope_lookup(Scope *s, const char *name);

// Look in the CURRENT scope only (for double-declaration check).
Symbol *scope_lookup_local(Scope *s, const char *name);

// Mark a symbol as initialized (after assignment).
void    scope_mark_init(Scope *s, const char *name);

#endif