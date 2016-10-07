#include "minunit.h"
#include <lcthw/list_algos.h>
#include <string.h>
#include <time.h>

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

int is_sorted(List *list, List_compare cmp)
{
    LIST_FOREACH(list, first, next, cur) {
        if (cur->next && cmp(cur->value, cur->next->value) > 0) {
            return 0;
        }
    }

    return 1;
}

char *test_bubble_sort()
{
    List *list = create_words();

    List_bubble_sort(list, (List_compare)strcmp);
    mu_assert(is_sorted(list, (List_compare)strcmp) == 1,
            "bubble sort did not sort the list.");

    List_destroy(list);

    return NULL;
}

char *test_merge_sort()
{
    List *list = create_words();

    List *res = List_merge_sort(list, (List_compare)strcmp);
    mu_assert(is_sorted(res, (List_compare)strcmp) == 1,
            "merge sort did not sort the list.");

    List_destroy(list);
    List_destroy(res);

    return NULL;
}

char *test_quick_sort()
{
    List *list = create_words();

    List_quick_sort(list, (List_compare)strcmp);
    mu_assert(is_sorted(list, (List_compare)strcmp) == 1,
            "quick sort did not sort the list.");

    List_destroy(list);

    return NULL;
}

#define NUM_ELEMS 1000
#define NUM_TRIALS 1000

// creates list with empty nodes
List *create_array()
{
    List *list = List_create();
    int i = 0;

    for (i = 0; i < NUM_ELEMS; i++) {
        List_push(list, malloc(sizeof(int)));
    }

    return list;
}

// alloc's for each value in node
void populate_array(int **array)
{
    int i = 0;

    srand(time(0));

    for (i = 0; i < NUM_ELEMS; i++) {
        *array[i] = rand() % 10;
    }
}

char *test_sort_performance()
{
    int i = 0;
    int max_value = 100;
    clock_t start;
    clock_t end;
    double total_time_mergesort = 0;
    double  total_time_quicksort = 0;
    List *list = create_array();
    List *merge_res = NULL;

    for (i = 0; i < NUM_TRIALS; i++) {
        // give each node fresh values for each trial
        LIST_FOREACH(list, first, next, cur) {
            *(int *)cur->value = rand() % max_value;
        }

        start = clock();
        merge_res = List_merge_sort(list, (List_compare)strcmp);
        end = clock();

        total_time_mergesort += (double)(end - start) / CLOCKS_PER_SEC;

        start = clock();
        List_quick_sort(list, (List_compare)strcmp);
        end = clock();

        total_time_quicksort += (double)(end - start) / CLOCKS_PER_SEC;
    }

    double result_merge = total_time_mergesort / NUM_TRIALS;
    double result_quick = total_time_quicksort / NUM_TRIALS;
    debug("%d elements sorted in %d trials", NUM_ELEMS, NUM_TRIALS);
    debug("average time for merge sort: %f", result_merge);
    debug("average time for quick sort: %f", result_quick);

    List_clear(list);
    List_destroy(list);

    return NULL;
}


char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);
    mu_run_test(test_quick_sort);
    mu_run_test(test_sort_performance);

    return NULL;
}

RUN_TESTS(all_tests);
