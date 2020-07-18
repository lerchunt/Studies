#ifndef __AST_H
#define __AST_H

#include <stdbool.h>
#include "list.h"
#include "type.h"

typedef char *id;

enum code {
    T_UNIT,
    T_BOOL,
    T_INT,
    T_FLOAT,
    T_NOT,
    T_NEG,
    T_ADD,
    T_SUB,
    T_FNEG,
    T_FADD,
    T_FSUB,
    T_FMUL,
    T_FDIV,
    T_EQ,
    T_LE,
    T_IF,
    T_LET,
    T_VAR,
    T_LETREC,
    T_APP,
    T_TUPLE,
    T_LETTUPLE,
    T_ARRAY,
    T_GET,
    T_PUT
};

struct tree_;

struct fundef {
    id var;
    type t;
    plist args; 
    struct tree_ *body;
};

typedef struct fundef *pfundef;

typedef struct tree_ {
  enum code code;
  union {
      bool b;
      int i;
      float f;
      id v;
      struct tree_ *t;
      struct {
          struct tree_ *t1;
          struct tree_ *t2;
      } tbinary;
      struct {
          struct tree_ *t1;
          struct tree_ *t2;
          struct tree_ *t3;
      } tternary;
      struct {
          id v;
          ptype t;
          struct tree_ *t1;
          struct tree_ *t2;
      } tlet;
      struct {
          pfundef fd;
          struct tree_ *t;
      } tletrec;
      struct {
          plist l;
      } ttuple;
      struct {
          struct tree_ *t;
          plist l;
      } tapp;
      struct {
          plist l;
          struct tree_ *t1;
          struct tree_ *t2;
      } lettuple;
  } params; 
} tree; 

typedef tree *ptree;

ptree ast_var(id v);

ptree ast_unit();

ptree ast_let(id v, ptree t1, ptree t2);

ptree ast_integ(int i);

ptree ast_float(float f);

ptree ast_bool(bool b);

ptree ast_not(ptree t);

ptree ast_neg(ptree t);

ptree ast_fneg(ptree t);

ptree ast_add(ptree t1, ptree t2);

ptree ast_sub(ptree t1, ptree t2);

ptree ast_fadd(ptree t1, ptree t2);

ptree ast_fsub(ptree t1, ptree t2);

ptree ast_fmul(ptree t1, ptree t2);

ptree ast_fdiv(ptree t1, ptree t2);

ptree ast_eq(ptree t1, ptree t2);

ptree ast_array(ptree t1, ptree t2);

ptree ast_get(ptree t1, ptree t2);

ptree ast_le(ptree t1, ptree t2);

ptree ast_app(ptree t1, plist l);

ptree ast_if(ptree t1, ptree t2, ptree t3);

ptree ast_put(ptree t1, ptree t2, ptree t3);

ptree ast_tuple(plist l);

ptree ast_lettuple(plist l, ptree t1, ptree t2);

ptree ast_letrec(pfundef fd, ptree t1);

id id_gen();
#endif
