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
    int skips = 0;
    int i = 0;

    while (!sorted) {
        sorted = 1;
        i = 1;

        LIST_FOREACH(list, first, next, cur) {
            // avoid performing a compare/swap on the final node
            if (cur->next) {
                if (cmp(cur->value, cur->next->value) > 0) {
                    ListNode_swap(cur, cur->next);
                    sorted = 0;

                    if (i == List_count(list) - skips - 1) {
                        skips++;
                        break;
                    }
                }
            }

            i++;
        }
    }

    return 0;

error:
    return -1;
}

List *List_merge_sort(List *list, List_compare cmp)
{
    if (List_count(list) <= 1) {
        return list;
    }

    List *left = List_create();
    List *right = List_create();
    int mid = List_count(list) / 2;

    List_split(list, left, right, mid);

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

static ListNode *partition(ListNode *start, ListNode *end, List_compare cmp)
{
	ListNode *pivot = end;
	ListNode *last_high = start;
	ListNode *cur = start;

	while (cur) {
		if (cmp(cur->value, pivot->value) < 0) {
			ListNode_swap(cur, last_high);
			last_high = last_high->next;
		}

		cur = cur->next;
	}

	ListNode_swap(last_high, pivot);

	return last_high;
}

static void quick_sort_recur(ListNode *start, ListNode *end, List_compare cmp)
{
	if (start == end) return;
	if (end == start->prev) return;

	ListNode *p = partition(start, end, cmp);
	quick_sort_recur(start, p->prev, cmp);
	quick_sort_recur(p->next, end, cmp);
}

void List_quick_sort(List *list, List_compare cmp)
{
    check(list != NULL, "cannot perform quicksort on NULL list.");

    quick_sort_recur(list->first, list->last, cmp);

error:
    return;
}
