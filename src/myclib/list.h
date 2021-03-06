#ifndef myclib_List_h
#define myclib_List_h

struct ListNode;

typedef struct ListNode {
  struct ListNode *next;
  struct ListNode *prev;
  void *value;
} ListNode;

typedef struct List {
  int count;
  struct ListNode *first;
  struct ListNode *last;
} List;

typedef int (*List_compare) (const void *a, const void *b);

List *List_create();
void List_destroy(List *list);
void List_clear(List *list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List *list, void *value);
void *List_pop(List *list);

void List_unshift(List *list, void *value);
void *List_shift(List *list);

void *List_remove(List *list, ListNode *node);

void List_split(List *source, List *left, List *right, int pivot);
List *List_merge(List *left, List *right, List_compare cmp);

#define LIST_FOREACH(L, S, N, C) ListNode *_node = NULL;\
                                                   ListNode *C = NULL;\
for(C = _node = L->S; _node != NULL; C = _node = _node->N)

#endif
