#ifndef myclib_List_algos_h
#define myclib_List_algos_h

#include <myclib/list.h>

int List_bubble_sort(List *list, List_compare cmp);

List *List_merge_sort(List *list, List_compare cmp);

void List_quick_sort(List *list, List_compare cmp);

#endif
