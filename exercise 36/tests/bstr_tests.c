#include "minunit.h"
#include <lcthw/bstrlib.h>

bstring message;


char *test_bfromcstr () {
    
    message = bfromcstr("hello world");
    
    return 0;
};

char *test_blk2bstr () {
    
    char *string = "game of thrones";
    
    message = blk2bstr(string, 5);
    
    return 0;
};

char *test_bstrcpy () {
    bstring copiedMessage;
    copiedMessage = bstrcpy(message);
    return 0;
};

char *test_bassign () {
    bstring aBstring;
    bstring bBstring;
    
    aBstring = bfromcstr("this will be overwritten");
    bBstring = bfromcstr("OVERIDE!");
    
    bassign(aBstring, bBstring);
    return 0;
};


// and so on.. head to bstrlib.h for more function



char * all_tests() //start of program
{
    mu_suite_start(); //char *message = NULL;
    
    mu_run_test(test_bfromcstr);
    mu_run_test(test_blk2bstr);
    mu_run_test(test_bstrcpy);
    mu_run_test(test_bassign);
    return NULL;
}


RUN_TESTS(all_tests);