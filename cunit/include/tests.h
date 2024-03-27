#ifndef CUNIT_TESTS_H
# define CUNIT_TESTS_H

# include "stdlib.h"
# include "stdio.h"
# include "types.h"
# include "err.h"
# include "common.h"

# define CU_TEST_TRAMP(Category, Name)							\
	static void CU_ATTR(constructor) CU_IDENTIFIER(Category, Name, Jmp)(void)	\
	{										\
		add_test((user_test_fn)CU_IDENTIFIER(Category, Name, Impl));		\
	} 

# define CU_TEST_PROTO(Category, Name)		\
	static test_res_t CU_IDENTIFIER(Category, Name, Impl)(void)

# define CU_TEST_BASE(Category, Name, ...)					\
	CU_TEST_PROTO(Category, Name);						\
	CU_TEST_TRAMP(Category, Name)						\
	CU_TEST_PROTO(Category, Name)						
	
# define Test(...) CU_EXPAND(CU_TEST_BASE(__VA_ARGS__, 0))

tests_result_t	*run_tests(user_test_t *tests);
user_test_t	*get_tests(void);
void		add_test(user_test_fn);
void		free_tests(user_test_t *tests);
void		print_total(tests_result_t *data);

#endif /* CUNIT_TESTS_H */

