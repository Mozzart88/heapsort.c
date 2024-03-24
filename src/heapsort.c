#include <heapsort.h>

__attribute__((unused)) static void	_swap(int *p1, int *p2)
{
	int	i;

	i = *p1;
	*p1 = *p2;
	*p2 = i;
}

static void _memcpy(int *src, int *dst, size_t size)
{
	if (!src || !dst)
		return;
	while (size--)
		*(dst + size) = *(src + size);
}

static void	_heapify(int *root, int *next, int *last, heapsort_callback cb)
{
	int	*left;
	int	*right;



	left = next < last ? next : NULL;
	right = next + 1 < last ? next + 1 : NULL;
	next += ((next - root) * 2L);
	if (left && next <= last)
		_heapify(left, next, last, cb);
	if (right && next + 1 <= last)
		_heapify(right, next + 2, last, cb);
	if (left && cb(*left, *root))
		_swap(left, root);
	if (right && cb(*right, *root))
		_swap(right, root);




}

void		_sort(int *arr, size_t size, heapsort_callback cb)
{
	int	*last;

	last = arr + size - 1;
	if (cb(*arr, *last))
	{
		_swap(arr, last);
		_heapify(arr, arr + 1, last - 1, cb);
	}
	if (last > arr)
		_sort(arr, size - 1, cb);
}

int 		*my_heapsort(int *arr, size_t size, heapsort_callback cb)
{
	int	*res;
	int	*last;

	if ((res = (int*)malloc((sizeof (int)) * size)) == NULL)
		return NULL;
	_memcpy(arr, res, size);
	last = res + size - 1;
	_heapify(res, res + 1, last, cb);	
	_sort(res, size, cb);

	return res;
}
