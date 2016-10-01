#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <stdlib.h>

List *List_create()
{
    List *list = calloc(1, sizeof(List));

    list->first = NULL;
    list->last = NULL;
    list->count = 0;

    return list;
}

void List_destroy(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void List_push(List *list, void *value)
{
    check(list != NULL, "List is NULL cannot perform push.");

    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List *list)
{
    check(list != NULL, "List is NULL cannot perform pop.");

    ListNode *node = list->last;
    void *value = node->value;

    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        list->last->next = NULL;
    }

    list->count--;

    free(node);

    return value;

error:
    return NULL;
}

void List_unshift(List *list, void *value)
{
    check(list != NULL, "Cannot unshift on NULL list.");

    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL && list->last == NULL) {
        list->first = node;
        list->last = node;
        node->prev = NULL;
        node->next = NULL;
    } else {
        list->first->prev = node;
        node->next = list->first;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list)
{
    check(list != NULL, "Cannot shift a NULL list.");

    ListNode *node = list->first;
    void *value = node->value;

    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    }

    list->count--;
    free(node);

    return value;

error:
    return NULL;
}
