
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "medlang.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtable.h"
#include "semantic.h"
#include "interp.h"

void yyerror(const char *s);
int  yylex(void);
extern int lineno;

/* The root of the entire AST — set by the program rule */
ASTNode *ast_root = NULL;

int parse_error_count = 0;


/* Line 189 of yacc.c  */
#line 93 "medlang.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT_LITERAL = 258,
     FLOAT_LITERAL = 259,
     STRING_LITERAL = 260,
     IDENTIFIER = 261,
     ORGAN = 262,
     FLOW = 263,
     DIABETES = 264,
     CELL = 265,
     NULLTISSUE = 266,
     MAJORORGAN = 267,
     MINORORGAN = 268,
     NONPATHOLOGIC = 269,
     TISSUE = 270,
     SEALED = 271,
     NOSAMPLE = 272,
     PROTOCOL = 273,
     DIAGNOSE = 274,
     ALTERNATE = 275,
     SCREENING = 276,
     RESULT = 277,
     IDIOPATHICCASE = 278,
     TERMINATE = 279,
     FOLLOWUP = 280,
     DISCHARGE = 281,
     CYCLE = 282,
     CONTINUOUS = 283,
     LOADINGDOSE = 284,
     ADMISSION = 285,
     PLUS = 286,
     MINUS = 287,
     MULTIPLY = 288,
     DIVIDE = 289,
     MOD = 290,
     EQ = 291,
     NEQ = 292,
     GT = 293,
     LT = 294,
     GEQ = 295,
     LEQ = 296,
     AND = 297,
     OR = 298,
     NOT = 299,
     ASSIGN = 300,
     SEMICOLON = 301,
     COMMA = 302,
     LPAREN = 303,
     RPAREN = 304,
     LBRACE = 305,
     RBRACE = 306,
     RANGE_OP = 307,
     PRESCRIBE = 308,
     DEFINE = 309,
     INCLUDE_HEADER = 310,
     RECORD_KW = 311,
     OBSERVE_KW = 312,
     EXIT_KW = 313,
     WARDALLOC = 314,
     FREEWARD = 315,
     SIZESCAN = 316,
     POWER_FN = 317,
     ROOTCAUSE = 318,
     ABSDOSE = 319,
     ROUNDDOWN = 320,
     ROUNDUP = 321,
     SINE = 322,
     COSINE = 323,
     TANGENT = 324,
     ISCRITICAL = 325,
     RECORD_STRUCT = 326,
     INSTRUMENT = 327,
     TYPEALIAS = 328,
     DIAGNOSISLIST = 329,
     SYNAPSE = 330,
     BIOPSY = 331,
     IN_KW = 332,
     UMINUS = 333
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 23 "medlang.y"

    int        ival;
    float      fval;
    char      *sval;
    ASTNode   *node;
    ParamNode *param;
    ArgNode   *arg;



/* Line 214 of yacc.c  */
#line 218 "medlang.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 230 "medlang.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1169

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNRULES -- Number of states.  */
#define YYNSTATES  260

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   333

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    33,    35,    37,
      39,    43,    49,    56,    61,    66,    73,    81,    88,    97,
     105,   106,   108,   110,   114,   117,   119,   122,   124,   126,
     128,   130,   132,   134,   136,   138,   140,   142,   144,   146,
     148,   150,   152,   154,   157,   161,   164,   169,   173,   176,
     182,   190,   198,   206,   207,   210,   215,   219,   229,   239,
     240,   244,   249,   252,   253,   257,   263,   271,   277,   283,
     284,   286,   288,   292,   294,   298,   300,   303,   306,   309,
     313,   317,   321,   325,   329,   333,   337,   341,   345,   349,
     353,   357,   361,   364,   367,   371,   373,   375,   377,   379,
     381,   383,   385,   390,   395,   400,   405,   410,   415,   420,
     425,   430
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      80,     0,    -1,    81,    -1,    -1,    82,    -1,    81,    82,
      -1,    84,    -1,    85,    -1,    86,    -1,    87,    -1,    88,
      -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,    11,
      -1,    12,    -1,    13,    -1,    14,    -1,    15,    -1,    83,
       6,    46,    -1,    83,     6,    45,   115,    46,    -1,    16,
      83,     6,    45,   115,    46,    -1,    16,    83,     6,    46,
      -1,    17,    83,     6,    46,    -1,    17,    83,     6,    45,
     115,    46,    -1,    30,    48,    89,    49,    50,    92,    51,
      -1,    30,    48,    89,    49,    50,    51,    -1,    83,     6,
      48,    89,    49,    50,    92,    51,    -1,    83,     6,    48,
      89,    49,    50,    51,    -1,    -1,    90,    -1,    91,    -1,
      90,    47,    91,    -1,    83,     6,    -1,    93,    -1,    92,
      93,    -1,    95,    -1,    96,    -1,    97,    -1,    98,    -1,
     101,    -1,   104,    -1,   105,    -1,   106,    -1,   107,    -1,
     112,    -1,   113,    -1,    84,    -1,    85,    -1,    86,    -1,
      94,    -1,   114,    -1,     1,    46,    -1,    50,    92,    51,
      -1,    50,    51,    -1,     6,    45,   115,    46,    -1,    26,
     115,    46,    -1,    26,    46,    -1,    19,    48,   115,    49,
      94,    -1,    19,    48,   115,    49,    94,    20,    94,    -1,
      19,    48,   115,    49,    94,    20,    97,    -1,    21,    48,
     115,    49,    50,    99,    51,    -1,    -1,    99,   100,    -1,
      22,   115,    46,    92,    -1,    23,    46,    92,    -1,    27,
      48,   102,    46,   115,    46,   103,    49,    94,    -1,    27,
      48,     6,    77,     3,    52,     3,    49,    94,    -1,    -1,
       6,    45,   115,    -1,    83,     6,    45,   115,    -1,    83,
       6,    -1,    -1,     6,    45,   115,    -1,    28,    48,   115,
      49,    94,    -1,    29,    94,    28,    48,   115,    49,    46,
      -1,    57,    48,   108,    49,    46,    -1,    56,    48,   108,
      49,    46,    -1,    -1,   109,    -1,   110,    -1,   109,    47,
     110,    -1,   111,    -1,     6,    45,   115,    -1,   115,    -1,
      24,    46,    -1,    25,    46,    -1,   115,    46,    -1,   115,
      31,   115,    -1,   115,    32,   115,    -1,   115,    33,   115,
      -1,   115,    34,   115,    -1,   115,    35,   115,    -1,   115,
      36,   115,    -1,   115,    37,   115,    -1,   115,    38,   115,
      -1,   115,    39,   115,    -1,   115,    40,   115,    -1,   115,
      41,   115,    -1,   115,    42,   115,    -1,   115,    43,   115,
      -1,    44,   115,    -1,    32,   115,    -1,    48,   115,    49,
      -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,   116,
      -1,   117,    -1,    17,    -1,    62,    48,   108,    49,    -1,
      63,    48,   108,    49,    -1,    64,    48,   108,    49,    -1,
      65,    48,   108,    49,    -1,    66,    48,   108,    49,    -1,
      67,    48,   108,    49,    -1,    68,    48,   108,    49,    -1,
      69,    48,   108,    49,    -1,    70,    48,   108,    49,    -1,
       6,    48,   108,    49,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    99,    99,   105,   113,   115,   120,   121,   122,   123,
     124,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     148,   150,   155,   157,   162,   164,   173,   175,   184,   186,
     195,   196,   200,   202,   212,   221,   223,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   245,   261,   263,   272,   281,   283,   292,
     294,   296,   306,   311,   312,   316,   318,   330,   333,   339,
     340,   342,   344,   350,   351,   360,   370,   379,   384,   393,
     394,   398,   400,   410,   415,   418,   427,   432,   441,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   466,   467,   468,   469,   470,   471,
     472,   473,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   497
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_LITERAL", "FLOAT_LITERAL",
  "STRING_LITERAL", "IDENTIFIER", "ORGAN", "FLOW", "DIABETES", "CELL",
  "NULLTISSUE", "MAJORORGAN", "MINORORGAN", "NONPATHOLOGIC", "TISSUE",
  "SEALED", "NOSAMPLE", "PROTOCOL", "DIAGNOSE", "ALTERNATE", "SCREENING",
  "RESULT", "IDIOPATHICCASE", "TERMINATE", "FOLLOWUP", "DISCHARGE",
  "CYCLE", "CONTINUOUS", "LOADINGDOSE", "ADMISSION", "PLUS", "MINUS",
  "MULTIPLY", "DIVIDE", "MOD", "EQ", "NEQ", "GT", "LT", "GEQ", "LEQ",
  "AND", "OR", "NOT", "ASSIGN", "SEMICOLON", "COMMA", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "RANGE_OP", "PRESCRIBE", "DEFINE", "INCLUDE_HEADER",
  "RECORD_KW", "OBSERVE_KW", "EXIT_KW", "WARDALLOC", "FREEWARD",
  "SIZESCAN", "POWER_FN", "ROOTCAUSE", "ABSDOSE", "ROUNDDOWN", "ROUNDUP",
  "SINE", "COSINE", "TANGENT", "ISCRITICAL", "RECORD_STRUCT", "INSTRUMENT",
  "TYPEALIAS", "DIAGNOSISLIST", "SYNAPSE", "BIOPSY", "IN_KW", "UMINUS",
  "$accept", "program", "top_level_list", "top_level_item", "type_spec",
  "var_decl", "sealed_var_decl", "nosample_decl", "admission_func",
  "func_def", "param_list", "param_list_ne", "param", "stmt_list", "stmt",
  "block", "assign_stmt", "discharge_stmt", "diagnose_stmt",
  "screening_stmt", "case_body", "case_item", "cycle_stmt", "for_init",
  "for_update", "continuous_stmt", "loading_dose_stmt", "observe_stmt",
  "record_stmt", "arg_list", "arg_list_ne", "arg", "named_arg",
  "terminate_stmt", "followup_stmt", "expr_stmt", "expr", "builtin_call",
  "user_call", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    80,    81,    81,    82,    82,    82,    82,
      82,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      84,    84,    85,    85,    86,    86,    87,    87,    88,    88,
      89,    89,    90,    90,    91,    92,    92,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    94,    94,    95,    96,    96,    97,
      97,    97,    98,    99,    99,   100,   100,   101,   101,   102,
     102,   102,   102,   103,   103,   104,   105,   106,   107,   108,
     108,   109,   109,   110,   111,   111,   112,   113,   114,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     6,     4,     4,     6,     7,     6,     8,     7,
       0,     1,     1,     3,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     3,     2,     4,     3,     2,     5,
       7,     7,     7,     0,     2,     4,     3,     9,     9,     0,
       3,     4,     2,     0,     3,     5,     7,     5,     5,     0,
       1,     1,     3,     1,     3,     1,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     3,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    11,    12,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     2,     4,     0,     6,     7,     8,
       9,    10,     0,     0,    30,     1,     5,     0,     0,     0,
       0,     0,    31,    32,     0,    20,    30,     0,    23,     0,
      24,    34,     0,     0,   105,   106,   107,   108,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   109,   110,     0,     0,     0,     0,    33,    79,
     103,   102,     0,    79,    79,    79,    79,    79,    79,    79,
      79,    79,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,     0,    22,    25,     0,
     108,   111,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,     0,     0,     0,    48,    49,    50,     0,    35,
      51,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    52,     0,   108,     0,    80,    81,    83,    85,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,     0,    53,     0,     0,     0,    86,    87,
      58,     0,    69,     0,     0,    55,     0,    79,    79,     0,
      26,    36,    88,     0,   121,     0,   112,   113,   114,   115,
     116,   117,   118,   119,   120,    29,     0,     0,     0,     0,
      57,     0,     0,     0,     0,     0,    54,     0,     0,    84,
      82,    28,    56,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,    59,    63,    70,     0,     0,     0,    75,
       0,    78,    77,     0,     0,     0,    71,    73,     0,    60,
      61,     0,     0,    62,    64,     0,     0,     0,    76,     0,
       0,     0,     0,     0,     0,     0,    68,    74,    67,     0
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    13,    14,    15,   114,   115,   116,   117,    20,    21,
      31,    32,    33,   118,   119,   120,   121,   122,   123,   124,
     234,   244,   125,   203,   247,   126,   127,   128,   129,   135,
     136,   137,   138,   130,   131,   132,   139,    62,    63
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -109
static const yytype_int16 yypact[] =
{
     187,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
     399,   399,   -37,    12,   187,  -109,    34,  -109,  -109,  -109,
    -109,  -109,    40,    56,   399,  -109,  -109,    -9,   -39,   -14,
      69,   -19,    35,  -109,   848,  -109,   399,   848,  -109,   848,
    -109,  -109,    31,   399,  -109,  -109,  -109,    37,  -109,   848,
     848,   848,    38,    41,    42,    44,    50,    59,    60,    61,
      68,   999,  -109,  -109,    39,  1015,  1031,   373,  -109,   902,
    -109,  -109,   835,   902,   902,   902,   902,   902,   902,   902,
     902,   902,   848,   848,   848,   848,   848,   848,   848,   848,
     848,   848,   848,   848,   848,  -109,    54,  -109,  -109,    64,
      -3,   399,    70,    71,    74,    75,   109,    76,    79,    67,
     443,  -109,    80,    82,    77,  -109,  -109,  -109,   513,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  1047,    -1,    85,    88,  -109,  -109,   920,
    -109,    87,    89,    91,    95,    97,    98,   102,   107,   110,
      45,    45,  -109,  -109,  -109,    62,    62,    33,    33,    33,
      33,   235,  1127,   583,  -109,   848,   848,   848,  -109,  -109,
    -109,  1063,   330,   848,   130,  -109,   653,   902,   902,    24,
    -109,  -109,  -109,   848,  -109,   902,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,   723,  1079,   889,   942,
    -109,   -43,   131,   114,   961,   113,  -109,   116,   117,   920,
    -109,  -109,  -109,    67,   118,   848,   160,   122,   848,    67,
     848,   123,   124,   162,  -109,   920,   128,   848,  1095,  -109,
     980,  -109,  -109,   -15,   -13,   180,   920,   179,   141,  -109,
    -109,   848,   142,  -109,  -109,   140,   145,   143,  -109,  1111,
     793,    67,   848,    67,   793,   233,  -109,   920,  -109,   303
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,  -109,   177,    63,    14,    27,    29,  -109,  -109,
     169,  -109,   163,  -102,  -105,  -108,  -109,  -109,   -25,  -109,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,   -55,
    -109,    25,  -109,  -109,  -109,  -109,   -34,  -109,  -109
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -67
static const yytype_int16 yytable[] =
{
      61,   174,   215,    65,   102,    66,    37,    38,   176,   241,
     242,    24,    25,   181,    17,    70,    71,    72,   141,   142,
     143,   144,   145,   146,   147,   148,   149,    18,    17,    19,
      42,    39,    40,   133,   216,   110,    34,    35,   243,    36,
      27,    18,   165,    19,   183,    69,    28,    69,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   196,    29,    16,    82,    83,    84,    85,    86,    34,
      35,   181,   171,    22,    23,    41,   133,    16,    84,    85,
      86,    67,    43,   179,   133,    69,    73,    30,    96,    74,
      75,   181,    76,    82,    83,    84,    85,    86,    77,    30,
      89,    90,    91,    92,   163,   223,    30,    78,    79,    80,
     164,   229,    44,    45,    46,    47,    81,   110,   166,   167,
     168,   169,   207,   208,   172,   239,    48,   173,   177,   133,
     178,   197,   198,   199,   184,   185,   186,   217,   187,   204,
     188,    49,   133,   256,   189,   258,   190,   191,   255,   209,
     181,   192,   259,    50,   181,   170,   193,    51,   205,   194,
     218,   220,   133,   226,    23,   221,   222,   227,   224,   231,
     232,    52,    53,    54,    55,    56,    57,    58,    59,    60,
     235,   225,   233,   245,   228,   246,   230,   248,   250,   251,
     252,    26,   253,   236,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    64,    68,   249,   240,     0,
     210,     0,     0,     0,     0,     0,   133,    12,   257,     0,
     133,   133,     0,     0,     0,   133,     0,     0,     0,     0,
       0,     0,     0,     0,    99,   202,    44,    45,    46,   100,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     101,     0,   102,     0,   103,   -66,   -66,   104,   105,   106,
     107,   108,   109,     0,     0,    49,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    50,     0,     0,
       0,    51,     0,   110,   -66,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    99,     0,    44,    45,    46,   100,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     101,     0,   102,     0,   103,   -65,   -65,   104,   105,   106,
     107,   108,   109,     0,     0,    49,   201,     1,     2,     3,
       4,     5,     6,     7,     8,     9,     0,    50,     0,     0,
       0,    51,     0,   110,   -65,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    99,     0,    44,    45,    46,   100,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     101,     0,   102,     0,   103,     0,     0,   104,   105,   106,
     107,   108,   109,     0,     0,    49,     1,     2,     3,     4,
       5,     6,     7,     8,     9,     0,     0,    50,     0,     0,
       0,    51,     0,   110,   111,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    99,     0,    44,    45,    46,   100,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     101,     0,   102,     0,   103,     0,     0,   104,   105,   106,
     107,   108,   109,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,    51,     0,   110,   175,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    99,     0,    44,    45,    46,   100,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     101,     0,   102,     0,   103,     0,     0,   104,   105,   106,
     107,   108,   109,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,    51,     0,   110,   180,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    99,     0,    44,    45,    46,   100,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     101,     0,   102,     0,   103,     0,     0,   104,   105,   106,
     107,   108,   109,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,    51,     0,   110,   195,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    99,     0,    44,    45,    46,   100,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     101,     0,   102,     0,   103,     0,     0,   104,   105,   106,
     107,   108,   109,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,    51,     0,   110,   206,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    99,     0,    44,    45,    46,   100,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     101,     0,   102,     0,   103,     0,     0,   104,   105,   106,
     107,   108,   109,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,    51,     0,   110,   211,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    99,     0,    44,    45,    46,   100,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
     101,     0,   102,     0,   103,     0,     0,   104,   105,   106,
     107,   108,   109,     0,     0,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
       0,    51,     0,   110,     0,     0,     0,     0,     0,   112,
     113,    44,    45,    46,    47,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     0,    48,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
      49,     0,     0,     0,   140,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,     0,    51,     0,     0,     0,
       0,     0,     0,     0,     0,    44,    45,    46,   134,     0,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    48,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,    49,     0,     0,     0,   213,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,     0,
      51,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,     0,     0,     0,     0,
       0,   214,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,     0,     0,     0,
     219,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,     0,     0,     0,     0,     0,   238,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,    95,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       0,    97,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,    98,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,     0,     0,   182,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,   200,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,     0,     0,   212,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       0,   237,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,   254,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93
};

static const yytype_int16 yycheck[] =
{
      34,   109,    45,    37,    19,    39,    45,    46,   110,    22,
      23,    48,     0,   118,     0,    49,    50,    51,    73,    74,
      75,    76,    77,    78,    79,    80,    81,     0,    14,     0,
      49,    45,    46,    67,    77,    50,    45,    46,    51,    48,
       6,    14,    45,    14,    45,    48,     6,    48,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,   163,     6,     0,    31,    32,    33,    34,    35,    45,
      46,   176,   106,    10,    11,     6,   110,    14,    33,    34,
      35,    50,    47,     6,   118,    48,    48,    24,    49,    48,
      48,   196,    48,    31,    32,    33,    34,    35,    48,    36,
      38,    39,    40,    41,    50,   213,    43,    48,    48,    48,
      46,   219,     3,     4,     5,     6,    48,    50,    48,    48,
      46,    46,   177,   178,    48,   233,    17,    48,    48,   163,
      48,   165,   166,   167,    49,    47,    49,     6,    49,   173,
      49,    32,   176,   251,    49,   253,    49,    49,   250,   183,
     255,    49,   254,    44,   259,    46,    49,    48,    28,    49,
      46,    48,   196,     3,   101,    49,    49,    45,    50,    46,
      46,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      52,   215,    20,     3,   218,     6,   220,    46,    46,    49,
      45,    14,    49,   227,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    36,    43,   241,   233,    -1,
     185,    -1,    -1,    -1,    -1,    -1,   250,    30,   252,    -1,
     254,   255,    -1,    -1,    -1,   259,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,   172,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    44,    -1,    -1,
      -1,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    44,    -1,    -1,
      -1,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    21,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    44,    -1,    -1,
      -1,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    21,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    21,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    21,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    21,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    21,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    -1,    21,    -1,    -1,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,
      57,     3,     4,     5,     6,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    -1,    17,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      32,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    17,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    32,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      48,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    49,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    -1,    46,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    46,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    46,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    -1,    46,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    -1,    46,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    -1,    46,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    46,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    -1,    -1,    46,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    30,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    83,    83,    48,     0,    82,     6,     6,     6,
      83,    89,    90,    91,    45,    46,    48,    45,    46,    45,
      46,     6,    49,    47,     3,     4,     5,     6,    17,    32,
      44,    48,    62,    63,    64,    65,    66,    67,    68,    69,
      70,   115,   116,   117,    89,   115,   115,    50,    91,    48,
     115,   115,   115,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    46,    49,    46,    46,     1,
       6,    17,    19,    21,    24,    25,    26,    27,    28,    29,
      50,    51,    56,    57,    83,    84,    85,    86,    92,    93,
      94,    95,    96,    97,    98,   101,   104,   105,   106,   107,
     112,   113,   114,   115,     6,   108,   109,   110,   111,   115,
      49,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,    50,    46,    45,    48,    48,    46,    46,
      46,   115,    48,    48,    94,    51,    92,    48,    48,     6,
      51,    93,    46,    45,    49,    47,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    51,    92,   115,   115,   115,
      46,     6,    83,   102,   115,    28,    51,   108,   108,   115,
     110,    51,    46,    49,    49,    45,    77,     6,    46,    49,
      48,    49,    49,    94,    50,   115,     3,    45,   115,    94,
     115,    46,    46,    20,    99,    52,   115,    46,    49,    94,
      97,    22,    23,    51,   100,     3,     6,   103,    46,   115,
      46,    49,    45,    49,    46,    92,    94,   115,    94,    92
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 100 "medlang.y"
    {
            (yyval.node) = make_program((yyvsp[(1) - (1)].node));
            ast_root = (yyval.node);
        ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 105 "medlang.y"
    {
            (yyval.node) = make_program(NULL);
            ast_root = (yyval.node);
            printf("[PARSE] Empty program.\n");
        ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 114 "medlang.y"
    { (yyval.node) = make_stmt_list((yyvsp[(1) - (1)].node), NULL); ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 116 "medlang.y"
    { (yyval.node) = make_stmt_list((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 120 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 121 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 122 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 123 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 124 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 132 "medlang.y"
    { (yyval.sval) = "Organ";         ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 133 "medlang.y"
    { (yyval.sval) = "Flow";           ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 134 "medlang.y"
    { (yyval.sval) = "Diabetes";       ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 135 "medlang.y"
    { (yyval.sval) = "Cell";           ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 136 "medlang.y"
    { (yyval.sval) = "NullTissue";     ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 137 "medlang.y"
    { (yyval.sval) = "MajorOrgan";     ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 138 "medlang.y"
    { (yyval.sval) = "MinorOrgan";     ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 139 "medlang.y"
    { (yyval.sval) = "NonPathologic";  ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 140 "medlang.y"
    { (yyval.sval) = "Tissue";         ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 149 "medlang.y"
    { (yyval.node) = make_decl((yyvsp[(1) - (3)].sval), (yyvsp[(2) - (3)].sval), 0, 0, NULL, lineno); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 151 "medlang.y"
    { (yyval.node) = make_decl((yyvsp[(1) - (5)].sval), (yyvsp[(2) - (5)].sval), 0, 0, (yyvsp[(4) - (5)].node), lineno); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 156 "medlang.y"
    { (yyval.node) = make_decl((yyvsp[(2) - (6)].sval), (yyvsp[(3) - (6)].sval), 1, 0, (yyvsp[(5) - (6)].node), lineno); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 158 "medlang.y"
    { (yyval.node) = make_decl((yyvsp[(2) - (4)].sval), (yyvsp[(3) - (4)].sval), 1, 0, NULL, lineno); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 163 "medlang.y"
    { (yyval.node) = make_decl((yyvsp[(2) - (4)].sval), (yyvsp[(3) - (4)].sval), 0, 1, NULL, lineno); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 165 "medlang.y"
    { (yyval.node) = make_decl((yyvsp[(2) - (6)].sval), (yyvsp[(3) - (6)].sval), 0, 1, (yyvsp[(5) - (6)].node), lineno); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 174 "medlang.y"
    { (yyval.node) = make_func_def("NullTissue", "Admission", (yyvsp[(3) - (7)].param), (yyvsp[(6) - (7)].node), lineno); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 176 "medlang.y"
    { (yyval.node) = make_func_def("NullTissue", "Admission", (yyvsp[(3) - (6)].param), NULL, lineno); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 185 "medlang.y"
    { (yyval.node) = make_func_def((yyvsp[(1) - (8)].sval), (yyvsp[(2) - (8)].sval), (yyvsp[(4) - (8)].param), (yyvsp[(7) - (8)].node), lineno); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 187 "medlang.y"
    { (yyval.node) = make_func_def((yyvsp[(1) - (7)].sval), (yyvsp[(2) - (7)].sval), (yyvsp[(4) - (7)].param), NULL, lineno); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 195 "medlang.y"
    { (yyval.param) = NULL; ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 196 "medlang.y"
    { (yyval.param) = (yyvsp[(1) - (1)].param); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 201 "medlang.y"
    { (yyval.param) = (yyvsp[(1) - (1)].param); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 203 "medlang.y"
    { /* append $3 to end of $1 */
          ParamNode *p = (yyvsp[(1) - (3)].param);
          while (p->next) p = p->next;
          p->next = (yyvsp[(3) - (3)].param);
          (yyval.param) = (yyvsp[(1) - (3)].param);
        ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 213 "medlang.y"
    { (yyval.param) = make_param((yyvsp[(1) - (2)].sval), (yyvsp[(2) - (2)].sval), NULL); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 222 "medlang.y"
    { (yyval.node) = make_stmt_list((yyvsp[(1) - (1)].node), NULL); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 224 "medlang.y"
    { (yyval.node) = make_stmt_list((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 228 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 229 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 230 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 231 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 232 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 233 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 234 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 235 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 236 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 237 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 238 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 239 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 240 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 241 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 242 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 243 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 246 "medlang.y"
    {
            yyerrok;
            parse_error_count++;
            (yyval.node) = NULL;
            fprintf(stderr,
                "[MedLang] Syntax error near line %d, resuming after '|'\n",
                lineno);
        ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 262 "medlang.y"
    { (yyval.node) = make_block((yyvsp[(2) - (3)].node), lineno); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 264 "medlang.y"
    { (yyval.node) = make_block(NULL, lineno); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 273 "medlang.y"
    { (yyval.node) = make_assign((yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].node), lineno); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 282 "medlang.y"
    { (yyval.node) = make_return((yyvsp[(2) - (3)].node), lineno); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 284 "medlang.y"
    { (yyval.node) = make_return(NULL, lineno); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 293 "medlang.y"
    { (yyval.node) = make_if((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), NULL, lineno); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 295 "medlang.y"
    { (yyval.node) = make_if((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node), lineno); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 297 "medlang.y"
    { (yyval.node) = make_if((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node), lineno); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 307 "medlang.y"
    { (yyval.node) = make_if((yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node), NULL, lineno); /* placeholder */ ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 311 "medlang.y"
    { (yyval.node) = NULL; ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 312 "medlang.y"
    { (yyval.node) = make_stmt_list((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 317 "medlang.y"
    { (yyval.node) = make_stmt_list((yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 319 "medlang.y"
    { (yyval.node) = (yyvsp[(3) - (3)].node); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 331 "medlang.y"
    { (yyval.node) = make_for((yyvsp[(3) - (9)].node), (yyvsp[(5) - (9)].node), (yyvsp[(7) - (9)].node), (yyvsp[(9) - (9)].node), lineno); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 334 "medlang.y"
    { (yyval.node) = make_range_loop((yyvsp[(3) - (9)].sval), (yyvsp[(5) - (9)].ival), (yyvsp[(7) - (9)].ival), (yyvsp[(9) - (9)].node), lineno); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 339 "medlang.y"
    { (yyval.node) = NULL; ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 341 "medlang.y"
    { (yyval.node) = make_assign((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 343 "medlang.y"
    { (yyval.node) = make_decl((yyvsp[(1) - (4)].sval), (yyvsp[(2) - (4)].sval), 0, 0, (yyvsp[(4) - (4)].node), lineno); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 345 "medlang.y"
    { (yyval.node) = make_decl((yyvsp[(1) - (2)].sval), (yyvsp[(2) - (2)].sval), 0, 0, NULL, lineno); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 350 "medlang.y"
    { (yyval.node) = NULL; ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 352 "medlang.y"
    { (yyval.node) = make_assign((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 361 "medlang.y"
    { (yyval.node) = make_while((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), lineno); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 371 "medlang.y"
    { (yyval.node) = make_do_while((yyvsp[(2) - (7)].node), (yyvsp[(5) - (7)].node), lineno); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 380 "medlang.y"
    { (yyval.node) = make_func_call("Observe", (yyvsp[(3) - (5)].arg), lineno); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 385 "medlang.y"
    { (yyval.node) = make_func_call("Record", (yyvsp[(3) - (5)].arg), lineno); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 393 "medlang.y"
    { (yyval.arg) = NULL; ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 394 "medlang.y"
    { (yyval.arg) = (yyvsp[(1) - (1)].arg); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 399 "medlang.y"
    { (yyval.arg) = (yyvsp[(1) - (1)].arg); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 401 "medlang.y"
    { /* append $3 */
          ArgNode *a = (yyvsp[(1) - (3)].arg);
          while (a->next) a = a->next;
          a->next = (yyvsp[(3) - (3)].arg);
          (yyval.arg) = (yyvsp[(1) - (3)].arg);
        ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 410 "medlang.y"
    { (yyval.arg) = (yyvsp[(1) - (1)].arg); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 416 "medlang.y"
    { (yyval.arg) = make_arg((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].node), NULL); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 419 "medlang.y"
    { (yyval.arg) = make_arg(NULL, (yyvsp[(1) - (1)].node), NULL); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 428 "medlang.y"
    { (yyval.node) = make_break(lineno); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 433 "medlang.y"
    { (yyval.node) = make_continue(lineno); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 442 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 450 "medlang.y"
    { (yyval.node) = make_binop(PLUS,     (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 451 "medlang.y"
    { (yyval.node) = make_binop(MINUS,    (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 452 "medlang.y"
    { (yyval.node) = make_binop(MULTIPLY, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 453 "medlang.y"
    { (yyval.node) = make_binop(DIVIDE,   (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 454 "medlang.y"
    { (yyval.node) = make_binop(MOD,      (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 455 "medlang.y"
    { (yyval.node) = make_binop(EQ,       (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 456 "medlang.y"
    { (yyval.node) = make_binop(NEQ,      (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 457 "medlang.y"
    { (yyval.node) = make_binop(GT,       (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 458 "medlang.y"
    { (yyval.node) = make_binop(LT,       (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 459 "medlang.y"
    { (yyval.node) = make_binop(GEQ,      (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 460 "medlang.y"
    { (yyval.node) = make_binop(LEQ,      (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 461 "medlang.y"
    { (yyval.node) = make_binop(AND,      (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 462 "medlang.y"
    { (yyval.node) = make_binop(OR,       (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), lineno); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 463 "medlang.y"
    { (yyval.node) = make_unop(NOT,   (yyvsp[(2) - (2)].node), lineno); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 465 "medlang.y"
    { (yyval.node) = make_unop(MINUS, (yyvsp[(2) - (2)].node), lineno); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 466 "medlang.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 467 "medlang.y"
    { (yyval.node) = make_int_lit((yyvsp[(1) - (1)].ival), lineno); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 468 "medlang.y"
    { (yyval.node) = make_float_lit((yyvsp[(1) - (1)].fval), lineno); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 469 "medlang.y"
    { (yyval.node) = make_string_lit((yyvsp[(1) - (1)].sval), lineno); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 470 "medlang.y"
    { (yyval.node) = make_ident((yyvsp[(1) - (1)].sval), lineno); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 471 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 472 "medlang.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 473 "medlang.y"
    { (yyval.node) = make_int_lit(0, lineno); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 481 "medlang.y"
    { (yyval.node) = make_func_call("Power",     (yyvsp[(3) - (4)].arg), lineno); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 482 "medlang.y"
    { (yyval.node) = make_func_call("RootCause", (yyvsp[(3) - (4)].arg), lineno); ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 483 "medlang.y"
    { (yyval.node) = make_func_call("AbsDose",   (yyvsp[(3) - (4)].arg), lineno); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 484 "medlang.y"
    { (yyval.node) = make_func_call("RoundDown", (yyvsp[(3) - (4)].arg), lineno); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 485 "medlang.y"
    { (yyval.node) = make_func_call("RoundUp",   (yyvsp[(3) - (4)].arg), lineno); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 486 "medlang.y"
    { (yyval.node) = make_func_call("Sine",      (yyvsp[(3) - (4)].arg), lineno); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 487 "medlang.y"
    { (yyval.node) = make_func_call("Cosine",    (yyvsp[(3) - (4)].arg), lineno); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 488 "medlang.y"
    { (yyval.node) = make_func_call("Tangent",   (yyvsp[(3) - (4)].arg), lineno); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 489 "medlang.y"
    { (yyval.node) = make_func_call("IsCritical",(yyvsp[(3) - (4)].arg), lineno); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 498 "medlang.y"
    { (yyval.node) = make_func_call((yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].arg), lineno); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2710 "medlang.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 501 "medlang.y"


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

    /* Syntax Analysis */
    int parse_result = yyparse();
    if (parse_result != 0)
        return parse_result;

    /* Check if errors were recovered during parsing */
    if (parse_error_count > 0) {
        fprintf(stderr, "[MedLang] %d parse error(s) found. Compilation aborted.\n", parse_error_count);
        return 1;
    }

    printf("[MedLang] Parse completed successfully.\n");

    /* Semantic Analysis */
    if (ast_root) {
        int sem_result = analyze_program(ast_root);
        if (sem_result != 0) {
            fprintf(stderr,"[MedLang] Semantic errors found.\n");
            return sem_result;
        }
    }

    /* AST Interpreter */  
    if (ast_root) {
        printf("[MedLang] Starting interpreter...\n");
        interp_run(ast_root);
    }          

    return 0;
}
