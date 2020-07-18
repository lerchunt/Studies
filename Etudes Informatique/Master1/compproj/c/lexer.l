%{
#include "assert.h"
#include "ast.h" 
#include "parser.h"
#include "string.h"
#include <stdbool.h>
#include <stdlib.h>

%}

%option noyywrap 
%option noinput 
%option nounput 

space    [ \t\n\r]
digit    [0-9]
lower    [a-z]
upper    [A-Z]
comment  \(\*(.|\n)*\*\)

%%
{space}+        { }
{comment}       { }
"("             { return LPAREN; }
")"             { return RPAREN; }
"true"          { yylval.tok_bool = true; return BOOL; }
"false"         { yylval.tok_bool = false; return BOOL; }
"not"           { return NOT; }
{digit}+        {  yylval.tok_int = atoi(yytext); return INT; }
{digit}+("."{digit}*)?(["e" "E"]["+" "-"]?digit+)?  {  yylval.tok_float = atof(yytext); return FLOAT; } 
"-"             { return MINUS; }
"+"             { return PLUS; }
"-."            { return MINUS_DOT; }
"+."            { return PLUS_DOT; }
"*."            { return AST_DOT; }
"/."            { return SLASH_DOT; }
"="             { return EQUAL; }
"<>"            { return LESS_GREATER; }
"<="            { return LESS_EQUAL; }
">="            { return GREATER_EQUAL; }
"<"             { return LESS; }
">"             { return GREATER; }
"if"            { return IF; }
"then"          { return THEN; }
"else"          { return ELSE; }
"let"           { return LET; }
"in"            { return IN; }
"rec"           { return REC; }
","             { return COMMA; }
"_"             { yylval.tok_id = id_gen(); return IDENT; }
"Array.create"  { return ARRAY_CREATE; }
"."             { return DOT; }
"<-"            { return LESS_MINUS; }
";"             { return SEMICOLON; }
eof             { return TEOF; }
{lower}({digit}|{lower}|{upper}|"_")*   { 
    char *new_id = malloc(strlen(yytext));
    strcpy(new_id, yytext);
    yylval.tok_id = new_id  ; return IDENT; }
.               { fprintf(stderr, "Error: lexical error\n"); exit(-1); }
%%

int yyerror(ptree *p, const char *msg) {
    fprintf(stderr,"Error: %s\n",msg);
    exit(-1);
}

/*
void yyprint (FILE *file, int ttype, YYSTYPE value) {
    printf("(-");
    switch(ttype) {
        case BOOL: printf("%d", value.tok_bool); break;
        case INT:  printf("%d", value.tok_int); break;
        case FLOAT:  printf("%f", value.tok_float); break;
        case IDENT:   printf("%s", value.tok_id); break;
        default: break; 
    }
    printf("-)");
//  if (type == VAR)
 //   fprintf (file, " %s", value.tptr->name);
//  else if (type == NUM)
//    fprintf (file, " %d", value.val);
}
*/



