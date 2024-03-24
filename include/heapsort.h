#ifndef HEAPSORT_H
#  define HEAPSORT_H
#  ifndef STDLIB_H
#    include "stdlib.h"
#  endif

typedef unsigned char (*heapsort_callback)(int, int) ;

int *my_heapsort(int*, size_t, heapsort_callback);
#endif 
