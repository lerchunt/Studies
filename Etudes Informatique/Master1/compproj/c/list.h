#ifndef __LIST_H
#define __LIST_H

#include <stdbool.h>

typedef struct _listNode {
  void *data;
  struct _listNode *next;
} listNode;
 
typedef struct {
  int logicalLength;
  listNode *head;
} list;

typedef list *plist;
 
plist empty();
 
plist cons(void *element, plist l);

int list_size(plist l);
 
void *head(plist l);
plist tail(plist l);
plist append(plist l1, plist l2);
bool is_empty(plist l);
 
#endif
