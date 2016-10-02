#include "minunit.h"
#include <lcthw/list.h>

char *test1 = "test one";
char *test2 = "test two";
char *test3 = "test three";

char *test_create()
{
    List *list = List_create();

    mu_assert(list != NULL, "list was not created.");

    free(list);

    return NULL;
}

char *test_destroy()
{
    List *list = List_create();
    List_destroy(list);

    return NULL;
}

char *test_clear()
{
    int *one = malloc(sizeof(int));
    int *two = malloc(sizeof(int));
    int *three = malloc(sizeof(int));
    List *list = List_create();
    ListNode *node_one = malloc(sizeof(ListNode));
    ListNode *node_two = malloc(sizeof(ListNode));
    ListNode *node_three = malloc(sizeof(ListNode));

    *one = 1;
    *two = 2;
    *three = 3;

    node_one->value = one;
    node_two->value = two;
    node_three->value = three;

    list->first = node_one;
    list->last = node_three;

    node_one->prev = NULL;
    node_one->next = node_two;
    node_two->prev = node_one;
    node_two->next = node_three;
    node_three->prev = node_two;
    node_three->next = NULL;

    List_clear(list);

    LIST_FOREACH(list, first, next, cur) {
        mu_assert(cur->value == NULL, "the node value was not cleared.");
    }

    List_destroy(list);

    return NULL;
}

char *test_push()
{
    List *list = List_create();
    char *value = NULL;

    List_push(list, test1);
    mu_assert(list->last->value == test1, "node not pushed onto list.");

    List_push(list, test2);
    mu_assert(list->last->value == test2, "node not pushed onto list.");

    List_push(list, test3);
    mu_assert(list->last->value == test3, "node not pushed onto list.");
    mu_assert(list->count == 3, "list count not updated after push.");

    value = List_pop(list);
    mu_assert(value == test3, "node not popped off of list.");

    value = List_pop(list);
    mu_assert(value == test2, "node not popped off of list.");

    value = List_pop(list);
    mu_assert(value == test1, "node not popped off of list.");

    mu_assert(list->count == 0, "list count not updated after pop.");

    List_destroy(list);

    return NULL;
}

char *test_unshift()
{
    List *list = List_create();

    List_unshift(list, test1);

    mu_assert(list->first->value == test1, "wrong first value after unshift.");
    mu_assert(list->count == 1, "List count was not correctly updated after unshift.");

    List_unshift(list, test2);

    mu_assert(list->first->value == test2, "wrong first value after unshift.");
    mu_assert(list->count == 2, "List count was not correctly updated after unshift.");

    List_destroy(list);

    return NULL;
}

char *test_shift()
{
    List *list = List_create();
    char *value = NULL;

    List_push(list, test1);
    List_push(list, test2);
    List_push(list, test3);

    value = List_shift(list);
    mu_assert(value == test1, "did not shift the correct value.");

    value = List_shift(list);
    mu_assert(value == test2, "did not shift the correct value.");

    value = List_shift(list);
    mu_assert(value == test3, "did not shift the correct value.");

    List_destroy(list);

    return NULL;
}

/*
 * Only need to test the middle because pop and unshift
 * test removed from the first and last elements in the
 * list
 */
char *test_remove_middle()
{
    List *list = List_create();
    List_push(list, test1);
    List_push(list, test2);
    List_push(list, test3);

    char *value = List_remove(list, list->first->next);

    mu_assert(value == test2, "node was not removed correctly.");
    mu_assert(List_count(list) == 2, "list count was not decremented.");

    List_destroy(list);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_destroy);
    mu_run_test(test_clear);
    mu_run_test(test_push);
    mu_run_test(test_unshift);
    mu_run_test(test_shift);
    mu_run_test(test_remove_middle);

    return NULL;
}

RUN_TESTS(all_tests);
