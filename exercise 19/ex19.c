#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex19.h" //include this header of ex19.h

int Monster_attack (void *self,int damage) { //this is forward declared in ex19.h
    Monster *monster = self; //self must match the signature of Monster
    printf("You attack %s!\n",monster->_(description)); //_() is a Macro define in object.h in this case this will become monster->proto.description
    monster->hit_points -= damage; //substract the value of the field hit_points to whatever value is passed to the argument damage
    if (monster->hit_points > 0) {
        printf("It is still alive.\n");
        return 0;
    }
    else {
        printf("It is dead!\n");
        return 1;
    }
}

int Monster_init(void *self) {
    Monster *monster = self; //this self must match the Monster signature
    monster->hit_points = 10; //initially set the monster hit points to 10
    return 1;
}

Object MonsterProto = {
    .init = Monster_init, //set the function Monster_init to the init field of struct Object
    .attack = Monster_attack
};

void *Room_move(void *self,Direction direction) { //forward declared in ex19.h
    Room *room = self;
    Room *next = NULL; //initial?
    if (direction == NORTH && room->north) {
        printf("You go north, into:\n");
        next = room->north; //assign next to the field north which is a Room struct
    }
    else if(direction == SOUTH && room->south) {
        printf("You go south, into:\n");
        next = room->south;
    }
    else if(direction == EAST && room->east) {
        printf("You go east, into:\n");
        next = room->east;
    }
    else if(direction == WEST && room->west) {
        printf("You go west, into:\n");
        next = room->west;
    }
    else {
        printf("You can't go that direction.");
        next = NULL;
    }
    
    if (next) {
        next->_(describe)(next);
    }
    
    return next;

}

int Room_attack(void *self,int damage) { //forward declared in ex19.h
    Room *room = self;
    Monster *monster = room->bad_guy; //bad_guy is a field of struct Room which has a data type of Monster
    if (monster) {
        monster->_(attack)(monster,damage);
        return 1;
    }
    else {
        printf ("You flail in the air at nothing.\n");
        return 0;
    }
}

Object RoomProto = { //creates a object of type Object
    .move = Room_move, //assign this function to the field move of struct Object
    .attack = Room_attack,
};

void *Map_move(void *self, Direction direction)
{
    Map *map = self;
    Room *location = map->location;
    Room *next = NULL;
    
    next = location->_(move)(location, direction);
    
    if(next) {
        map->location = next;
    }
    
    return next;
}

int Map_attack(void *self, int damage)
{
    Map* map = self;
    Room *location = map->location;
    
    return location->_(attack)(location, damage);
}


int Map_init(void *self) {
    Map *map = self;
    Room *hall = NEW(Room,"The great Hall"); //NEW(T,N) is a macro define in object.h, in this case this will become Object_new(Room,RoomProto,"The great Hall")
    Room *throne = NEW(Room, "The throne room"); //this bothers me
    Room *arena = NEW(Room, "The arena, with the minotaur");
    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");
    
    arena->bad_guy = NEW(Monster,"The evil minotaur");
    hall->north = throne;
    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;
    arena->east = throne;
    kitchen->west = throne;
    
    map->start = hall;
    map->location = hall;
    
    return 1;
}

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int process_input(Map *game)
{
    printf("\n> ");
    
    char ch = getchar();
    getchar(); // eat ENTER
    
    int damage = rand() % 4; //random number between 0 -4
    
    switch(ch) {
        case -1:
            printf("Giving up?\n");
            return 0;
            break;
            
        case 'n':
            game->_(move)(game, NORTH);
            break;
            
        case 's':
            game->_(move)(game, SOUTH);
            break;
            
        case 'e':
            game->_(move)(game, EAST);
            break;
            
        case 'w':
            game->_(move)(game, WEST);
            break;
            
        case 'a':
            
            game->_(attack)(game, damage);
            break;
        case 'l':
            printf("You can go:\n");
            if(game->location->north) printf("NORTH\n");
            if(game->location->south) printf("SOUTH\n");
            if(game->location->east) printf("EAST\n");
            if(game->location->west) printf("WEST\n");
            break;
            
        default:
            printf("What?: %d\n", ch);
    }
    
    return 1;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    Map *game = NEW(Map, "The Hall of the Minotaur.");
    
    printf("You enter the ");
    game->location->_(describe)(game->location);
    
    while(process_input(game)) {
    }
    
    return 0;
}




