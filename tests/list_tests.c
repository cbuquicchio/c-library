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
    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_destroy);
    mu_run_test(test_push);
    mu_run_test(test_unshift);
    mu_run_test(test_shift);

    return NULL;
}

RUN_TESTS(all_tests);
