#include <lcthw/list.h>
#include <lcthw/dbg.h>

List *List_create()
{
    return calloc(1, sizeof(List)); //allocates a memory of size List note: doesn't have to be sizeof(struct List) cause List is a typedef
}

void List_destroy(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        if(cur->prev) {
            free(cur->prev);
        }
    }
    
    free(list->last);
    free(list);
}


void List_clear(List *list)
{
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}


void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}


void List_push(List *list, void *value) //called second after List_create()
{
    ListNode *node = calloc(1, sizeof(ListNode)); //allocates a memory for ListNode struct
    check_mem(node);
    
    node->value = value; //value (right) is of type void * (i.e char * : "test1 data") assign it to field of ListNode struct value (left) which is of type void *
    
    if(list->last == NULL) { //if the field last which is a struct ListNode empty do this, (i.e this is empty so this is true)
        
        list->first = node; //assign struct ListNode to first which is of struct ListNode type also
        list->last = node;
    } else { //if last field of list ehich is of type struct ListNode is not empty do this
        list->last->next = node; //go in struct List go to last field which is a struct ListNode and then go to field next which is a struct ListNode (first defenition) and assign node which is struct ListNode
        node->prev = list->last; //node is of struct ListNode access its field prev which is of struct ListNode, assign field last from list which is of struct List so that means last is of struct ListNode to the field prev
        list->last = node; //then assign node which is of struct ListNode to field last which is of struct ListNode
        
        //stop at this one will go back after some few exercises.....
    }
    
    list->count++;
    
error:
    return;
}

void *List_pop(List *list)
{
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);
    
    node->value = value;
    
    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }
    
    list->count++;
    
error:
    return;
}

void *List_shift(List *list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *result = NULL;
    
    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");
    
    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }
    
    list->count--;
    result = node->value;
    free(node);
    
error:
    return result;
}