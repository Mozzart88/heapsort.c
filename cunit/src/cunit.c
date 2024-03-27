#include "cunit.h"

int	main(void)
{
	user_test_t	*tests;
	tests_result_t	*res;
	int		ret;

	tests = get_tests();
	if (!tests)
		cu_panic("No tests to run");
	res = run_tests(tests);
	free_tests(tests);
	print_total(res);
	ret = res->failed ? 1 : 0;
	free(res);
	res = NULL;
	return ret;
}

