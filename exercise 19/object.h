#ifndef _object_h //this will check if _object_h is defined if not all the code till #endif will be executed
#define _object_h //now that it is defined the #ifndef _object_h above will evaluate to false and not running this blocks of code again

typedef enum { //enumeration, these will hold integer values in a consecutive manner
    NORTH, SOUTH, EAST, WEST //NORTH = 0, SOUTH = 1, EAST = 2, WEST = 3
} Direction; //Direction now will be of data type, since it is 'typedef'

typedef struct {
    char *description; //fields for the struct Object
    int (*init)(void *self); //fields can also be a function
    void (*describe)(void *self);
    void (*destroy)(void *self);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;

int Object_init(void *self); //forward declaration of function
void Object_destroy(void *self);
void Object_describe(void *self);
void *Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);
void *Object_new(size_t size, Object proto, char *description);

#define NEW(T, N) Object_new(sizeof(T), T##Proto, N) //a macro
#define _(N) proto.N

#endif