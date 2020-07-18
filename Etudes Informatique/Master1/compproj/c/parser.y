%{
#include <assert.h>
#include <stddef.h>
#include "ast.h"
#include <stdio.h>

#define YYDEBUG 1

//#define YYPRINT(file, ttype, value)   yyprint (file, ttype, value)

int yylex (void);
extern int yyerror(ptree *p, const char *msg); 
//extern void yyprint (FILE *file, int ttype, YYSTYPE value); 

%}

%parse-param { ptree *ast }

%union {
    int tok_int;
    float tok_float;
    id tok_id;
    int tok_bool;
    ptree tok_tree;
    plist tok_list;
    pfundef tok_fd;
}

%token <tok_bool> BOOL
%token <tok_int> INT
%token <tok_float> FLOAT
%token NOT
%token MINUS
%token PLUS
%token MINUS_DOT
%token PLUS_DOT
%token AST_DOT
%token SLASH_DOT
%token EQUAL
%token LESS_GREATER
%token LESS_EQUAL
%token GREATER_EQUAL
%token LESS
%token GREATER
%token IF
%token THEN
%token ELSE
%token <tok_id> IDENT
%token LET
%token IN
%token REC
%token COMMA
%token ARRAY_CREATE
%token DOT
%token LESS_MINUS
%token SEMICOLON
%token LPAREN
%token RPAREN
%token TEOF

%right prec_let
%right SEMICOLON
%right prec_if
%right LESS_MINUS
%left COMMA
%left EQUAL LESS_GREATER LESS GREATER LESS_EQUAL GREATER_EQUAL
%left PLUS MINUS PLUS_DOT MINUS_DOT
%left AST_DOT SLASH_DOT
%right prec_unary_minus
%left prec_app
%left DOT

%type <tok_fd> fundef
%type <tok_list> pat
%type <tok_list> elems
%type <tok_list> actual_args
%type <tok_list> formal_args
%type <tok_tree> simple_exp 
%type <tok_tree> exp
%type <tok_tree> input 

%%
input:
     exp { *ast = $1; }
;

simple_exp: 
  LPAREN exp RPAREN
    { $$ = $2; }
| LPAREN RPAREN
    { $$ = ast_unit(); }
| BOOL
    { $$ = ast_bool(yylval.tok_bool); }
| INT
    { $$ = ast_integ(yylval.tok_int); }
| FLOAT
    { $$ = ast_float(yylval.tok_float); }
| IDENT
    { $$ = ast_var(yylval.tok_id); }
| simple_exp DOT LPAREN exp RPAREN
    { $$ = ast_get($1, $4); }

exp: 
  simple_exp
    { $$ = $1; }
| NOT exp
    %prec prec_app
    { 
      $$ = ast_not($2); }
| MINUS exp
    %prec prec_unary_minus
    { ptree t = $2;
      if (t->code == T_FLOAT) {
        $$ = ast_float(-$2->params.f);
      } else {
        $$ = ast_neg($2);
      }
    }

| exp PLUS exp 
    { $$ = ast_add($1, $3); }
| exp MINUS exp
    { $$ = ast_sub($1, $3); }
| exp EQUAL exp
    { $$ = ast_eq($1, $3); }
| exp LESS_GREATER exp
    { $$ = ast_not(ast_eq($1, $3)); }
| exp LESS exp
    { $$ = ast_not(ast_le($3, $1)); }
| exp GREATER exp
    { $$ = ast_not(ast_le($1, $3)); }
| exp LESS_EQUAL exp
    { $$ = ast_le($1, $3); }
| exp GREATER_EQUAL exp
    { $$ = ast_le($3, $1); }
| IF exp THEN exp ELSE exp
    %prec prec_if
    { $$ = ast_if($2, $4, $6); }
| MINUS_DOT exp
    %prec prec_unary_minus
    { $$ = ast_fneg($2); }
| exp PLUS_DOT exp
    { $$ =  ast_fadd($1, $3); }
| exp MINUS_DOT exp
    { $$ = ast_fsub($1, $3); }
| exp AST_DOT exp
    { $$ =  ast_fmul($1, $3); }
| exp SLASH_DOT exp
    { $$ =  ast_fdiv($1, $3); }
| LET IDENT EQUAL exp IN exp
    %prec prec_let
    { $$ = ast_let($2, $4, $6); }
| LET REC fundef IN exp
    %prec prec_let
    { $$ =  ast_letrec($3, $5);}
| exp actual_args
    %prec prec_app
    { $$ = ast_app($1, $2); }
| elems
    { $$ = ast_tuple($1); }
| LET LPAREN pat RPAREN EQUAL exp IN exp
    { $$ = ast_lettuple($3, $6, $8); }
| simple_exp DOT LPAREN exp RPAREN LESS_MINUS exp
    { $$ = ast_put($1, $4, $7); }
| exp SEMICOLON exp
    { $$ = ast_let((id) id_gen(), $1, $3); }
| ARRAY_CREATE simple_exp simple_exp
    %prec prec_app
    { $$ = ast_array($2, $3); }
| error
    { assert(false); }

fundef:
  IDENT formal_args EQUAL exp
    {
    pfundef f = malloc(sizeof(struct fundef));
    f->var = $1;
    // f.type  TODO
    f->args = $2;
    f->body = $4;
    $$ = f;
    }

formal_args:
  IDENT formal_args
    {  
        $$ = cons($1, $2);
    }
| IDENT
    {
        $$ = cons($1, empty());
    }

actual_args:
  actual_args simple_exp
    %prec prec_app
    { 
        $$ = append($1, cons($2, empty()));
    }
| simple_exp
    %prec prec_app
    { 
       $$ = cons($1, empty());
    }

elems:
  elems COMMA exp
    {
      $$ = append($1, cons($3, empty()));
     }
| exp COMMA exp
    { 
      $$ = cons($1, cons($3, empty()));
  }

pat:
  pat COMMA IDENT
    {
      $$ = append($1, cons($3, empty()));
    }
| IDENT COMMA IDENT
    {
      $$ = cons($1, cons($3, empty()));
    }

%%


extern void yyprint (FILE *file, int ttype, YYSTYPE value); 
