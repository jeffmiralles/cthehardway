#include <stdio.h>
#include <ctype.h>
#include "dbg.h"


int print_a_message(const char *msg)
{
    printf("A STRING: %s\n", msg);
    
    return 0;
}


int uppercase(const char *msg)
{
    int i = 0;
    int max = sizeof(msg);
    max--;
    
    // BUG: \0 termination problems, ....solved
    for(i = 0;i < max; i++) {
        printf("%c", toupper(msg[i]));
    }
    
    printf("\n");
    
    return 0;
}

int lowercase(const char *msg)
{
    int i = 0;
    int max = sizeof(msg);
    max--;
    // BUG: \0 termination problems, ...solved
    for(i = 0; i < max; i++) {
        printf("%c", tolower(msg[i]));
    }
    
    printf("\n");
    
    return 0;
}

int fail_on_purpose(const char *msg)
{
    printf("%s",msg); //just to remove unsued variable warning
    return 1;
}