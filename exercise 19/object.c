#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h" //this will include object.h header file
#include <assert.h>

void Object_destroy(void *self) { //funtion that will deallocate Object *, this function is 'forward declared' in the object.h header
    Object *obj = self; //self must match the type Object,and cast it to obj
    if (obj) { //if obj exist in memory do this or it is nut NULL
        if (obj->description) free(obj->description); //also checks the field description from the struct obj
        free(obj); //finally deallocates this Object *
    }
}

void Object_describe(void *self) { //this will print the string contained in the field description
    Object *obj = self;
    printf ("%s.\n",obj->description);
}

int Object_init(void *self) { //function that will return int 1
    return 1;
}

void *Object_move(void *self,Direction direction) { //accepts argument of type Direction which is declared as an enumeration,
    printf("You can't go that direction.\n"); //prints to the console
    return NULL; //return null, points to nothing?
}

int Object_attack(void *self,int damage) { //function that will return 0 and print something, also it accepts a int type argument
    printf("You can't attack that.\n");
    return 0;
}

void *Object_new(size_t size,Object proto,char *description){ //function that accepts 3 arguments
    if (!proto.init) proto.init = Object_init; //this will set the function Object_init to proto.init if it is not set
    if (!proto.describe) proto.describe = Object_describe; //same
    if(!proto.destroy) proto.destroy = Object_destroy;
    if(!proto.attack) proto.attack = Object_attack;
    if(!proto.move) proto.move = Object_move;
    Object *el = calloc(1,size);
    *el = proto;
    el->description = strdup(description); //assign the field description with whatever passed to the argument of this function,strdup copies this string into a memory
    
    if (!el->init(el)) { //this makes sure that el exist or initialised, TEST
        el -> destroy(el); //destroy itself
        return NULL; //return a null pointer
    }
    else {
        return el; //return this Object pointer
    }
}