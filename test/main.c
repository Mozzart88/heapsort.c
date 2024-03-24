#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include <heapsort.h>

#define KO (_print("💀 "), 1)
#define OK (_print("🔥 "), 0)

static int	_print(char *s)
{
	return write(STDOUT_FILENO, s, strlen(s));
}

static void _printArr(int *a, size_t s)
{
	size_t	i;

	i = 0;
	write(STDOUT_FILENO, "{", 1);
	while (i < s)
	{
		printf("%d ", a[i]);
		++i;
	}
	write(STDOUT_FILENO, "}\n", 2);
}

static void _printErr(int *a1, int *a2, size_t size)
{
		write(STDOUT_FILENO, "\n", 1); 
		write(STDOUT_FILENO, "actual: ", 8); 
		_printArr(a1, size);
		write(STDOUT_FILENO, "expected: ", 10); 
		_printArr(a2, size);
}

static int	_memcmp(const void *s1, const void *s2, size_t l)
{
	char 	*m1;
	char 	*m2;

	if (!s1 || !s2)
		return -1;
	m1 = (char*)s1;
	m2 = (char*)s2;

	while(l && *m1 == *m2)
	{
		++m1;
		++m2;
		--l;
	}
	if (*m1 != *m2)
		return *m1 - *m2;
	return 0;
}

static unsigned char _asc(int a, int b)
{
	return a > b;
}

__attribute__((unused)) static char	test1()
{
	const size_t size = 5;
	int expected[size];
	int arr[size];
	int *actual;
	size_t i;
	
	i = 0;
	while (i < size)
	{
		expected[i] = i;
		arr[i] = size - i - 1;
		++i;
	}

	actual = my_heapsort(arr, size, _asc);
	if (!actual)
		 return KO;
	if (_memcmp(expected, actual, size) != 0)
	{
		_printErr(actual, expected, size);
		bzero(actual, size);
		free(actual);
		return KO;
	}
	bzero(actual, size);
	free(actual);
	return OK;
}
__attribute__((unused)) static char	test2()
{
	const size_t size = 5;
	int expected[size];
	int arr[size];
	int *actual;
	

	expected[0] = 0;
	expected[1] = 1;
	expected[2] = 1;
	expected[3] = 3;
	expected[4] = 5;
	
	arr[0] = 1;
	arr[1] = 3;
	arr[2] = 5;
	arr[3] = 1;
	arr[4] = 0;
	actual = my_heapsort(arr, size, _asc);
	if (actual == 0)
		 return KO;
	if (_memcmp(expected, actual, size) != 0)
	{
		_printErr(actual, expected, size);
		bzero(actual, size);
		free(actual);
		return KO;
	}
	bzero(actual, size);
	free(actual);
	return OK;

}
__attribute__((unused)) static char	test3()
{
	const size_t size = 1;
	int expected[size];
	int arr[size];
	int *actual;
	

	expected[0] = 1;
	arr[0] = 1;
	actual = my_heapsort(arr, size, _asc);
	if (actual == 0)
		 return KO;
	if (_memcmp(expected, actual, size) != 0)
	{
		_printErr(actual, expected, size);
		bzero(actual, size);
		free(actual);
		return KO;
	}
	bzero(actual, size);
	free(actual);
	return OK;

}
__attribute__((unused)) static char	test4()
{
	const size_t size = 4;
	int expected[size];
	int arr[size];
	int *actual;
	size_t i;
	
	i = 0;
	while (i < size)
	{
		expected[i] = i;
		arr[i] = size - i - 1;
		++i;
	}
	actual = my_heapsort(arr, size, _asc);
	if (actual == 0)
		 return KO;
	if (_memcmp(expected, actual, size) != 0)
	{
		_printErr(actual, expected, size);
		bzero(actual, size);
		free(actual);
		return KO;
	}
	bzero(actual, size);
	free(actual);
	return OK;

}
__attribute__((unused)) static char	test5()
{
	const size_t size = 30;
	int expected[size];
	int arr[size];
	int *actual;
	size_t i;
	
	i = 0;
	while (i < size)
	{
		expected[i] = i;
		arr[i] = size - i - 1;
		++i;
	}

	actual = my_heapsort(arr, size, _asc);
	if (actual == 0)
		 return KO;
	if (_memcmp(expected, actual, size) != 0)
	{
		_printErr(actual, expected, size);
		bzero(actual, size);
		free(actual);
		return KO;
	}
	bzero(actual, size);
	free(actual);
	 return OK;

}

__attribute__((unused)) static char	test6()
{
	const size_t size = 200;
	int expected[size];
	int arr[size];
	int *actual;
	size_t i;
	
	i = 0;
	while (i < size)
	{
		expected[i] = i;
		arr[i] = size - i - 1;
		++i;
	}

	actual = my_heapsort(arr, size, _asc);
	if (actual == 0)
		 return KO;
	if (_memcmp(expected, actual, size) != 0)
	{
		_printErr(actual, expected, size);
		bzero(actual, size);
		free(actual);
		return KO;
	}
	bzero(actual, size);
	free(actual);
	return OK;

}


int main(void)
{
	int res;
	
	setbuf(stdout, NULL);
	res = test1() | test2() | test3() | test4() | test5() | test6();
//	res = test5();
	return res;
}
