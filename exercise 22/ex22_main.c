#include "ex22.h" //only includes the header ex22.h
#include "dbg.h"

const char *MY_NAME = "Zed A. Shaw"; //constant

void scope_demo (int count) {
    log_info("count is: %d",count);
    
    if (count > 10) {
        int count = 100; //bad, bug: different variable from the parameter
        log_info("count in this scope is %d",count); //will it print count from the parameter or 100? answer: 100,int count will be local to this if statement
    }
    
    log_info ("count is at exit: %d",count); //again count on the parameter or 100?. answer: the count in the paramer i.e 4
    count = 3000;
    log_info("count after assign: %d",count); //3000 or count in parameter. answer: 3000 it can change this count that is inside this function, cause the parameter int count is of different pointer from the one who called it scope_demo(count), if you want to change the count outside of this function you must pass it as a pointer in the parameter so pointer count outside of this function is the same as the pointer passed in the parameter
}

int main(int argc,char *argv[]) {
    log_info ("My name: %s, age: %d",MY_NAME,get_age()); //calls the accessor function declared in ex22.c
    
    set_age(100); //setter
    
    log_info("My age is now: %d",get_age()); //call get_age() accessor function again, i.e 100
    
    log_info("THE_SIZE is: %d",THE_SIZE); //1000? it is not declared in here but its extern in ex22.h and it is 1000 in ex22.c, direct access, answer: 1000
    print_size(); //now this function is declared in ex22.c that will print THE_SIZE which is declared in that same file ex22.c, 1000? answer: also 1000
    THE_SIZE = 9;
    
    log_info("THE_SIZE is now: %d",THE_SIZE); //9 or 1000?. answer: 9 ,THE_SIZE is read-write
    print_size(); //print it again, 1000 or 9?. answer: also 9
    
    
    log_info("Ratio at first: %f",update_ratio(2.0)); //call this function declared in ex22.c
    log_info("Ratio again: %f",update_ratio(10.0)); //at this time check if the old_ratio updates
    log_info("Ratio once more: %f",update_ratio(300.0)); //same as above
    
    int count = 4;
    scope_demo(count); //function is in this file
    //scope_demo(&count *20); //80
    
    log_info("count after calling scope_demo: %d",count); //4 or 3000?. answer 4, the count that is passed on the parameter of scope_demo is of different pointer from this count so it wont change if you want it to change pass the count as a pointer scope_demo(&count) then change everthing in the function of scope_demo from count to *count including the parameter since &count means the pointer of the count variable
    
    return 0;
}