#include "minunit.h"
#include <lcthw/darray_algos.h>

int testcmp(char **a, char **b)
{
    return strcmp(*a, *b); //compares string
}

DArray *create_words() //a function that will return a struct Darray
{
    DArray *result = DArray_create(0, 5); //
    char *words[] = {"asdfasfd", "werwar", "13234", "asdfasfd", "oioj"}; //this is like a 2 level pointer this means i.e words[0] = "asdfasfd"
    int i = 0;
    
    for(i = 0; i < 5; i++) { //loops 5 times
        DArray_push(result, words[i]); //pass a DArray struct to first parameter, a pointer to a char at second
    }
    
    return result; //herre
}

int is_sorted(DArray *array)
{
    int i = 0;
    
    for(i = 0; i < DArray_count(array) - 1; i++) {
        if(strcmp(DArray_get(array, i), DArray_get(array, i+1)) > 0) {
            return 0;
        }
    }
    
    return 1;
}

char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name) //accepts a function in first parameter it must match this signature
{
    DArray *words = create_words(); //after this is run, words struct DArray have 5 void * (aka words*[])
    mu_assert(!is_sorted(words), "Words should start not sorted.");
    
    debug("--- Testing %s sorting algorithm", name);
    
    int rc = func(words, (DArray_compare)testcmp); //func is DArray_qsort function, first param is pointer to DArray struct 2nd is must typecase to DArray_compare int (const void *a,const void *b), testcmp is a function.. int (char **a, char **b) this is ok to typecast cause you can assisgn for example a char **a to a void * cos they are just pointers
    
    mu_assert(rc == 0, "sort failed");
    mu_assert(is_sorted(words), "didn't sort it");
    
    DArray_destroy(words);
    
    return NULL;
}

char *test_qsort()
{
    return run_sort_test(DArray_qsort, "qsort"); //i.e call run_sort_test passing a function to the first parameter which returns an int and const char * to the second parameter ("qsort")
}

char *test_heapsort()
{
    return run_sort_test(DArray_heapsort, "heapsort");
}

char *test_mergesort()
{
    return run_sort_test(DArray_mergesort, "mergesort");
}


char * all_tests() //start of program
{
    mu_suite_start(); //char *message = NULL;
    
    mu_run_test(test_qsort); //first
    mu_run_test(test_heapsort);
    mu_run_test(test_mergesort);
    
    return NULL;
}

RUN_TESTS(all_tests);