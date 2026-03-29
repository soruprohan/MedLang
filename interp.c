/* interp.c -AST Interpreter
   Executes the program directly from the AST.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ast.h"
#include "interp.h"
#include "medlang.tab.h" 

/* ================================================================
   Runtime value: numeric (double) or string
   ================================================================ */
typedef struct { int is_str; double num; char *str; } Val;

static Val vnum(double d)  { Val v; v.is_str=0; v.num=d; v.str=NULL; return v; }
static Val vstr(char *s)   { Val v; v.is_str=1; v.num=0; v.str=s;    return v; }
static Val vzero(void)     { return vnum(0); }
static long vlong(Val v)   { return (long)v.num; }

/* ================================================================
   Runtime variable store (scoped)
   ================================================================ */
typedef struct Var { char *name; Val val; int sealed; struct Var *next; } Var;
typedef struct Env { Var *vars; struct Env *parent; } Env;

//env_push — Enter/create a new scope
static Env *env_push(Env *p) {
    Env *e = calloc(1, sizeof(Env)); e->parent = p; return e;
}
//env_pop — Exit a scope, freeing all variables in it
static void env_pop(Env *e) {
    for (Var *v = e->vars, *n; v; v = n) { n=v->next; free(v->name); free(v); }
    free(e);
}
//env_set — Declare a variable
static void env_set(Env *e, const char *name, Val val, int sealed) {
    Var *v = calloc(1, sizeof(Var));
    v->name = strdup(name); v->val = val; v->sealed = sealed;
    v->next = e->vars; e->vars = v;
}
//env_find — Look up a variable
static Var *env_find(Env *e, const char *name) {
    for (Env *c = e; c; c = c->parent)
        for (Var *v = c->vars; v; v = v->next)
            if (strcmp(v->name, name) == 0) return v;
    return NULL;
}

/* ================================================================
   Function table
   ================================================================ */
#define MAX_FUNCS 128
static struct { char *name; ASTNode *def; } ftab[MAX_FUNCS]; //an array of function names and their ASTNode definitions
static int fcount = 0;

//freg — Register a function
static void freg(ASTNode *def) {
    if (fcount < MAX_FUNCS) { ftab[fcount].name=def->func.name; ftab[fcount++].def=def; }
}

//flookup — Find a function by name
static ASTNode *flookup(const char *name) {
    for (int i=0; i<fcount; i++) if (strcmp(ftab[i].name,name)==0) return ftab[i].def;
    return NULL;
}

//This recursively walks the entire AST at startup to find and register all function definitions before any code runs
static void collect_funcs(ASTNode *n) {
    if (!n) return;
    if (n->type==NODE_STMT_LIST) { collect_funcs(n->list.head); collect_funcs(n->list.tail); return; }
    if (n->type==NODE_FUNC_DEF) freg(n);
}

/* ================================================================
   Signal (break / continue / return propagation)
   ================================================================ */
typedef enum { SIG_NONE, SIG_BREAK, SIG_CONTINUE, SIG_RETURN } Sig;
typedef struct { Sig sig; Val val; } Res;

#define R_NONE      ((Res){SIG_NONE,     vzero()})
#define R_BREAK     ((Res){SIG_BREAK,    vzero()})
#define R_CONTINUE  ((Res){SIG_CONTINUE, vzero()})
#define R_RETURN(v) ((Res){SIG_RETURN,   (v)    })

/* ================================================================
   Forward declarations
   ================================================================ */
static Val eval (ASTNode *n, Env *e);
static Res exec (ASTNode *n, Env *e);
static Res stmts(ASTNode *n, Env *e);

/* ================================================================
   Print a string processing backslash escape sequences.
   (The lexer strips quotes but leaves \n etc. as two chars.)
   ================================================================ */
static void print_esc(const char *s) {
    for (; *s; s++) {
        if (*s=='\\' && s[1]) { 
            switch (*++s) {
                case 'n':  putchar('\n'); break;   // newline
                case 't':  putchar('\t'); break;   // tab
                case 'r':  putchar('\r'); break;   // carriage return
                case '\\': putchar('\\'); break;   // literal backslash
                case '"':  putchar('"');  break;   // literal quote
                default:   putchar(*s);   break;   // unknown — just print as-is
            }
        } else putchar(*s);   //for all the non backlash cases, just print the character as is
    }
}

/* ================================================================
   Observe (printf): first arg is format string or bare value.
   ================================================================ */
static void do_observe(ASTNode *n, Env *e) {  //here a function call node is passed in
    ArgNode *a = n->call.args;
    if (!a) return;
    Val first = eval(a->expr, e);
    if (!first.is_str) { printf("%g", first.num); return; }

    const char *p = first.str;
    ArgNode *rest = a->next;
    for (; *p; p++) {
        if (*p=='\\' && p[1]) {
            switch (*++p) {
                case 'n': putchar('\n'); break;
                case 't': putchar('\t'); break;
                case 'r': putchar('\r'); break; 
                case '\\': putchar('\\'); break;
                case '"': putchar('"');  break; 
                default: putchar(*p); break;
            }
            continue;
        }
        if (*p=='%' && p[1] && rest) {
            Val v = eval(rest->expr, e); rest=rest->next; p++;
            switch (*p) {
                case 'd': case 'i': printf("%ld",(long)v.num); break;
                case 'f': printf("%f", v.num); break;
                case 'g': printf("%g", v.num); break;
                case 'e': printf("%e", v.num); break;
                case 'c': printf("%c", (int)v.num); break;
                case 's': if(v.is_str) print_esc(v.str); else printf("%g",v.num); break;
                case '%': putchar('%'); break;
                default:  putchar('%'); putchar(*p); break;
            }
            continue;
        }
        putchar(*p);
    }
}

/* ================================================================
   Record (scanf): first arg is format string, rest are var names.
   ================================================================ */
static void do_record(ASTNode *n, Env *e) {
    ArgNode *a = n->call.args;
    if (!a) return;
    Val fmt = eval(a->expr, e);
    if (!fmt.is_str) return;
    ArgNode *rest = a->next;
    for (const char *p = fmt.str; *p && rest; p++) {
        if (*p != '%') continue;
        p++;
        if (!*p) break;
        ASTNode *ex = rest->expr; rest = rest->next;
        if (!ex || ex->type != NODE_IDENT) continue; //only identifiers can be passed to Record for assignment, if it's not an identifier just skip it and move on to the next one
        Var *var = env_find(e, ex->sval); //find the variable in scope
        if (!var) continue;
        switch (*p) {
            case 'd': case 'i': { long t;   if(scanf("%ld",&t)==1)  var->val=vnum(t); break; }
            case 'f': case 'g': { double t; if(scanf("%lf",&t)==1)  var->val=vnum(t); break; }
            case 'c':           { char t;   if(scanf(" %c",&t)==1)  var->val=vnum(t); break; }
            case 's':           { char buf[512]; if(scanf("%511s",buf)==1) var->val=vstr(strdup(buf)); break; }
        }
    }
}

/* ================================================================
   Expression evaluator
   ================================================================ */
static Val eval(ASTNode *n, Env *e) {
    if (!n) return vzero();
    switch (n->type) {
        case NODE_INT_LIT:    return vnum(n->ival);
        case NODE_FLOAT_LIT:  return vnum(n->fval);
        case NODE_STRING_LIT: return vstr(n->sval);

        case NODE_IDENT: {
            Var *v = env_find(e, n->sval);
            return v ? v->val : vzero();
        }

        case NODE_UNOP: {
            Val op = eval(n->binop.left, e);
            if (n->binop.op == NOT)   return vnum(!vlong(op));
            if (n->binop.op == MINUS) return vnum(-op.num);
            return op;
        }

        case NODE_BINOP: {
            if (n->binop.op == AND) {
                if (!vlong(eval(n->binop.left, e))) return vnum(0);
                return vnum(!!vlong(eval(n->binop.right, e)));
            }
            if (n->binop.op == OR) {
                if (vlong(eval(n->binop.left, e))) return vnum(1);
                return vnum(!!vlong(eval(n->binop.right, e)));
            }
            double l = eval(n->binop.left,  e).num;
            double r = eval(n->binop.right, e).num;
            switch (n->binop.op) {
                case PLUS:     return vnum(l + r);
                case MINUS:    return vnum(l - r);
                case MULTIPLY: return vnum(l * r);
                case DIVIDE:   if(r==0){fprintf(stderr,"[interp] div by zero\n");return vzero();} return vnum(l/r);
                case MOD:      if(r==0){fprintf(stderr,"[interp] mod by zero\n");return vzero();} return vnum((long)l%(long)r);
                case EQ:       return vnum(l == r);
                case NEQ:      return vnum(l != r);
                case GT:       return vnum(l >  r);
                case LT:       return vnum(l <  r);
                case GEQ:      return vnum(l >= r);
                case LEQ:      return vnum(l <= r);
                default:       return vzero();
            }
        }

        case NODE_FUNC_CALL: {
            const char *nm = n->call.name;
            ArgNode *a = n->call.args;
            #define A1 (a ? eval(a->expr,e).num : 0)
            #define A2 (a&&a->next ? eval(a->next->expr,e).num : 0)
            if (!strcmp(nm,"Power"))      return vnum(pow(A1,A2));
            if (!strcmp(nm,"RootCause"))  return vnum(sqrt(A1));
            if (!strcmp(nm,"AbsDose"))    return vnum(fabs(A1));
            if (!strcmp(nm,"RoundDown"))  return vnum(floor(A1));
            if (!strcmp(nm,"RoundUp"))    return vnum(ceil(A1));
            if (!strcmp(nm,"Sine"))       return vnum(sin(A1));
            if (!strcmp(nm,"Cosine"))     return vnum(cos(A1));
            if (!strcmp(nm,"Tangent"))    return vnum(tan(A1));
            if (!strcmp(nm,"IsCritical")) return vnum(A1>140||A2>90 ? 1 : 0);
            #undef A1
            #undef A2
            if (!strcmp(nm,"Observe")||!strcmp(nm,"Record")) { exec(n,e); return vzero(); }
            /* User-defined function */
            ASTNode *def = flookup(nm);
            if (!def) { fprintf(stderr,"[interp] undefined function '%s'\n",nm); return vzero(); }
            Env *global = e; while (global->parent) global = global->parent;
            Env *fs = env_push(global);
            ParamNode *pm = def->func.params;
            ArgNode   *ag = n->call.args;

            //Bind Arguments to Parameters
            for (; pm && ag; pm=pm->next, ag=ag->next)
            //global scope e caller er local args calculate kore called function er jonno global scope e value gula store kora
                env_set(fs, pm->name, eval(ag->expr,e), 0);
              //If the caller passed fewer arguments than parameters
              // but foo expects two params, the remaining parameters are initialized to zero instead of crashing.
              // A safety measure for mismatched argument counts.  
            for (; pm; pm=pm->next) env_set(fs, pm->name, vzero(), 0);

            Res r = stmts(def->func.body, fs);
            env_pop(fs);
            return r.sig==SIG_RETURN ? r.val : vzero();
        }

        default: return vzero();
    }
}

/* ================================================================
   Statement list walker (left-recursive NODE_STMT_LIST)
   ================================================================ */
static Res stmts(ASTNode *n, Env *e) {
    if (!n) return R_NONE;
    if (n->type == NODE_STMT_LIST) {
        Res r = stmts(n->list.head, e); //  recurse LEFT (deep) first
        //means break or continue or return signal up the chain without executing the rest of the statements
        if (r.sig != SIG_NONE) return r; //early exit if return/break
        return n->list.tail ? exec(n->list.tail, e) : R_NONE; //then execute RIGHT (newest)
    }
    return exec(n, e); //if anything other than a statement list node is passed in, just execute it
}

/* ================================================================
   Statement executor
   ================================================================ */
static Res exec(ASTNode *n, Env *e) {
    if (!n) return R_NONE;
    switch (n->type) {

        case NODE_PROGRAM:   return stmts(n->binop.left, e);
        case NODE_STMT_LIST: return stmts(n, e);

        case NODE_BLOCK: {
            Env *b = env_push(e); Res r = stmts(n->binop.left, b); env_pop(b); return r;
        }

        case NODE_DECL: {
            Val v = n->decl.init ? eval(n->decl.init, e) : vzero();
            env_set(e, n->decl.name, v, n->decl.is_sealed);
            return R_NONE;
        }

        case NODE_ASSIGN: {
            Var *v = env_find(e, n->assign.name);
            if (!v)        { fprintf(stderr,"[interp] undeclared '%s'\n",n->assign.name); return R_NONE; }
            if (v->sealed) { fprintf(stderr,"[interp] Sealed '%s'\n",n->assign.name);     return R_NONE; }
            v->val = eval(n->assign.expr, e);
            return R_NONE;
        }

        case NODE_RETURN:   return R_RETURN(n->binop.left ? eval(n->binop.left,e) : vzero());
        case NODE_BREAK:    return R_BREAK;
        case NODE_CONTINUE: return R_CONTINUE;

        case NODE_IF:
            if (vlong(eval(n->ifnode.cond, e))) return exec(n->ifnode.then_block, e);
            return n->ifnode.else_block ? exec(n->ifnode.else_block, e) : R_NONE;

        case NODE_WHILE:
            while (vlong(eval(n->loop.cond, e))) {
                Res r = exec(n->loop.body, e);
                if (r.sig==SIG_BREAK)  return R_NONE;
                if (r.sig==SIG_RETURN) return r;
            }
            return R_NONE;

        case NODE_DO_WHILE:
            do {
                Res r = exec(n->loop.body, e);
                if (r.sig==SIG_BREAK)  return R_NONE;
                if (r.sig==SIG_RETURN) return r;
            } while (vlong(eval(n->loop.cond, e)));
            return R_NONE;

        case NODE_FOR:
            if (n->forloop.init) exec(n->forloop.init, e);
            while (!n->forloop.cond || vlong(eval(n->forloop.cond, e))) {
                Res r = exec(n->forloop.body, e);
                if (r.sig==SIG_BREAK)  return R_NONE;
                if (r.sig==SIG_RETURN) return r;
                if (n->forloop.update) exec(n->forloop.update, e);
            }
            return R_NONE;

        case NODE_FOR_RANGE: {
            Env *re = env_push(e);
            env_set(re, n->range_loop.var, vnum(n->range_loop.from), 0);
            Var *lv = env_find(re, n->range_loop.var);
            for (long i=n->range_loop.from; i<=n->range_loop.to; i++) {
                lv->val = vnum(i);
                Res r = exec(n->range_loop.body, re);
                if (r.sig==SIG_BREAK)  { env_pop(re); return R_NONE; }
                if (r.sig==SIG_RETURN) { env_pop(re); return r; }
            }
            env_pop(re); return R_NONE;
        }

        case NODE_FUNC_DEF: return R_NONE;

        case NODE_FUNC_CALL:
            if (!strcmp(n->call.name,"Observe")) { do_observe(n,e); return R_NONE; }
            if (!strcmp(n->call.name,"Record"))  { do_record(n,e);  return R_NONE; }
            eval(n, e);
            return R_NONE;

        default: eval(n, e); return R_NONE;
    }
}

/* ================================================================
   Public entry point
   ================================================================ */
int interp_run(ASTNode *root) {
    if (!root) { fprintf(stderr,"[interp] no AST\n"); return 1; }

    fcount = 0;
    collect_funcs(root->binop.left);

    ASTNode *admission = flookup("Admission");
    if (!admission) { fprintf(stderr,"[interp] no Admission function\n"); return 1; }

    /* Execute global decls; FUNC_DEF nodes silently return R_NONE */
    Env *global = env_push(NULL);
    stmts(root->binop.left, global);

    Env *es = env_push(global);
    printf("[MedLang] --- Program Output ---\n");
    Res r = stmts(admission->func.body, es);
    printf("\n[MedLang] --- Execution Complete ---\n");
    //if (r.sig == SIG_RETURN) printf("[MedLang] Admission returned: %g\n", r.val.num);

    env_pop(es);
    env_pop(global);
    return 0;
}