#undef NDEBUG //undefine NDEBUG
#include "dbg.h" //the NDEBUG is not define so #define debug(M, ...) fprintf(stderr,"DEBUG %s:%d: " M "\n",__FILE__,__LINE__,##__VA_ARGS__) can be used
#include <stdio.h>
#include <assert.h>

/*
 * Naive copy that assumes all inputs are always valid
 * taken from K&R C and cleaned up a bit.
 */
void copy(char to[], char from[]) //this is not called, this code does not have a defense against misleading input
{
    int i = 0;
    
    // while loop will not end if from isn't '\0' terminated
    while((to[i] = from[i]) != '\0') { //if the to[] or from[] is NULL this will cause a crash
        ++i; //or this will not have a string terminator at the end of to[];
    }
}

/*
 * A safer version that checks for many common errors using the
 * length of each string to control the loops and termination.
 */
int safercopy(int from_len, char *from, int to_len, char *to)
{
    assert(from != NULL && to != NULL && "from and to can't be NULL"); //assert will abort the program if the condition from the argument result in false, a char * (from and to can't be NULL) is always true unless it is NULL
    
    int i = 0;
    int max = from_len > to_len - 1 ? to_len - 1 : from_len; //ternary, i.e 11 > (8-1) results in true so max = 7
    
    // to_len must have at least 1 byte
    if(from_len < 0 || to_len <= 0) return -1; //defensive programming, it checks in the assert and it is also checked in this line, -1 means error
    
    for(i = 0; i < max; i++) { //i.e this will loop 7 times
        to[i] = from[i]; //just copies the value of the from[index] to to[index]
    }
    
    to[to_len - 1] = '\0'; //then the last index must be string terminated i.e to[7] = '\0'
    
    return i; //then returns the value of i, i.e 7
}


int main(int argc, char *argv[])
{
    char from[] = "0123456789";
    int from_len = sizeof(from); //i.e 11
    
    char to[] = "0123456";
    int to_len = sizeof(to); //i.e 8
    
    debug("Copying '%s':%d to '%s':%d", from, from_len, to, to_len);
    
    int rc = safercopy(from_len, from, to_len, to); //call this function
    //copy(to, from);
    check(rc > 0, "Failed to safercopy.");
    check(to[to_len - 1] == '\0', "String not terminated.");
    
    debug("Result is: '%s':%d", to, to_len); //prints putput to the console
    
    //breaking
    rc = safercopy(from_len * -1, from, to_len, to); //this will return -1
    
    check(rc == -1, "safercopy should fail #1"); //if not true jump to error:, but this is true so do nothing
    
    check(to[to_len - 1] == '\0', "String not terminated."); //another check,
    
    rc = safercopy(from_len, from, 0, to);  //test no.2
    check(rc == -1, "safercopy should fail #2");
    check(to[to_len - 1] == '\0', "String not terminated.");
    
    return 0;
    
error:
    return 1;
}

