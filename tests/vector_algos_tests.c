#include <stdlib.h>
#include <time.h>
#include "minunit.h"
#include <myclib/vector_algos.h>

#define VECTOR_SIZE 1000
#define MAX_NUM 1000

int is_sorted(Vector *array, Vector_compare cmp)
{
    size_t i = 0;

    for (i = 1; i < array->end; i++) {
        if (cmp(array->contents[i], array->contents[i - 1]) < 0) {
            return 0;
        }
    }

    return 1;
}

Vector *construct_Vector()
{
    Vector *array = Vector_create(sizeof(int), VECTOR_SIZE);

    srand(131234);

    while (array->end < VECTOR_SIZE) {
        int *new_el = (int *)Vector_new(array);
        *new_el = rand() % MAX_NUM;
        Vector_push(array, new_el);
    }

    return array;
}

int intcmp(const int *a, const int *b)
{
    if (*a < *b) {
        return -1;
    } else if (*b < *a) {
        return 1;
    }

    return 0;
}

char *vector_quicksort_test()
{
    int res = 0;
    Vector *array = construct_Vector();

    Vector_quick_sort(array, (Vector_compare)intcmp);
    res = is_sorted(array, (Vector_compare)intcmp);

    mu_assert(res == 1, "Vector was not sorted.");

    Vector_clear_destroy(array);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(vector_quicksort_test);

    return NULL;
}

RUN_TESTS(all_tests);
