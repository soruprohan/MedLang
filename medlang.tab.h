
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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
     SEALED = 270,
     NOSAMPLE = 271,
     PROTOCOL = 272,
     DIAGNOSE = 273,
     ALTERNATE = 274,
     SCREENING = 275,
     RESULT = 276,
     IDIOPATHICCASE = 277,
     TERMINATE = 278,
     FOLLOWUP = 279,
     DISCHARGE = 280,
     CYCLE = 281,
     CONTINUOUS = 282,
     LOADINGDOSE = 283,
     ADMISSION = 284,
     PLUS = 285,
     MINUS = 286,
     MULTIPLY = 287,
     DIVIDE = 288,
     MOD = 289,
     EQ = 290,
     NEQ = 291,
     GT = 292,
     LT = 293,
     GEQ = 294,
     LEQ = 295,
     AND = 296,
     OR = 297,
     NOT = 298,
     ASSIGN = 299,
     SEMICOLON = 300,
     COMMA = 301,
     LPAREN = 302,
     RPAREN = 303,
     LBRACE = 304,
     RBRACE = 305,
     RANGE_OP = 306,
     PRESCRIBE = 307,
     DEFINE = 308,
     INCLUDE_HEADER = 309,
     RECORD_KW = 310,
     OBSERVE_KW = 311,
     EXIT_KW = 312,
     WARDALLOC = 313,
     FREEWARD = 314,
     SIZESCAN = 315,
     POWER_FN = 316,
     ROOTCAUSE = 317,
     ABSDOSE = 318,
     ROUNDDOWN = 319,
     ROUNDUP = 320,
     SINE = 321,
     COSINE = 322,
     TANGENT = 323,
     ISCRITICAL = 324,
     RECORD_STRUCT = 325,
     INSTRUMENT = 326,
     TYPEALIAS = 327,
     DIAGNOSISLIST = 328,
     SYNAPSE = 329,
     BIOPSY = 330,
     IN_KW = 331,
     UMINUS = 332
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 20 "medlang.y"

    int        ival;
    float      fval;
    char      *sval;
    ASTNode   *node;
    ParamNode *param;
    ArgNode   *arg;



/* Line 1676 of yacc.c  */
#line 140 "medlang.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


