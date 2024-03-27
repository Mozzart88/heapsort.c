#ifndef CUNIT_COMMON_H
# define CUNIT_COMMON_H

# include "stdio.h"

# include "types.h"

# define CU_ATTR(attr) __attribute__((attr))
# define CU_EXPAND(x) x

# define CU_IDENTIFIER(Category, Name, Suffix)	\
	Category ## _ ## Name ## _ ## Suffix


void		print_delimiter(char c, size_t repetitions);

#endif /* CUNIT_COMMON_H */
