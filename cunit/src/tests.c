#include "tests.h"

static user_test_t *new_test(user_test_fn test)
{
	user_test_t	*st;

	st = (user_test_t*)malloc(sizeof(user_test_t));
	if (st == NULL)
		cu_panic("Fail to allocate memmory for user test");
	st->test = test;
	st->next = NULL;
	return st;
}

static void		delete_test(user_test_t *test)
{
	if (test == NULL)
		return;
	test->next = NULL;
	test->test = NULL;
	free(test);
}

static void		test_append(user_test_t **tests, user_test_fn test)
{
	user_test_t	*tmp;

	if (*tests == NULL)
		*tests = new_test(test);
	else
	{
		tmp = *tests;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_test(test);
	}
}

static user_test_t	*tests_keeper(user_test_fn test)
{
	static user_test_t	*tests = NULL;

	if (test != NULL)
		test_append(&tests, test);
	return tests;
}

void	add_test(user_test_fn test)
{
	tests_keeper(test);
}

user_test_t	*get_tests(void)
{
	return tests_keeper(NULL);
}

static tests_result_t	*new_tests_result(tests_result_t **pointer)
{
	*pointer = (tests_result_t*)malloc(sizeof(tests_result_t));
	if (pointer == NULL)
		cu_panic("Faile to allocate memmory for tests rusult structure");
	(*pointer)->passed = 0;
	(*pointer)->failed = 0;
	(*pointer)->total = 0;
	(*pointer)->skiped = 0;
	(*pointer)->total_run = 0;
	return *pointer;
}

static void		test_passed(size_t *pointer)
{
	++(*pointer);
	printf("🔥");
}

static void		test_failed(size_t *pointer)
{
	++(*pointer);
	printf("💀");
}

tests_result_t	*run_tests(user_test_t *tests)
{
	user_test_t	*tmp;
	tests_result_t	*res;

	res = NULL;
	tmp = tests;
	new_tests_result(&res);
	while (tmp)
	{
		++(res->total);
		tmp->test() ? test_passed(&(res->passed)) :  test_failed(&(res->failed));
		++(res->total_run);
		if ((tmp = tmp->next))
			printf(" ");
	}
	printf("\n");
	return res;
}

void		free_tests(user_test_t *tests)
{
	if (tests->next)
		free_tests(tests->next);
	delete_test(tests);
}

void		print_total(tests_result_t *data)
{
	const int	break_line_width = 30;
	print_delimiter('=', break_line_width);
	printf("Passed: %ld\n", data->passed);
	printf("Failed: %ld\n", data->failed);
	printf("Skiped: %ld\n", data->skiped);
	printf("Total: %2ld\n", data->total);
	print_delimiter('=', break_line_width);
}

