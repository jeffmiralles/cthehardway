#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "dbg.h"
#define CLOCKS_PER_SEC 1000000

float timeForNormal_copyToComplete = 0.0f; //data storage for how much time this loop will compete

float timeForDuffs_deviceToComplete = 0.0f;

float timeForZeds_deviceToComplete = 0.0f;

int normal_copy(char *from, char *to, int count) //first contender
{
    float timeStartForNormal_copy = (float)clock()/CLOCKS_PER_SEC; //clock() is the clock ticks happened so far in the life time of the prog. CLOCKS_PER_SEC = how many clock ticks are there in 1 second, about 1000000
    int i = 0;
    
    for(i = 0; i < count; i++) { //start the loop now, if count is 1000 then loop this 1000 times
        to[i] = from[i]; //copies value from from[index] to to[index]
    }
    float  timeEndForNormal_copy = (float)clock()/CLOCKS_PER_SEC; //get again the time passed
    timeForNormal_copyToComplete = timeEndForNormal_copy - timeStartForNormal_copy; //calculate the total time for this loop to complete
    return i;
}

int duffs_device(char *from, char *to, int count)
{
    float timeStartForDuffs_device = (float)clock()/CLOCKS_PER_SEC;
    {
        
        int n = (count + 7) / 8; //if for example count is 1000, (1000+7)/8 is 125, it truncates points because left and right are int and will result in int
        
        switch(count % 8) { // 1000 % 8 = 0, no remainder
            case 0: do { *to++ = *from++; //just like copying data, though kinda different in a way..
            case 7: *to++ = *from++;
            case 6: *to++ = *from++;
            case 5: *to++ = *from++;
            case 4: *to++ = *from++;
            case 3: *to++ = *from++;
            case 2: *to++ = *from++;
            case 1: *to++ = *from++;
            } while(--n > 0);
        }
    }
    float timeEndForDuffs_device = (float)clock()/CLOCKS_PER_SEC;
    timeForDuffs_deviceToComplete = timeEndForDuffs_device - timeStartForDuffs_device;
    
    return count;
}

int zeds_device(char *from, char *to, int count) //just a copy of duffs_device, instead of do-while loop he uses goto
{
    float timeStartForZeds_device = (float)clock()/CLOCKS_PER_SEC;
    {
        int n = (count + 7) / 8;
        switch(count % 8) {
            case 0:
            again: *to++ = *from++;
                
            case 7: *to++ = *from++;
            case 6: *to++ = *from++;
            case 5: *to++ = *from++;
            case 4: *to++ = *from++;
            case 3: *to++ = *from++;
            case 2: *to++ = *from++;
            case 1: *to++ = *from++;
                if(--n > 0) goto again;
        }
    }
    float timeEndForZeds_device = (float)clock() / CLOCKS_PER_SEC;
    timeForZeds_deviceToComplete = timeEndForZeds_device - timeStartForZeds_device;
    return count;
}

int valid_copy(char *data, int count, char expects)
{
    int i = 0;
    for(i = 0; i < count; i++) {
        if(data[i] != expects) {
            log_err("[%d] %c != %c", i, data[i], expects);
            return 0;
        }
    }
    
    return 1;
}

void analytics () { //i wrote this function to print to the console how fast those three function executes with the same functionality
    
    printf("The total time for normal_copy to complete is: %f microseconds\n",timeForNormal_copyToComplete*1000000); //in microseconds
    printf("The total time for duffs_device to complete is: %f microseconds\n",timeForDuffs_deviceToComplete*1000000);
    printf("The total time for zeds_device to complete is: %f microseconds\n",timeForZeds_deviceToComplete*1000000);
}


int main(int argc, char *argv[])
{
    char from[230000] = {'a'}; //allocates 230000 bytes with an initial of 'a' at index 0, note: have to make this big to see the difference in speed of those functions
    char to[230000] = {'c'};
    int rc = 0;
    
    // setup the from to have some stuff
    memset(from, 'x', 230000); //this seems fast, it sets all 230000 bytes to a character 'x'
    // set it to a failure mode
    memset(to, 'y', 230000);
    check(valid_copy(to, 230000, 'y'), "Not initialized right.");
    
    // use normal copy to
    rc = normal_copy(from, to, 230000);
    check(rc == 230000, "Normal copy failed: %d", rc);
    check(valid_copy(to, 230000, 'x'), "Normal copy failed.");
    
    // reset
    memset(to, 'y',230000);
    
    // duffs version
    rc = duffs_device(from, to, 230000);
    check(rc == 230000, "Duff's device failed: %d", rc);
    check(valid_copy(to, 230000, 'x'), "Duff's device failed copy.");
    
    // reset
    memset(to, 'y', 230000);
    
    // my version
    rc = zeds_device(from, to, 230000);
    check(rc == 230000, "Zed's device failed: %d", rc);
    check(valid_copy(to, 230000, 'x'), "Zed's device failed copy.");
    
    analytics(); //just prints to the console the speed data of each function
    
    return 0;
error:
    return 1;
}