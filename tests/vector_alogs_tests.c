#include <stdlib.h>
#include <time.h>
#include "minunit.h"
#include <myclib/vector_algos.h>

#define VECTOR_SIZE 5000
#define MAX_NUM 100

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

    srand(time(0));

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
    Vector *array = construct_Vector();

    Vector_quick_sort(array, (Vector_compare)intcmp);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(vector_quicksort_test);

    return NULL;
}

RUN_TESTS(all_tests);
