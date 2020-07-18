#include <assert.h>
#include <stdio.h>
#include "ast.h"
#include "list.h"

void print_term(ptree t);

void print_binary(char *op, ptree t1, ptree t2) {
    printf("(");
    print_term(t1);
    printf(" %s ", op);
    print_term(t2);
    printf(")");
}

void print_id(id i) {
    printf("%s", i);
}

void print_unary(char *op, ptree t) {
    printf("(");
    printf("%s ", op);
    print_term(t);
    printf(")");
}

// precondition: list is not empty
void print_list(plist l, char *sep, void f(void *)) {
    assert(l && !is_empty(l));
    plist cur = l;
    f(head(cur));
    cur = tail(cur);
    while (!is_empty(cur)) {
        printf("%s", sep);
        f(head(cur));
        cur = tail(cur);
    }
}

void print_term(ptree t) {
    assert(t);
    switch (t->code) {
        case T_UNIT:
            printf("()");
            break;
        case T_BOOL:
            printf("%s", t->params.b?"true":"false");
            break;
        case T_INT:
            printf("%d", t->params.i);
            break;
        case T_FLOAT:
            printf("%.2f", t->params.f);
            break;
        case T_LET:
            printf("(");
            printf("let %s = ", t->params.tlet.v);
            print_term( t->params.tlet.t1);
            printf(" in ");
            print_term( t->params.tlet.t2);
            printf(")");
            break;
        case T_VAR:
            printf("%s", t->params.v);
            break;
        case T_ADD:
            print_binary("+", 
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_SUB:
            print_binary("-", 
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_FADD:
            print_binary("+.", 
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_FSUB:
            print_binary("-.", 
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_FMUL:
            print_binary("*.", 
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_FDIV:
            print_binary("/.", 
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_LE:
            print_binary("<=", 
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_EQ:
            print_binary("=", 
                    t->params.tbinary.t1,
                    t->params.tbinary.t2);
            break;
        case T_NEG:
            print_unary("-", t->params.t);
            break;
        case T_FNEG:
            print_unary("-.", t->params.t);
            break;
        case T_NOT:
            assert(t->code == T_NOT);
            assert(t->params.t->code != T_NOT);
            print_unary("not", t->params.t);
            break;
        case T_PUT:
            printf("(");
            print_term(t->params.tternary.t1);
            printf(".(");
            print_term(t->params.tternary.t2);
            printf(") <- ");
            print_term(t->params.tternary.t3);
            printf(")");
            break;
        case T_GET:
            print_term(t->params.tbinary.t1);
            printf(".(");
            print_term(t->params.tbinary.t2);
            printf(")");
            break;
        case T_ARRAY:
            printf("(Array.create ");
            print_term(t->params.tbinary.t1);
            printf(" ");
            print_term(t->params.tbinary.t2);
            printf(")");
            break;
        case T_IF:
            printf("(if ");
            print_term(t->params.tternary.t1);
            printf(" then ");
            print_term(t->params.tternary.t2);
            printf(" else ");
            print_term(t->params.tternary.t3);
            printf(")");
            break;
        case T_LETREC:
            printf("(let rec %s ", 
                    t->params.tletrec.fd->var);
        print_list(t->params.tletrec.fd->args, " ", 
                   (void *)print_id);
            printf(" = ");
            print_term(t->params.tletrec.fd->body);
            printf(" in ");
            print_term(t->params.tletrec.t);
            printf(")");
            break;
         case T_TUPLE:
            printf("(");
            print_list(t->params.ttuple.l, ", ", 
                      (void *)print_term);
            // TODO - revoir type
            printf(")");
            break;
         case T_APP:
            printf("(");
            print_term(t->params.tapp.t);
            printf(" ");
            print_list(t->params.tapp.l, " " , 
                      (void *)print_term);
            printf(")");
            break;
         case T_LETTUPLE:
            printf("(let (");
            print_list(t->params.lettuple.l, ", ", 
                      (void *)print_id);
            printf(") = ");
            print_term(t->params.lettuple.t1);
            printf(" in ");
            print_term(t->params.lettuple.t2);
            printf(")");
            break;
       default:
            printf("%d ", t->code);
            assert(false);
    } 
}
extern FILE *yyin;
extern int yydebug;
extern int yyparse(ptree *ast);

int main(int argc, char **argv) {
	FILE *file;
    if (argc != 2) {
        printf("usage: %s file name\n", argv[0]);
        return 0;
    }
	file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("cannot open file %s\n", argv[1]);
        return 0;
    }

    yyin = file;

    // yydebug = 1;
    ptree p;
    if (yyparse(&p) != 0) {
        printf("parse error");
        return 0;
    } 
    print_term(p);
    printf("\n");
    return 0;
}



