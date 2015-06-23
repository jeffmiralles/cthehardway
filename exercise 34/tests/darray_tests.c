#include "minunit.h"
#include <lcthw/darray.h>

static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create()
{
    array = DArray_create(sizeof(int), 100);
    /* i.e array is a pointer to struct DArray
     end = 0
     max = 0
     element_size = (size_t) 4
     expand_rate = (size_t) 300
     *contents = NULL
     */
    mu_assert(array != NULL, "DArray_create failed.");
    mu_assert(array->contents != NULL, "contents are wrong in darray");
    mu_assert(array->end == 0, "end isn't at the right spot");
    mu_assert(array->element_size == sizeof(int), "element size is wrong.");
    mu_assert(array->max == 100, "wrong max length on initial size");
    
    return NULL;
}

char *test_destroy()
{
    DArray_destroy(array);
    
    return NULL;
}

char *test_new()
{
    val1 = DArray_new(array); // val1 is a pointer to static int, the DArray_new function just return an allocated void * of size 4 (i.e calloc(1, array->element_size)) element_size is (size_t) 4
    
    mu_assert(val1 != NULL, "failed to make a new element");
    
    val2 = DArray_new(array); //same as val1, but will point to another memory location
    mu_assert(val2 != NULL, "failed to make a new element");
    
    return NULL;
}

char *test_set()
{
    DArray_set(array, 0, val1); //see DArray_set function in darray.h inline function, summary : just set a void * to the contents of array struct (*content)
    DArray_set(array, 1, val2); //add a void * (note the void * is also what the val1 or val2 is pointing )
    
    /*
     after this 2 function executed here is our data 
     end = 1;
     max = 100;
     element_size = 4;
     expand_rate = 300;
     *contents = void * (aka int * : val1)
     *contents++ = void * (aka int * : val2)
     */
    
    return NULL;
}

char *test_get()
{
    mu_assert(DArray_get(array, 0) == val1, "Wrong first value."); //DAarray_get returns the *contents of contents field in array struct , i.e contents[0] is a void * that points in a memory location that val1 int * is pointing to, so the condition is true
    mu_assert(DArray_get(array, 1) == val2, "Wrong second value.");
    
    return NULL;
}

char *test_remove()
{
    int *val_check = DArray_remove(array, 0);
    mu_assert(val_check != NULL, "Should not get NULL.");
    mu_assert(*val_check == *val1, "Should get the first value.");
    mu_assert(DArray_get(array, 0) == NULL, "Should be gone.");
    DArray_free(val_check);
    
    val_check = DArray_remove(array, 1);
    mu_assert(val_check != NULL, "Should not get NULL.");
    mu_assert(*val_check == *val2, "Should get the first value.");
    mu_assert(DArray_get(array, 1) == NULL, "Should be gone.");
    DArray_free(val_check);
    
    return NULL;
}

char *test_expand_contract()
{
    int old_max = array->max;
    DArray_expand(array);
    mu_assert((unsigned int)array->max == old_max + array->expand_rate, "Wrong size after expand.");
    
    DArray_contract(array);
    mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the expand_rate at least.");
    
    DArray_contract(array);
    mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the expand_rate at least.");
    
    return NULL;
}

char *test_push_pop()
{
    int i = 0;
    for(i = 0; i < 1000; i++) {
        int *val = DArray_new(array);
        *val = i * 333;
        DArray_push(array, val);
    }
    
    mu_assert(array->max == 1201, "Wrong max size.");
    
    for(i = 999; i >= 0; i--) {
        int *val = DArray_pop(array);
        mu_assert(val != NULL, "Shouldn't get a NULL.");
        mu_assert(*val == i * 333, "Wrong value.");
        DArray_free(val);
    }
    
    return NULL;
}


char * all_tests() {
    mu_suite_start();
    
    mu_run_test(test_create); //call this first
    mu_run_test(test_new); //second
    mu_run_test(test_set); //third
    mu_run_test(test_get); //fourth
    mu_run_test(test_remove); //and so on
    mu_run_test(test_expand_contract);
    mu_run_test(test_push_pop);
    mu_run_test(test_destroy);
    
    return NULL;
}

RUN_TESTS(all_tests);