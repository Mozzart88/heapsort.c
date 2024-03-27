#include "common.h"

void		print_delimiter(char c, size_t repetitions)
{
	char	str[repetitions + 1];
	size_t	i;

	i = 0;
	while (i < repetitions)
	{
		str[i] = c;
		++i;
	}
	str[i] = 0;
	printf("%s\n", str);
}

