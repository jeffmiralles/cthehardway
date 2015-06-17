#include <stdio.h> //imports from libraries
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person { //create a struct
    char *name; //field for this struct
    int age; //field
    int height; //field
    int weight; //field
};

struct Person *Person_create (char *name,int age,int height,int weight) { //a function that needs to return a type of struct Person, accepts 4 arguments
    struct Person *who = malloc (sizeof(struct Person)); //allocates a memory of a total size of struct of Person
    assert (who != NULL); //this makes sure that what you allocate exist from memory?, if it doesn't it will abort program
    who -> name = strdup(name); //assign a field from the struct a value passed in the argument char *name, strdup copies the string into a memory
    who -> age = age; //assigning age argument to this struct field
    who -> height = height;
    who -> weight = weight;
    return who; //returns this newly allocated struct Person
}

void Person_destroy(struct Person *who) { //use for cleaning up memory to avoid memory leak
    assert (who != NULL); //again making sure that it exist
    free(who->name); //free this one and the copy that it make from the strdup?
    free(who); //free the memory used, concept of deallocate?
}
void Person_print (struct Person *who) { //a function that will print the fields in the struct
    printf("Name: %s\n",who->name);
    printf("\tAge: %d\n",who->age);
    printf("\tHeight: %d\n",who->height);
    printf("\tWeight: %d\n",who->weight);
}
int main (int argc,char *argv[]) {
    struct Person *joe = Person_create("Joe Alex",32,64,140); //calls the function Person_create put its returned value to a pointer to struct Person
    struct Person *frank = Person_create("Frank Blank",20,72,180);
    
    printf("Joe is at memory location %p:\n", joe); //the address in the memory where this pointer is located
    Person_print(joe); //calls the function Person_print
    
    printf("Frank is at memory location %p:\n",frank);
    Person_print(frank);
    
    joe -> age += 20; //reassigning values to the fields
    joe -> height -= 2;
    joe -> weight += 40;
    Person_print(joe);
    
    frank -> age += 20;
    frank -> weight += 20;
    Person_print(frank);
    
    Person_destroy(joe); //calls the Person_destroy function
    Person_destroy(frank);
    
    return 0; //return 0 for success
}