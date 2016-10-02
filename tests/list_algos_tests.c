#include "minunit.h"
#include <lcthw/list_algos.h>
#include <string.h>

char *values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS" };

#define NUM_VALUES 5

List *create_words()
{
    int i = 0;
    List *words = List_create();

    for (i = 0; i < NUM_VALUES; i++) {
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List *words)
{
    LIST_FOREACH(words, first, next, cur) {
        if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char *)cur->value,
                    (char *)cur->next->value);
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort()
{
    List *list = create_words();

    List_bubble_sort(list, (List_compare)strcmp);
    mu_assert(is_sorted(list) == 1, "bubble sort did not sort the list.");

    List_destroy(list);

    return NULL;
}

char *test_merge_sort()
{
    List *list = create_words();

    List *res = List_merge_sort(list, (List_compare)strcmp);
    mu_assert(is_sorted(res) == 1, "merge sort did not sort the list.");

    List_destroy(list);
    List_destroy(res);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);
