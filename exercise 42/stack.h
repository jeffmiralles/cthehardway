//
//  stack.h
//  exercises 42
//
//  Created by Laney Miralles on 6/26/15.
//  Copyright (c) 2015 DMS Solutions. All rights reserved.
//

#ifndef exercises_42_stack_h
#define exercises_42_stack_h
#include <stdlib.h>

#define Stack_push(stack,test) if (*stack == 0) {*stack = test; } else {*++stack = test;}
#define Stack_pop(stack)


typedef char * Stack;

static inline void *Stack_create() {
    return calloc(3,sizeof(void *));
}


#endif
