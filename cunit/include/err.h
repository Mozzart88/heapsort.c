#ifndef CUNIT_ERR_H
# define CUNIT_ERR_H

# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"

# define cu_panic(Error) cu_panic_(Error, __FILE__, __LINE__)

void	cu_panic_(char *error_str, char *file, int line);

#endif /* CUNIT_ERR_H */
