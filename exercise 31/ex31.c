#include <unistd.h>

int main(int argc, const char *argv[]) {
    int i = 0;
    while (i < 100) { //this will loop forever
        usleep(3000); // 3 microseconds, this will block the current thread, making the program not responsive
    }
    return 0;
}

//get the process ID (after it run) ps ax | grep ex31. i.e 1560
//attached gdb debugger to the process sudo gdb ./ex31 1560
//put break points at line 5 and at line 6, break 5, break 6
//use continue to run the process till it reach the second breakpoint, .i.e 6
//set i = 200, use set to change the value of the variable (this is for gdb)
//print i, to know if its changed or not
//if this i is changed, enter the command next to go to the whole loop function, the condition will fail since 200 < 100 is false and will hit return 0 exiting the program
//quit, quit gdb debugger