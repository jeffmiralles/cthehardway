#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int main (void) {
    
    //===Available Data Types===
    
    int intValue = 2147483647; //regular integer, defaults in 32 bits in size
    
    double doubleValue = 1.7976931348623158e+308; //holds large floating point number, 64 bits in size
    
    float floatValue = 3.402823e+38; //holds small floating point number, 32 bits in size
    
    char character = '1'; //holds a single 1 byte character, 8 bits in size, it can be any character
    
    void *this; //The type specifier void indicates that no value, or pointer has no type,A pointer of type void * represents the address of an object, but not its type. For example a memory allocation function void *malloc( size_t size ); returns a pointer to void which can be casted to any data type.
    
    enum enumeration { //Enumerated types, work as integers, convert to integers, but give you symbolic names for sets.
        first = 1, //by deafult the 'first' value is 0 if its 1 (first=1) then 'second' is 2, third is 3
        second, // 1
        third //2
    };
    
    
    
    
    //=== Type Modifiers===
    
    unsigned int uintValue = -1; //Changes the type so that it does not have negative numbers, giving you a larger upper bound but nothing lower than 0. if i print this using %u format specifier this will result in 4294967295, 0xFFFFFFFF, so it must be a positive number to be not misinterpreted in your program
    
    signed int sintValue = 1; //Gives you negative and positive numbers, but halves your upper bound in exchange for the same lower bound negative, -2147483648 to 2147483647
    
    long int longIntValue = 1; //ses a larger storage for the type so that it can hold bigger numbers, usually doubling the current size
    
    short shortValue = 1; //Uses smaller storage for the type so it stores less, but takes half the space. –32,768 to 32,767
    
    
    
    
    //===Type Qualifiers
    
    char const kChar = 'A'; //since this is initialised it cannot be changed
    //kChar = 'F'; if this i uncomment this it will result a compilation error : assignment of read-only variable, can get this kChar value but cannot be written
    
    
    
    //===Type Conversion===
    /* Order
     long double
     double
     float
     int (but only char and short int);
     long
     */
    int jeffInt = 1;
    double jeffDouble = 2;
    double jeffTotal = jeffInt + jeffDouble; //result is in double based on the order, int + double, double comes before int
    
    
    
    //===Type Sizes===
    int8_t x1 = INT8_MAX; // 127
    uint8_t x2 = UINT8_MAX; //255
    int16_t x3 = INT16_MAX; //32767
    uint16_t x4 = UINT16_MAX; //65535
    int32_t x5 = INT32_MAX; //2147483647
    uint32_t x6 = UINT32_MAX; //4294967295
    int64_t x7 = INT64_MAX; //9223372036854775807
    uint64_t x8 = UINT64_MAX; //18446744073709551615
    
    int hold = INT_LEAST8_MAX; //127
    int hold2 = INT_LEAST8_MIN; //127
    
    //===Data Operators===
    struct Person {
        char *name;
        int age;
    };
    
    struct Person *jeff = malloc(sizeof(struct Person));
    jeff->name = "jeff";
    jeff->age = 99;
    
    int object_init(void *self) {
        return 1;
    }
    
    typedef struct {
        int (*init)(void *self);
    } Object;
    
    Object proto;
    
    proto.init = object_init;
    
    char *people[] = {
        "me","jeff","long","joe","manny"
    };
    
    char *name = people[4];
    
    int i = 12; //valur of i
    int *pointer = &i; //pointer of i -> pointer
    int value = *pointer; //value of pointer
    
    
    
    //===Logic Operators===

    if (1 != 2) {
        //1 is really not equal to 2 so run this code
    }
    else if ('a' == 'b') {
        //is character a equal to character b
    }
    else if (5 <= 3) {
        
    }
    else {
        //end
    }
    
    
    
    //===Bit Operators===
    
    int bitI = 2;
    int bitJ = 3;
    int bitAnd = bitI & bitJ; //0010 & 0011 starting from left 0 AND 1 = 0, 1 AND 1 = 1.... therefore 0010 ,2
    int shiftLeft = 8 << 1; //0x00001000  << 1, 0x00010000... 16
    int shiftRight = 8 >> 2;//0x00001000 >> 2, 0x00000010... 2
    int bitXor = bitI ^ bitJ; //0010 ^ 0011 starting from left 1 ^ 0 = 1, 1 ^ 1 = 0.... 0001  1
    int compliment = ~0; //~0x00000000  =>  0xffffffff   -1 in signed int
    
    
    
    
    //===Boolean Operators===
    
    if (!true || true && true) {
        //!true is false || true becomes true then && true, both are true so execute this
    }
    
    bool what = (bitJ > bitI) ? true : false; //3 < 2 no so.. return false
    
    
    
    
    //Available Control Structures
    
    do {
        //this will execute at least 1 time
        break; //this will exit a loop
    } while (1); //this is infinite since we have a break from the do it is fine
    
    int counter = 0;
    
    for (counter = 0; counter < 10; counter++) {
        //code in here will be executed
        continue;
        //code in here will be skipped and the loop jumps
    }
    
    
    goto inhere;
    
    //more codes
    //some more codes will not execute because of goto inhere
    
inhere:
    //this is where the goto will jump
    
    
    
    return 0;
}

