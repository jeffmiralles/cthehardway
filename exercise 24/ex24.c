#include <stdio.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor { //enumeration
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor; //this is typedef to be able to use this as a data type

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person { //5 fields
    int age;
    char first_name[MAX_DATA]; //MAX_DATA (100), 100 bytes allocated
    char last_name[MAX_DATA];
    EyeColor eyes; //EyeColor is typedef
    float income;
} Person;


int main(int argc, char *argv[])
{
    Person you= {.age = 0,.first_name="artss"}; //this will allocate and initialize you Struct on the stack memory, better off allocating this kind of object in the heap, {.age = 0}? i think this is just for this Struct to be allocated it must initialised one of its field, though {}; seems to work, or it can be of used for default value
    int i = 0;
    char *in = NULL; //value is of nothing, a null byte
    
    printf("What's your First Name? ");
    in = fgets(you.first_name, MAX_DATA-1, stdin); //fgets is a function define in stdio.h, it will put whatever is in stdin to the you.first_name, stdin is a File source and stdin simply means the standard input of your computer i.e keyboard. MAX_DATA-1 cause need to reserve a byte of memory to '\0' string end, that means i.e i can only put 99 character + 1 for '\0', ok... i tried MAX_DATA = 4, 4-1 = 3 then i input letter 'p' and press enter it seems that the enter is also a character \n and is included that means "p\n\0" is in the buffer (total of 3 bytes) since it does'nt exceed the 3 bytes in the 2nd parameter the buffer is now empty, But if input on my keyboard "pp" this means the buffer is of 4 bytes "pp\n\0" it exceeds the 3 byte input so that means the "pp\0" is going to return (remember that the you must reserve a byte for end string '\0' if there is no space for this it will take the last byte) so what happens in the buffer is that it contain '\n' character, the next time fgets() function is called it will not ask you to input anymore in the buffer cause it is not cleared yet, lets say we have run a fgets, 3 bytes max "\n\0" will be returned and there now the buffer is cleared
    
    check(in != NULL, "Failed to read first name.");
    
    printf("What's your Last Name? ");
    in = fgets(you.last_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read last name.");
    
    printf("How old are you? ");
    int rc = fscanf(stdin, "%d",&you.age); //this is like fgets but you are getting a number which then will convert to integer and stored it into a location in the 3rd argument, you.age is a value dereferencing it by using &you.age will point it to a location of this value, its just that the parameter is of type int * so you must passed also a pointer by dereferencing a value (&you.age) will result in a pointer
    
    check(rc > 0, "You have to enter a number."); //if there is error, goto error and end program, this must check that the entered input is a number
    
    printf("What color are your eyes:\n");
    for(i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");
    
    int eyes = -1; //-1 is for making the inputed choice to match the enumeration OTHER_EYES
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "You have to enter a number.");
    
    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");
    
    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income); //this time with a float format specifier
    check(rc > 0, "Enter a floating point number.");
    
    printf("----- RESULTS -----\n");
    
    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);
    
    return 0;
error:
    
    return -1;
}