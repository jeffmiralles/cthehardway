#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int THE_SIZE = 1000;

static int THE_AGE = 37; //kinda like the inverse of extern, this variable is only available in this file

int get_age() { //accessor, by default they are declared as extern so it can be used through all the files (like getter method in Obj-c)
    return THE_AGE; //return age, i.e 37
}

void set_age(int age) { //like setter in Obj-c
    THE_AGE = age; //whoever calls this function can set the age even though THE_AGE is static in this file
}

double update_ratio(double new_ratio) { //this function will be called in ex22_main.c
    static double ratio = 1.0; //function level static variable
    double old_ratio = ratio; //reassigning like a copy
    ratio = new_ratio; //the new_ratio will be coming from ex22_main.c and this is static variable, can it be assigned?. anser: yes because new_ratio parameter is of different pointer from the one that passed a data to this function which is in ex22_main.c, WHat if the parameter that is passed is of the same pointer in ex22_main.c? anser it is ok.
    
    return old_ratio; //returned the copied ratio
}

void print_size() {
    log_info ("I think size is: %d",THE_SIZE);
    
    
     //fprintf(stderr,"[INFO] (%s:%d) I think size is: %d \n",__FILE__,__LINE__,THE_SIZE);

}