#include "minunit.h"
#include <myclib/vector.h>

Vector *array = NULL;

char *test_vector_create()
{
    size_t elem_size = sizeof(int);
    size_t max = 10;
    array = Vector_create(elem_size, max);

    mu_assert(array != NULL, "Vector should not be NULL.");
    mu_assert(array->end == 0, "Vector.end not set.");
    mu_assert(array->element_size == elem_size,
            "Vector.element_size not set.");
    mu_assert(array->max == max, "Vector.max not set.");

    free(array->contents);
    free(array);

    return NULL;
}

char *test_vector_destroy()
{
    array = Vector_create(sizeof(int), (size_t)10);

    Vector_destroy(array);

    return NULL;
}

char *test_vector_clear()
{
    array = Vector_create(sizeof(int), (size_t)10);

    Vector_clear(array);
    Vector_destroy(array);

    return NULL;
}

char *test_vector_expand()
{
    int res = 0;

    array = Vector_create(sizeof(int), (size_t)10);
    res = Vector_expand(array);

    mu_assert(res == 0, "Vector contents were not expanded.");
    mu_assert(array->max == 310, "Vector max was not increased.");

    Vector_clear_destroy(array);

    return NULL;
}

char *test_vector_contract()
{
    int res = 0;

    array = Vector_create(sizeof(int), (size_t)5);
    array->end = 3; // simulate a partially full array
    res = Vector_contract(array);

    mu_assert(res == 0, "Vector contents did not contract.");
    mu_assert(array->max = 3, "Vector max was not decreased.");

    Vector_clear_destroy(array);

    return NULL;
}

char *test_vector_push_pop()
{
    int i = 0;
    Vector *array = Vector_create(sizeof(int), 500);

    for (i = 0; i < 1000; i++) {
        int *val = Vector_new(array);
        *val = i;
        Vector_push(array, val);
    }

    for (i = 999; i <= 0; i++) {
        int *val = Vector_pop(array);
        mu_assert(val != NULL, "not good.");
        mu_assert(*val == i, "not good.");
        Vector_free(val);
    }

    mu_assert(array->max == 1100, "not good.");

    Vector_clear_destroy(array);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_vector_create);
    mu_run_test(test_vector_destroy);
    mu_run_test(test_vector_clear);
    mu_run_test(test_vector_expand);
    mu_run_test(test_vector_contract);
    mu_run_test(test_vector_push_pop);

    return NULL;
}

RUN_TESTS(all_tests);
