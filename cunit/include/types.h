#ifndef CUNIT_TYPES_H
# define CUNIT_TYPES_H

# ifndef NULL
#  define NULL ((void*)0)
# endif /* NULL */
# ifndef _BOOL_T
#  define _BOOL_T
#  ifndef FALSE
#   define FALSE NULL
#  endif /* FALSE */
#  ifndef TRUE
#   define TRUE !FALSE
#  endif /* TRUE */
#  ifndef _SIZE_T
#   define _SIZE_T
typedef unsigned long int size_t;
#  endif /* _SIZE_T */

typedef enum	bool_e {
		true = TRUE,
		false = (int)(long)FALSE
}		bool_t;
# endif /* _BOOL_T */

typedef enum	test_res_e {
		pass = true,
		fail = false
}		test_res_t;

typedef		test_res_t(*user_test_fn)(void);

typedef struct			user_test_st {
	user_test_fn		test;
	struct user_test_st	*next;
}				user_test_t;

typedef struct	tests_result_st {
	size_t	passed;
	size_t	failed;
	size_t	total;
	size_t	skiped;
	size_t	total_run;
}		tests_result_t;

#endif /* CUNIT_TYPES_H */
