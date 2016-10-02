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

void List_clear(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
        cur->value = NULL;
    }
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
    return list->last != NULL ? List_remove(list, node) : NULL;

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
    return node != NULL ? List_remove(list, node) : NULL;

error:
    return NULL;
}

void *List_remove(List *list, ListNode *node)
{
    check(list != NULL, "Cannot remove from NULL list.");
    check(node != NULL, "Cannot remove NULL node from list.");

    void *value = node->value;

    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        list->first = node->next;
        check(list->first != NULL,
                "Invalid list, somehow got a first that is NULL.");
        node->next->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL,
                "Ivalid list, somehow got a last that is NULL.");
        node->prev->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    list->count--;
    free(node);

    return value;

error:
    return NULL;
}

void List_split(List *source, List *left, List *right, int pivot)
{
    int count = 0;

    LIST_FOREACH(source, first, next, cur) {
        if (count < pivot) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }

        count++;
    }
}

List *List_merge(List *left, List *right, List_compare cmp)
{
    List *result = List_create();
    void *value = NULL;

    while (List_count(left) > 0 || List_count(right) > 0) {
        if (List_count(left) > 0 && List_count(right) > 0) {
            if (cmp(left->first->value, right->first->value) > 0) {
                value = List_shift(right);
            } else {
                value = List_shift(left);
            }

            List_push(result, value);
        } else if (List_count(left) > 0) {
            value = List_shift(left);
            List_push(result, value);
        } else if (List_count(right) > 0) {
            value = List_shift(right);
            List_push(result, value);
        }
    }

    return result;
}
