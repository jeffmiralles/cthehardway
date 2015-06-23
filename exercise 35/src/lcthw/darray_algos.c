#include <lcthw/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp)
{
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp); //qsort is a function that will exchange value from the base of pointer contents (meaning *contents) to (array)->end i.e 5,cmp will be the mediate if the exchange will happen or not (go to testcmp function)
    return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
    return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
    return mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
}