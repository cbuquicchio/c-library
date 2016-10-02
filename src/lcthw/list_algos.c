#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

static void ListNode_swap(ListNode *a, ListNode *b)
{
    void *temp = a->value;

    a->value = b->value;
    b->value = temp;
}

int List_bubble_sort(List *list, List_compare cmp)
{
    check(list != NULL, "cannot compare a NULL list.");

    // avoid sorting an empty list or list of one
    if (List_count(list) <= 0) {
        return 0;
    }

    int sorted = 0;

    while (!sorted) {
        sorted = 1;

        LIST_FOREACH(list, first, next, cur) {
            // avoid performing a compare/swap on the final node
            if (cur->next) {
                if (cmp(cur->value, cur->next->value) > 0) {
                    ListNode_swap(cur, cur->next);
                    sorted = 0;
                }
            }
        }
    }

    return 0;

error:
    return -1;
}

static void List_split(List *source, List *left, List *right)
{
    int mid = List_count(source) / 2;
    int count = 0;

    // split list in to left and right
    LIST_FOREACH(source, first, next, cur) {
        if (count < mid) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }

        count++;
    }
}

static List *List_merge(List *left, List *right, List_compare cmp)
{
    List *result = List_create();
    void *value = NULL;

    while (List_count(left) > 0 || List_count(right) > 0) {
        if (List_count(left) > 0 && List_count(right) > 0) {
            if (cmp(left->first->value, right->first->value) > 0) {
                value = List_shift(right);
            } else {
                value = List_shift(left);
            }

            List_push(result, value);
        } else if (List_count(left) > 0) {
            value = List_shift(left);
            List_push(result, value);
        } else if (List_count(right) > 0) {
            value = List_shift(right);
            List_push(result, value);
        }
    }

    return result;
}

List *List_merge_sort(List *list, List_compare cmp)
{
    if (List_count(list) <= 1) {
        return list;
    }

    List *left = List_create();
    List *right = List_create();

    List_split(list, left, right);

    List *left_sorted = List_merge_sort(left, cmp);
    List *right_sorted = List_merge_sort(right, cmp);

    if (left != left_sorted) {
        List_destroy(left);
    }

    if (right != right_sorted) {
        List_destroy(right);
    }

    List *result = List_merge(left_sorted, right_sorted, cmp);

    List_destroy(left_sorted);
    List_destroy(right_sorted);

    return result;
}
