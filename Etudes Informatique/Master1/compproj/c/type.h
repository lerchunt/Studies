#ifndef __TYPE_H
#define __TYPE_H

enum TCode {
    TY_UNIT,
    TY_BOOL,
    TY_INT,
    TY_FLOAT,
    TY_FUN,
    TY_TUPLE,
    TY_ARRAY,
    TY_VAR
};

typedef struct {
    enum TCode code;
    union {
      char *var;
     // TODO
    } params;
} type;

typedef type *ptype;

ptype gentvar();

#endif

