#include <myclib/vector.h>
#include <myclib/dbg.h>
#include <stdlib.h>

Vector *Vector_create(size_t element_size, size_t initial_max)
{
    check(element_size > 0, "element_size must be > 0.");
    check(initial_max > 0, "initial_max must be > 0.");

    Vector *array = calloc(1, sizeof(Vector));
    check_mem(array);

    array->contents = calloc(initial_max, sizeof(void *));
    check_mem(array->contents);

    array->element_size = element_size;
    array->expand_rate = DEFAULT_EXPAND_RATE;
    array->max = initial_max;
    array->size = 0;


    return array;

error:
    if (array) {
        free(array);
    }

    return NULL;
}

void Vector_destroy(Vector *array)
{
    if (array) {
        if (array->contents) {
            free(array->contents);
        }

        free(array);
    }
}

void Vector_clear(Vector *array)
{
    int i = 0;

    if (array->element_size > 0) {
        for (i = 0; i < array->max; i++) {
            if (array->contents) {
                array->contents[i] = NULL;
                free(array->contents[i]);
            }
        }
    }
}

static inline int Vector_resize(Vector *array, size_t new_max)
{
    void **new_contents = calloc(new_max, sizeof(void *));
    check_mem(new_contents);

    int i = 0;
    int upper_limit = (int)new_max < Vector_max(array) ?
        (int)new_max : Vector_max(array);

    for (i = 0; i < upper_limit; i++) {
        new_contents[i] = array->contents[i];
    }

    free(array->contents);
    array->contents = new_contents;
    array->max = new_max;

    return 0;

error:
    return -1;
}

int Vector_expand(Vector *array)
{
    size_t new_max = array->max + array->expand_rate;
    int res = Vector_resize(array, new_max);
    check(res == 0, "Vector did not resize for expand.");

    return 0;

error:
    return -1;
}

int Vector_contract(Vector *array)
{
    size_t new_max = array->size < (int)array->expand_rate ?
        (int)array->expand_rate : array->size;
    int res = Vector_resize(array, new_max);
    check(res == 0, "Vector did not resize for contract.");

    return 0;

error:
    return -1;
}

int Vector_push(Vector *array, void *el)
{
    check(array, "Cannot push onto undefined vector.");
    int res = 0;

    if (Vector_size(array) == Vector_max(array)) {
        res = Vector_expand(array);
    }

    check(res == 0, "Could not push onto vector, expansion failed.");

    Vector_set(array, Vector_size(array), el);
    array->size++;

    return 0;

error:
    return -1;
}

void *Vector_pop(Vector *array)
{
    check(array, "Cannot pop off of undefined vector.");
    check(array->size - 1 >= 0, "Cannot pop off of empty vector.");

    void *el = Vector_remove(array, array->size - 1);
    array->size--;

    if (Vector_size(array) > (int)array->expand_rate
        && Vector_size(array) % (int)array->expand_rate)
    {
        Vector_contract(array);
    }

    return el;

error:
    return NULL;
}


