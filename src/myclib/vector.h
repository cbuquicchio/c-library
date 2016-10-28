#ifndef myclib_Vector_h
#define myclib_Vector_h
#include <stdlib.h>
#include <assert.h>
#include <myclib/dbg.h>

typedef struct Vector {
    size_t end;
    size_t element_size;
    size_t expand_rate;
    size_t max;
    void **contents;
} Vector;

typedef int (*Vector_compare) (const void *a, const void *b);

Vector *Vector_create(size_t element_size, size_t initial_max);

void Vector_destroy(Vector *array);

void Vector_clear(Vector *array);

int Vector_expand(Vector *array);

int Vector_contract(Vector *array);

int Vector_push(Vector *array, void *el);

void *Vector_pop(Vector *array);

void Vector_clear_destroy(Vector *array);

#define Vector_last(A) ((A)->contents[(A)->end - 1])
#define Vector_first(A) ((A)->contents[0])
#define Vector_count(A) ((A)->end)
#define Vector_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 300

static inline void Vector_set(Vector *array, size_t i, void *el)
{
    check(i < array->max, "vector attempt to set past max.");

    if (i > array->end) {
	array->end = i + 1;
    }

    array->contents[i] = el;

error:
    return;
}

static inline void *Vector_get(Vector *array, size_t i)
{
    check (i < array->max, "vector attempt to get past max.");

    return array->contents[i];

error:
    return NULL;
}

static inline void *Vector_remove(Vector *array, size_t i)
{
    void *el = array->contents[i];

    array->contents[i] = NULL;

    return el;
}

static inline void *Vector_new(Vector *array)
{
    check(array->element_size > 0,
      "Can't use Vector_new on 0 size vectors.");

    return calloc(1, array->element_size);

error:
    return NULL;
}

#define Vector_free(E) free(E);

#endif
