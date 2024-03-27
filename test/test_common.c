#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "cunit.h"
#include <heapsort.h>

#define unused __attribute__((unused))

typedef enum e_strategy {
	ASC,
	DSC,
	RANDOM,
	RANDOM_WITH_MANY_REPS,
	ALMOST_SORTED_ASC,
	ALMOST_SORTED_DSC
} t_strategy;

typedef int *(*_sort)(int*, size_t, unsigned char (*)(int, int));

const _sort fn = my_heapsort;

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

static void _printErr(int *a1, size_t size)
{
		write(STDOUT_FILENO, "\n", 1); 
		write(STDOUT_FILENO, "actual: ", 8); 
		_printArr(a1, size);
}

static unsigned char _asc(int a, int b)
{
	return a < b;
}

static unsigned char _dsc(int a, int b)
{
	return a > b;
}

void	create_simple_array(int *dst, size_t size, t_strategy strategy)
{
	size_t i;


	if (strategy == ASC)
	{
		i = 0;
		while (i < size)
		{
			dst[i] = i;
			++i;
		}
	} else {
		while (size--)
			dst[size] = size;
	}
}

unused void	create_random_array(unused int *dst, unused size_t size, unused t_strategy strategy)
{

}

unused void	create_almost_sorted_array(unused int *dst, unused size_t size, unused t_strategy strategy)
{

}

void	create_array(int *pointer, size_t size, t_strategy strategy)
{
	if (strategy == ASC)
		create_simple_array(pointer, size, strategy);
	else if (strategy == DSC)
		create_simple_array(pointer, size, strategy);
	else if (strategy == RANDOM)
		create_random_array(pointer, size, strategy);
	else if (strategy == RANDOM_WITH_MANY_REPS)
		create_random_array(pointer, size, strategy);
	else if (strategy == ALMOST_SORTED_ASC)
		create_almost_sorted_array(pointer, size, ASC);
	else if (strategy == ALMOST_SORTED_DSC)
		create_almost_sorted_array(pointer, size, DSC);
}

static bool_t	is_sorted(int *arr, size_t size, t_strategy order)
{
	unsigned char (*fn)(int,int) = order == ASC ? _asc : _dsc;

	while (--size)
	{
		if (!fn(*arr, *(arr + 1)) && *arr != *(arr + 1))
			return false;
		++arr;
	}
	return true;
}

Test(Common_test, sort_small_array)
{
	const size_t size = 5;
	int arr[size];
	int *actual;

	create_array(&arr[0], size, DSC);
	actual = fn(arr, size, _asc);
	if (!actual)
		 return fail;
	if (!is_sorted(actual, size, ASC))
	{
		_printErr(actual, size);
		bzero(actual, size);
		free(actual);
		return fail;
	}
	bzero(actual, size);
	free(actual);
	return pass;
}
Test(Common_test, sort_small_array_with_repetitions)
{
	const size_t size = 5;
	int arr[size];
	int *actual;
	
	arr[0] = 1;
	arr[1] = 3;
	arr[2] = 5;
	arr[3] = 1;
	arr[4] = 0;
	actual = fn(arr, size, _asc);
	if (actual == 0)
		 return fail;
	if (!is_sorted(actual, size, ASC))
	{
		_printErr(actual, size);
		bzero(actual, size);
		free(actual);
		return fail;
	}
	bzero(actual, size);
	free(actual);
	return pass;

}

Test(Common_test, sort_array_with_one_element)
{
	const size_t size = 1;
	int arr[size];
	int *actual;
	

	arr[0] = 1;
	actual = fn(arr, size, _asc);
	if (actual == 0)
		 return fail;
	if (!is_sorted(actual, size, ASC))
	{
		_printErr(actual, size);
		bzero(actual, size);
		free(actual);
		return fail;
	}
	bzero(actual, size);
	free(actual);
	return pass;

}

Test(Common_test, sort_small_array_with_even_length)
{
	const size_t size = 4;
	int arr[size];
	int *actual;
	
	create_array(&arr[0], size, DSC);
	actual = fn(arr, size, _asc);
	if (actual == 0)
		 return fail;
	if (!is_sorted(actual, size, ASC))
	{
		_printErr(actual, size);
		bzero(actual, size);
		free(actual);
		return fail;
	}
	bzero(actual, size);
	free(actual);
	return pass;

}

Test(Common_array, sort_array_30)
{
	const size_t size = 30;
	int arr[size];
	int *actual;

	create_array(&arr[0], size, DSC);
	actual = fn(arr, size, _asc);
	if (actual == 0)
		 return fail;
	if (!is_sorted(actual, size, ASC))
	{
		_printErr(actual, size);
		bzero(actual, size);
		free(actual);
		return fail;
	}
	bzero(actual, size);
	free(actual);
	 return pass;

}

Test(Common_array, sort_array_30_dsc)
{
	const size_t size = 30;
	int arr[size];
	int *actual;

	create_array(&arr[0], size, ASC);
	actual = fn(arr, size, _dsc);
	if (actual == 0)
		 return fail;
	if (!is_sorted(actual, size, DSC))
	{
		_printErr(actual, size);
		bzero(actual, size);
		free(actual);
		return fail;
	}
	bzero(actual, size);
	free(actual);
	 return pass;

}

Test(Common_test, sort_array_200)
{
	const size_t size = 200;
	int arr[size];
	int *actual;

	create_array(&arr[0], size, DSC);
	actual = fn(arr, size, _asc);
	if (actual == 0)
		 return fail;
	if (!is_sorted(actual, size, ASC))
	{
		_printErr(actual, size);
		bzero(actual, size);
		free(actual);
		return fail;
	}
	bzero(actual, size);
	free(actual);
	return pass;

}

Test(Common_array, sort_array_200_dsc)
{
	const size_t size = 200;
	int arr[size];
	int *actual;

	create_array(&arr[0], size, ASC);
	actual = fn(arr, size, _dsc);
	if (actual == 0)
		 return fail;
	if (!is_sorted(actual, size, DSC))
	{
		_printErr(actual, size);
		bzero(actual, size);
		free(actual);
		return fail;
	}
	bzero(actual, size);
	free(actual);
	 return pass;

}

