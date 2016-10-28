#include <stdlib.h>
#include <time.h>
#include <myclib/vector.h>
#include <myclib/dbg.h>

static size_t qsort_partition(size_t start, size_t end, void **contents,
        Vector_compare cmp)
{
    // need to optimize pivot selection
    size_t pivot = rand() % end;
    size_t wall = start;
    size_t i = 0;
    void *temp = NULL;

    for (i = start; i < end; i++) {
        if (cmp(contents[i], contents[pivot]) < 0) {
            temp = contents[i];
            contents[i] = contents[wall];
            contents[wall] = temp;
            wall++;
        }
    }

    temp = contents[pivot];
    contents[pivot] = contents[wall];
    contents[wall] = temp;

    return wall;
}

static void qsort_recur(size_t start, size_t end, void **contents,
        Vector_compare cmp)
{
    if (start >= end) {
        return;
    }

    // partition return index of wall el
    size_t pivot = qsort_partition(start, end, contents, cmp);
    size_t new_start = pivot + 1;

    // handle decrementing unsigned type
    size_t new_end = pivot == 0 ? 0 : pivot - 1;

    // sort left of partition
    qsort_recur(start, new_end, contents, cmp);

    // sort right of partition
    qsort_recur(new_start, end, contents, cmp);
}

void Vector_quick_sort(Vector *array, Vector_compare cmp)
{
    srand(time(0));
    qsort_recur(0, array->end - 1, array->contents, cmp);
}
