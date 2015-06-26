//
//  ringbuffer_tests.c
//  exercise 44
//
//  Created by Laney Miralles on 6/26/15.
//  Copyright (c) 2015 DMS Solutions. All rights reserved.
//

#include <stdio.h>
#include "minunit.h"
#include <lcthw/ringbuffer.h>

RingBuffer *ring = NULL;
char *data = "jef";
char *test_create() {
    
    ring = RingBuffer_create(5);
    
//    typedef struct {
//        char *buffer;
//        int length;
//        int start;
//        int end;
//    } RingBuffer;
    
//    RingBuffer *RingBuffer_create(5)
//    {
//        RingBuffer *buffer = calloc(1, sizeof(RingBuffer)); //allocates a memory of size 24 bytes
//        buffer->length  = length + 1; //length is int (needs 4 bytes), value = 6 remaining is 20
//        buffer->start = 0; //remaining 16
//        buffer->end = 0; //remaining 8 * cause end is the last in the struct it must cover the max of 8 bytes due to char *
//        buffer->buffer = calloc(buffer->length, 1); //assign an address to the buffer with a block of 6, 1 byte each for each block
//        
//        return buffer; 
//    }
    /*
     summary:
     buffer {
        *buffer = '\0';
        length = 6;
        start = 0;
        end = 0;
     }
     
     */


    
    return NULL;
}

char *test_read_write () {
    int rc = 0;
    rc = RingBuffer_write(ring, "jef", 3);
//    int RingBuffer_write(ring, "jef", 3)
//    {
//        if(RingBuffer_available_data(buffer) == 0) {  // (((ring)->end + 1) % (ring)->length - (ring)->start - 1) = 0
//            buffer->start = buffer->end = 0;
//        }
//        
//        check(length <= RingBuffer_available_space(buffer),
//              "Not enough space: %d request, %d available",
//              RingBuffer_available_data(buffer), length);
//        
//        void *result = memcpy(RingBuffer_ends_at(buffer), data, length); //copies the bytes with a length of length from the parameter from src which is data (char *) to the dst ((ring)->buffer + (ring)->end)
//        check(result != NULL, "Failed to write data into buffer.");
//        
//        RingBuffer_commit_write(buffer, length); //((ring)->end = ((ring)->end + (3)) % (ring)->length)   = 3 this will update the end count
//        
//        return length;
//    error:
//        return -1;
//    }
    
    return NULL;
}

char *all_tests()
{
    mu_suite_start();
    
    mu_run_test(test_create);
    
    mu_run_test(test_read_write);
    
    return NULL;
}



RUN_TESTS(all_tests);