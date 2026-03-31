
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

/* Line 1676 of yacc.c  */
#line 19 "medlang.y"

    int        ival;
    float      fval;
    char      *sval;
    ASTNode   *node;
    ParamNode *param;
    ArgNode   *arg;



/* Line 1676 of yacc.c  */
#line 141 "medlang.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


