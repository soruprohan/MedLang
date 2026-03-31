%{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "medlang.tab.h"   

int lineno=1;
void yyerror(const char *s);
%}

DIGIT  [0-9]
LETTER   [a-zA-Z_]
ID     {LETTER}({LETTER}|{DIGIT})*
INT_LIT   {DIGIT}+
FLOAT_LIT {DIGIT}+"."{DIGIT}*
EXP    [Ee][+-]?{DIGIT}+
FLOAT_EXP {FLOAT_LIT}{EXP}?

%option noyywrap

%%

"##".*       {/*skip*/}

"#+"       {
            int c,prev=0;
                        while(1){
                            c=input();
                            if(c==EOF){
                                fprintf(stderr, "[MedLang Error] Line %d: unterminated multi-line comment\n",lineno);
                                break;
                       }
                            if(c=='\n') 
                                lineno++;
                            if(prev=='+' && c=='#'){
                                break;
                       }
                            prev=c;
                       }
           }

"Organ"          {return ORGAN;}
"Flow"            {return FLOW;}
"Diabetes"          {return DIABETES;}
"Cell"           {return CELL;}
 "NullTissue"        {return NULLTISSUE;}
"Tissue"          {return TISSUE;}
"MajorOrgan"     {return MAJORORGAN;}
"MinorOrgan"      {return MINORORGAN;}
 "NonPathologic"      {return NONPATHOLOGIC;}
"Sealed"           {return SEALED;}
"NoSample"        {return NOSAMPLE;}
"Protocol"       {return PROTOCOL;}
 "Diagnose"     {return DIAGNOSE;}
"Alternate"          {return ALTERNATE;}
"Screening"         {return SCREENING;}
"Result"         {return RESULT;}
 "IdiopathicCase"   {return IDIOPATHICCASE;}
"Terminate"            {return TERMINATE;}
"FollowUp"       {return FOLLOWUP;}
"Discharge"      {return DISCHARGE;}
"Cycle"      {return CYCLE;}
"Continuous"   {return CONTINUOUS;}
  "LoadingDose"         {return LOADINGDOSE;}
 "in"              {return IN_KW;}
"Admission"      {return ADMISSION;}
"Record"            {return RECORD_KW;}
"Observe"        {return OBSERVE_KW;}
"exit"                {return EXIT_KW;}

"Power"         {return POWER_FN;}
"RootCause"       {return ROOTCAUSE;}
"AbsDose"        {return ABSDOSE;}
"RoundDown"         {return ROUNDDOWN;}
"RoundUp"       {return ROUNDUP;}
"Sine"           {return SINE;}
"Cosine"       {return COSINE;}
"Tangent"           {return TANGENT;}
"IsCritical"    {return ISCRITICAL;}
"=:"                  {return ASSIGN;}
"Match"         {return EQ;}
"MisMatch"        {return NEQ;}
"AboveNormal"      {return GT;}
 "BelowNormal"       {return LT;}
 "MaxSafe"         {return GEQ;}
"MinSafe"             {return LEQ;}
"Both"          {return AND;}
"Either"           {return OR;}
"Negate"             {return NOT;}
"DosePlus"            {return PLUS;}
"DoseMinus"       {return MINUS;}
"DoseMultiply"       {return MULTIPLY;}
"DoseDivide"     {return DIVIDE;}
"DoseMod"       {return MOD;}

"|"         {return SEMICOLON;}
"<:"             {return LPAREN;}
":>"                  {return RPAREN;}
"[:"            {return LBRACE;}
":]"                {return RBRACE;}
".."             {return RANGE_OP;}
","             {return COMMA;}

\"[^\"\n]*\n     {
               fprintf(stderr,"[MedLang Error] Line %d: unterminated string literal\n", lineno);
                        lineno++;
                   }

{FLOAT_EXP}      {    yylval.fval=atof(yytext);
                     return FLOAT_LITERAL;
            }
{INT_LIT}       {     yylval.ival=atoi(yytext);
                       return INT_LITERAL;
                   }
\"[^\"\n]*\"        {  yylval.sval= strdup(yytext+1);
                        yylval.sval[yyleng-2]='\0';
                        return STRING_LITERAL;
                   }

                    
\'[^\'\n]\'    { yylval.ival = yytext[1];
                      return INT_LITERAL;
                   }

{ID}      { yylval.sval = strdup(yytext);
                 return IDENTIFIER; }

\n              {lineno++;}
[ \t\r]+           {}

.             {    fprintf(stderr,"[MedLang Error] Line %d: unknown character '%s'\n",lineno, yytext);}

%%