#include "minunit.h"
#include <lcthw/vector.h>

char *test_vector_create()
{
	size_t elem_size = sizeof(int *);
	size_t max_elems = 100;
	Vector *vector = Vector_create(elem_size, max_elems);

	mu_assert(vector != NULL, "Vector_create did not create a vector.");
	mu_assert(vector->contents != NULL,
			"Vector_create did set the contents.");
	mu_assert(vector->max == (int)max_elems,
	"Vector_create did not set the correct max.");
	mu_assert(vector->expand_rate == DEFAULT_EXPAND_RATE,
	"Vector_create did not set the correct expand_rate.");
	mu_assert(vector->element_size == elem_size,
	"Vector_create did not set the correct element_size.");
	mu_assert(vector->size == 0,
	"Vector_create did not set the size correctly.");

	free(vector->contents);
	free(vector);

return NULL;
}

char *test_vector_destroy()
{
	Vector *vector = Vector_create(sizeof(int), 100);
	Vector_destroy(vector);

	return NULL;
}

char *test_vector_clear()
{
	Vector *vector = Vector_create(sizeof(int), 100);
	Vector_clear(vector);
	Vector_destroy(vector);

	return NULL;
}

char *test_vector_new()
{
	Vector *vector = Vector_create(sizeof(int), 100);
	int val1 = NULL;
	int val2 = NULL;

	val1 = Vector_new(vector);
	mu_assert(val1 != NULL, "failed to make a new element.");

	val2 = Vector_new(vector);
	mu_assert(val1 != NULL, "failed to make a new element.");

	free(val1);
	free(val2);
	Vector_destroy(vector);

	return NULL;
}

char *test_vector_get_set()
{
	Vector *vector = Vector_create(sizeof(int), 10);
	int vals[] = { 1, 2 };

	Vector_set(vector, 7, &vals[0]);
	Vector_set(vector, 2, &vals[1]);

	mu_assert(*(int *)Vector_get(vector, 7) == vals[0],
			"Vector get did not retrieve the correct value.");
	mu_assert(*(int *)Vector_get(vector, 2) == vals[1],
			"Vector get did not retrieve the correct value.");

	Vector_destroy(vector);

	return NULL;
}

char *test_vector_expand()
{
	Vector *vector = Vector_create(sizeof(int), 100);
	int res = Vector_expand(vector);

	mu_assert(vector->max == 100 + (int)vector->expand_rate,
		"Vector_expand did not set the new max.");
	mu_assert(res == 0, "Vector_expand did not expand the contents.");

	Vector_destroy(vector);

	return NULL;
}

char *test_vector_contract()
{
	Vector *vector = Vector_create(sizeof(int), 100);
	int res = 0;

	res = Vector_contract(vector);

	mu_assert(res == 0, "Vector did not contract.");
	mu_assert(vector->max == (int)vector->expand_rate,
			"Vector did not contract to the correct size.");

	Vector_destroy(vector);

	vector = Vector_create(sizeof(int), 1000);
	vector->size = vector->expand_rate + 1;
	res = Vector_contract(vector);

	mu_assert(res == 0, "Vector did not contract.");
	mu_assert(vector->max == vector->size,
			"Vector did not contract to the correct size.");

	Vector_destroy(vector);

	return NULL;
}

char *test_vector_push_pop()
{
	Vector *vector = Vector_create(sizeof(int), 2);
	int vals[] = { 1, 2, 3 };
	int push_res = 0;
	void *pop_res = NULL;

	push_res = Vector_push(vector, &vals[0]);
	mu_assert(push_res == 0, "Vector push was not successful.");
	mu_assert(*(int *)Vector_get(vector, 0) == 1,
			"Vector did not push value");

	push_res = Vector_push(vector, &vals[1]);
	mu_assert(push_res == 0, "Vector push was not successful.");
	mu_assert(*(int *)Vector_get(vector, 1) == 2,
			"Vector did not push value");

	push_res = Vector_push(vector, &vals[2]);
	mu_assert(push_res == 0, "Vector push was not successful.");
	mu_assert(vector->max = 2 + vector->expand_rate,
			"Vector did not expand after push beyond max.");
	mu_assert(*(int *)Vector_get(vector, 2) == 3,
			"Vector did not push value");

	pop_res = Vector_pop(vector);
	mu_assert(pop_res != NULL, "Vector pop was not succesful");
	mu_assert(*(int *)pop_res == 3,
			"Vector pop did not return the correct value.");

	pop_res = Vector_pop(vector);
	mu_assert(pop_res != NULL, "Vector pop was not succesful");
	mu_assert(*(int *)pop_res == 2,
			"Vector pop did not return the correct value.");

	pop_res = Vector_pop(vector);
	mu_assert(pop_res != NULL, "Vector pop was not succesful");
	mu_assert(*(int *)pop_res == 1,
			"Vector pop did not return the correct value.");

	Vector_destroy(vector);

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_vector_create);
	mu_run_test(test_vector_destroy);
	mu_run_test(test_vector_clear);
	mu_run_test(test_vector_new);
	mu_run_test(test_vector_get_set);
	mu_run_test(test_vector_expand);
	mu_run_test(test_vector_contract);
	mu_run_test(test_vector_push_pop);

	return NULL;
}

RUN_TESTS(all_tests);
