#include <myclib/vector.h>
#include <myclib/dbg.h>
#include <stdlib.h>

Vector *Vector_create(size_t elem_size, size_t init_max)
{
    Vector *array = malloc(sizeof(Vector));
    check_mem(array);

    array->contents = calloc(init_max, sizeof(void *));
    check_mem(array->contents);

    array->end = 0;
    array->max = init_max;
    array->element_size = elem_size;
    array->expand_rate = DEFAULT_EXPAND_RATE;

    return array;

error:
    if (array) {
        if (array->contents){
            free(array->contents);
        }

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
    if (array) {
        if (array->contents) {
            size_t i = 0;

            for (i = 0; i < array->max; i++) {
                if (array->contents[i] != NULL) {
                    free(array->contents[i]);
                }
            }
        }
    }
}

void Vector_clear_destroy(Vector *array)
{
    Vector_clear(array);
    Vector_destroy(array);
}

static int Vector_resize(Vector *array, size_t new_size)
{
    check(array != NULL, "Cannot resize NULL vector.");
    check(new_size != 0, "Cannot resize to zero.");

    void *new_contents = realloc(array->contents, new_size * sizeof(void *));
    check_mem(new_contents);

    array->contents = new_contents;
    array->max = new_size;

    return 0;

error:
    return -1;
}

int Vector_expand(Vector *array)
{
    check(array != NULL, "Cannot resize NULL Vector.");

    int res = Vector_resize(array, array->max + array->expand_rate);
    check(res == 0, "Vector did not resize");

    memset(array->contents + (array-> max - array->expand_rate),
                0, array->expand_rate);

    return 0;

error:
    return -1;
}

int Vector_contract(Vector *array)
{
    check(array != NULL, "Cannot resize NULL Vector.");

    int res = Vector_resize(array, array->end);
    check(res == 0, "Vector did not resize.");

    return 0;

error:
    return -1;
}

int Vector_push(Vector *array, void *el)
{
    check(array != NULL, "Cannot push onto NULL Vector.");

    array->contents[array->end] = el;
    array->end++;

    if (array->end == array->max) {
        return Vector_expand(array);
    }

    return 0;

error:
    return -1;
}

void *Vector_pop(Vector *array)
{
    check(array != NULL, "Cannot pop off of NULL Vector.");
    check(array->end > 0, "Attempted to pop off of empty Vector.");

    void *el = Vector_remove(array, array->end - 1);
    array->end--;

    if (array->end > array->expand_rate &&
            array->end % array->expand_rate) {
        Vector_contract(array);
    }

    return el;

error:
    return NULL;
}
