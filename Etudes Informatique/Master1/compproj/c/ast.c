#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "type.h"
#include "ast.h"
#include "assert.h"
#include "string.h"

#define MAX_ID 10 

char buffer[MAX_ID];

id id_gen() {
    buffer[0] = '?';
    buffer[1] = 'v';
    static int cnt = 0;
    sprintf(buffer+2, "%d", cnt);
    char *res = malloc(sizeof(buffer)); 
    strcpy(res, buffer);
    cnt++;
    return res;
}

ptree ast_var(id v) {
    ptree t = malloc(sizeof(tree));
    t->code = T_VAR;
    t->params.v = v;
    return t;
}

ptree ast_unit() {
    ptree t = malloc(sizeof(tree));
    t->code = T_UNIT;
    return t;
}

ptree ast_let(id v, ptree t1, ptree t2) {
    ptree t = malloc(sizeof(tree));
    t->code = T_LET;
    t->params.tlet.v = v;
    t->params.tlet.t = gentvar(); 
    t->params.tlet.t1 = t1;
    t->params.tlet.t2 = t2;
    return t;
}

ptree ast_integ(int i) {
    ptree t = malloc(sizeof(tree));
    t->code = T_INT;
    t->params.i = i;
    return t;
}

ptree ast_float(float f) {
    ptree t = malloc(sizeof(tree));
    t->code = T_FLOAT;
    t->params.f = f;
    return t;
}

ptree ast_bool(bool b) {
    ptree t = malloc(sizeof(tree));
    t->code = T_BOOL;
    t->params.b = b;
    return t;
}

#define ptree_unary(CODE,t)  (\
        {ptree t2 = malloc(sizeof(tree));\
        t2->code = CODE;\
        t2->params.t = t;\
        return t2;})
// TODO; why bug if t instead of t2

#define ptree_binary(CODE,t1,t2)  (\
        {ptree t = malloc(sizeof(tree));\
        t->code = CODE;\
        t->params.tbinary.t1 = t1;\
        t->params.tbinary.t2 = t2;\
        return t;})

#define ptree_ternary(CODE,t1,t2,t3)  (\
        {ptree t = malloc(sizeof(tree));\
        t->code = CODE;\
        t->params.tternary.t1 = t1;\
        t->params.tternary.t2 = t2;\
        t->params.tternary.t3 = t3;\
        return t;})

ptree ast_not(ptree t) {
    ptree_unary(T_NOT, t);
}

ptree ast_neg(ptree t) {
    ptree_unary(T_NEG,t);
}

ptree ast_fneg(ptree t) {
    ptree_unary(T_FNEG,t);
}

ptree ast_add(ptree t1, ptree t2) {
    ptree_binary(T_ADD,t1,t2);
}

ptree ast_sub(ptree t1, ptree t2) {
    ptree_binary(T_SUB, t1, t2);
}

ptree ast_fadd(ptree t1, ptree t2) {
    ptree_binary(T_FADD, t1, t2);
}

ptree ast_fsub(ptree t1, ptree t2) {
    ptree_binary(T_FSUB, t1, t2);
}

ptree ast_fmul(ptree t1, ptree t2) {
    ptree_binary(T_FMUL, t1, t2);
}

ptree ast_fdiv(ptree t1, ptree t2) {
    ptree_binary(T_FDIV, t1, t2);
}

ptree ast_eq(ptree t1, ptree t2) {
    ptree_binary(T_EQ, t1, t2);
}

ptree ast_array(ptree t1, ptree t2) {
    ptree_binary(T_ARRAY, t1, t2);
}

ptree ast_get(ptree t1, ptree t2) {
    ptree_binary(T_GET, t1, t2);
}

ptree ast_le(ptree t1, ptree t2) {
    ptree_binary(T_LE, t1, t2);
}

ptree ast_if(ptree t1, ptree t2, ptree t3) {
    ptree_ternary(T_IF, t1, t2, t3);
}

ptree ast_put(ptree t1, ptree t2, ptree t3) {
    ptree_ternary(T_PUT, t1, t2, t3);
}

ptree ast_app(ptree t1, plist l) {
    ptree t = malloc(sizeof(tree));
    t->code = T_APP;
    t->params.tapp.t = t1; 
    t->params.tapp.l = l;
    return t;
}

ptree ast_tuple(plist l) {
    ptree t = malloc(sizeof(tree));
    t->code = T_TUPLE;
    t->params.ttuple.l = l;
    return t;
}

ptree ast_lettuple(plist l, ptree t1, ptree t2) {
    ptree t = malloc(sizeof(tree));
    t->code = T_LETTUPLE;
    t->params.lettuple.l = l;
    t->params.lettuple.t1 = t1;
    t->params.lettuple.t2 = t2;
    return t;
}

ptree ast_letrec(pfundef fd, ptree t1) {
    ptree t = malloc(sizeof(tree));
    t->code = T_LETREC;
    t->params.tletrec.fd = fd;
    t->params.tletrec.t = t1;
    return t;
}
 
