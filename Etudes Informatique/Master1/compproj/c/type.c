#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "ast.h"

#define MAX_BUF 6

char buffer[MAX_BUF];

ptype gentvar() {
    static int cnt = 0;
    ptype res = malloc(sizeof(type));
    res->code = TY_VAR; 
    buffer[0] = '?';
    buffer[1] = 't';
    res->params.var = malloc(sizeof(buffer)); 
    sprintf(buffer+2, "%d", cnt);
    strcpy(res->params.var, buffer);
    cnt++;
    return res;
}

