%{
#include <stdio.h>
#include <string.h>
#include "parser.h"
int line_no = 0;
int ch_no = 0;
%}
%option noyywrap
%option yylineno
%%

"const" {return CONSTANT;}

"int" { yylval.tip_data = strdup(yytext); return INT;}
"float" { yylval.tip_data = strdup(yytext); return FLOAT;}
"char" { yylval.tip_data = strdup(yytext); return CHAR;}
"string" { yylval.tip_data = strdup(yytext); return STRING;}
"bool" { yylval.tip_data = strdup(yytext); return BOOL;}

"class" {return CLASS;}


"@if" {return IF;}
"@else" {return ELSE;}
"@while" {return WHILE;}
"@for" {return FOR;}

"true"  { yylval.Bool = true; return BOOLEAN; }
"false" { yylval.Bool = false; return BOOLEAN; }

":=" {return ASSIGN;}
"||"  {return LOGIC_OR;}
"&&" {return LOGIC_AND;} 
"<"  {return LESS;}
"<=" {return LESS_EQ;}
">=" {return GRT_EQ;}
">"  {return GRT;} 
"==" {return EQ;}
"!=" {return NOT_EQ;}
"!"  {return NOT;}

"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"%" {return MOD;}


"EVAL" {return EVAL;}
"TYPEOF" {return TYPEOF;}
"return" {return RETURN;}

"begin_progr" {return BEGIN_PROGR;}
"end_progr" {return END_PROGR;}
"Eval" {return EVAL;}

[a-zA-Z][a-zA-Z0-9]* {yylval.String = strdup(yytext); return ID;}
cls_[a-zA-Z][a-zA-Z0-9]* {yylval.String = strdup(yytext); return CLASS_ID;}
fn_[a-zA-Z][a-zA-Z0-9]* {yylval.String = strdup(yytext); return FUN_ID;}
[-]?[0-9]+  {yylval.Int = atoi(yytext); return NR_INT;}
f[-]?(0|([1-9][0-9]*)).[0-9]*  {char* temp = strdup(yytext); temp++;  yylval.Float = atof(temp); return NR_FLOAT; }
[ \t] ;
\n {yylineno++; line_no++; ch_no=0;}
. {ch_no++; return yytext[0];}
