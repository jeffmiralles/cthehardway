#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100

int read_string(char **out_string, int max_buffer) //a pointer to a pointer to a string, 2 level pointer
{
    *out_string = calloc(1, max_buffer + 1); //allocates and initialised 1 block of memory with the specified size max_buffer + 1 to the value of the pointer **out_string which is *out_string,now it is not NULL anymore its now an empty char '\0'
    
    check_mem(*out_string);
    
    char *result = fgets(*out_string, max_buffer, stdin); //since out_string in the parameter is a pointer to a pointer object (2 levels) *out_pointer in this code will mean get the value of a **out_string, the value of a **out_string is a pointer to string *out_string, after getting the characters in buffer/ keyboard input store it to *out_string, the result will be just for checking purposes
    
    check(result != NULL, "Input error.");
    
    return 0; //return a 0 integer if this function is a success
    
error: //if the check macro sees an error it will perform a goto error, next line error: (errno=0)
    if(*out_string) free(*out_string);
    *out_string = NULL; //make the value of *out_string = null
    return -1;
}

int read_int(int *out_int) //pass a pointer to int variable to this parameter out_int
{
    char *input = NULL; //0x0, just the value is 0x0, input variable is still an address in memory
    int rc = read_string(&input, MAX_DATA); //returns 0 or -1, 0 for success, pass (&input) the address of input not the value on input which is NULL this means im passing **input
    check(rc == 0, "Failed to read number.");
    
    *out_int = atoi(input); //converts char * to int, and put the int to the value of out_int,parameter out_int is a pointer to get its value which is the address that will hold the real value.. *out_int
    
    free(input); //why must it be freed?
    return 0;
    
error:
    if(input) free(input); //
    return -1;
}

int read_scan(const char *fmt, ...) //will contain a pointer to char, and 1 or more arguments in ...
{
    int i = 0; //some initialized data
    int rc = 0;
    int *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;
    int max_buffer = 0;
    
    va_list argp; //object type, this will hold the information needed to retrieve the arguments in va_arg function
    va_start(argp, fmt); //fmt the last argument before the ellipsis
    
    for(i = 0; fmt[i] != '\0'; i++) {
        if(fmt[i] == '%') {
            i++;
            switch(fmt[i]) {
                case '\0':
                    sentinel("Invalid format, you ended with %%.");
                    break;
                    
                case 'd':
                    out_int = va_arg(argp, int *);
                    rc = read_int(out_int);
                    check(rc == 0, "Failed to read int.");
                    break;
                    
                case 'c':
                    out_char = va_arg(argp, char *);
                    //int what = fgetc(stdin);
                    *out_char = fgetc(stdin);
                    break;
                    
                case 's':
                    max_buffer = va_arg(argp, int); //this will get the next argument i.e. MAX_DATA 100 and put it in the max_buffer address
                    out_string = va_arg(argp, char **); //needs a 2 level pointer, i.e **first_name and store it to **out_string, a call to va_arg again will move it to the next argument, note it must match the type in the argument
                    rc = read_string(out_string, max_buffer);
                    check(rc == 0, "Failed to read string.");
                    break;
                    
                default:
                    sentinel("Invalid format.");
            }
        } else {
            fgetc(stdin);
        }
        
        check(!feof(stdin) && !ferror(stdin), "Input error.");
    }
    
    va_end(argp); //allows a function with variable arguments which used the va_start macro to return
    return 0;
    
error:
    va_end(argp);
    return -1;
}



int main(int argc, char *argv[])
{
    char *first_name = NULL; //NUll the value of this address first_name
    char initial = ' '; //the value of this address is a space 0x20 in ascii
    char *last_name = NULL;
    int age = 0;
    
    printf("What's your first name? ");
    int rc = read_scan("%s", MAX_DATA, &first_name); //MAX_DATA 100 and passing a pointer to the pointer of firstname this becomes **first_name
    check(rc == 0, "Failed first name.");
    
    printf("What's your initial? ");
    rc = read_scan("%cp", &initial);
    check(rc == 0, "Failed initial.");
    
    printf("What's your last name? ");
    rc = read_scan("%s", MAX_DATA, &last_name);
    check(rc == 0, "Failed last name.");
    
    printf("How old are you? ");
    rc = read_scan("%d", &age);
    
    printf("---- RESULTS ----\n");
    printf("First Name: %s", first_name);
    printf("Initial: '%c'\n", initial);
    printf("Last Name: %s", last_name);
    printf("Age: %d\n", age);
    
    free(first_name);
    free(last_name);
    return 0;
error:
    return -1;
}