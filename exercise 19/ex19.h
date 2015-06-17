#ifndef _ex19_h //if _ex19_h is not defines then do the following code
#define _ex19_h //this will define _ex19_h to make sure that this block of code execute only once

#include "object.h"

struct Monster { //struct 2 fields, 1 is an object..
    Object proto;
    int hit_points;
};

typedef struct Monster Monster; //signature

int Monster_attack(void *self,int damage); //forward declaration
int Monster_init (void *self);

struct Room {
    Object proto;
    
    Monster *bad_guy;
    
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
};

typedef struct Room Room;

void *Room_move(void *self,Direction direction); //can use Direction data type cause of object.h
int Room_attack(void *self,int damage);
int Room_init (void *self);

struct Map {
    Object proto;
    Room *start;
    Room *location;
};

typedef struct Map Map;

void *Map_move (void *self,Direction direction);
int Map_attack(void *self,int damage);
int Map_init(void *self);

#endif