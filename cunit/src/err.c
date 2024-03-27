#include "err.h"

void	cu_panic_(char *error_str, char *file, int line)
{
	dprintf(STDERR_FILENO, "%s:%d: %s\n", file, line, error_str);
	exit(-1);
}

