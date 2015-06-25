#include "minunit.h"
#include <lcthw/bstree.h>
#include <assert.h>
#include <lcthw/bstrlib.h>
#include <stdlib.h>
#include <time.h>

BSTree *map = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("xest data 3");
struct tagbstring expect1 = bsStatic("THE VALUE 1");
struct tagbstring expect2 = bsStatic("THE VALUE 2");
struct tagbstring expect3 = bsStatic("THE VALUE 3");

static int traverse_good_cb(BSTreeNode *node)
{
    debug("KEY: %s", bdata((bstring)node->key));
    traverse_called++;
    return 0;
}


static int traverse_fail_cb(BSTreeNode *node)
{
    debug("KEY: %s", bdata((bstring)node->key));
    traverse_called++;
    
    if(traverse_called == 2) {
        return 1;
    } else {
        return 0;
    }
}

typedef short (*haha);
typedef struct cBSTree {
    short *js;
    short jok;
    int hshs;
    double asasas;
    
} cBSTree;

cBSTree *jeff = NULL;
char *test_create()
{
    map = BSTree_create(NULL); //BSTree *BSTree_create(BSTree_compare compare)
    /*
     typedef struct BSTree {
        int count;
        BSTree_compare compare;
        BSTreeNode *root;
     } BSTree;
     
     typedef int (*BSTree_compare)(void *a, void *b);
     
     typedef struct BSTreeNode {
     void *key;
     void *data;
     
     struct BSTreeNode *left;
     struct BSTreeNode *right;
     struct BSTreeNode *parent;
     } BSTreeNode;
     
     static int default_compare(void *a, void *b)
     {
        return bstrcmp((bstring)a, (bstring)b);
     }
     
     BSTree *BSTree_create(BSTree_compare compare) i.e compare->NULL
     {
        BSTree *map = calloc(1, sizeof(BSTree)); //allocates a 1 block of memory with size of int(4) + BSTree_compare(8 byte for a pointer to a function) + BSTreeNode *(8 struct) = 24 bytes total, note: the 4 bytes of empty memory will be next to int to cover the division of by 8 bytes cause 8 is the highest
     
        check_mem(map);
     
        map->compare = compare == NULL ? default_compare : compare; // i.e compare is NULL, so this means true so map->compare = default_compare
     
        return map;
     
     error:
        if(map) {
            BSTree_destroy(map);
        }
        return NULL;
     }
     
     summary :
     map {
        count = 0;
        compare = default_compare; //a function that have implementation
        root = NULL;
     }
     
     */
    
    
    mu_assert(map != NULL, "Failed to create map.");
    
    return NULL;
}

char *test_destroy()
{
    BSTree_destroy(map);
    
    return NULL;
}


char *test_get_set()
{
    int rc = BSTree_set(map, &test1, &expect1);
    
    /*
     
     
     
     */
    mu_assert(rc == 0, "Failed to set &test1");
    bstring result = BSTree_get(map, &test1);
    mu_assert(result == &expect1, "Wrong value for test1.");
    
    rc = BSTree_set(map, &test2, &expect2);
    mu_assert(rc == 0, "Failed to set test2");
    result = BSTree_get(map, &test2);
    mu_assert(result == &expect2, "Wrong value for test2.");
    
    rc = BSTree_set(map, &test3, &expect3);
    mu_assert(rc == 0, "Failed to set test3");
    result = BSTree_get(map, &test3);
    mu_assert(result == &expect3, "Wrong value for test3.");
    
    return NULL;
}

char *test_traverse()
{
    int rc = BSTree_traverse(map, traverse_good_cb);
    mu_assert(rc == 0, "Failed to traverse.");
    mu_assert(traverse_called == 3, "Wrong count traverse.");
    
    traverse_called = 0;
    rc = BSTree_traverse(map, traverse_fail_cb);
    mu_assert(rc == 1, "Failed to traverse.");
    mu_assert(traverse_called == 2, "Wrong count traverse for fail.");
    
    return NULL;
}

char *test_delete()
{
    bstring deleted = (bstring)BSTree_delete(map, &test1);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect1, "Should get test1");
    bstring result = BSTree_get(map, &test1);
    mu_assert(result == NULL, "Should delete.");
    
    deleted = (bstring)BSTree_delete(map, &test1);
    mu_assert(deleted == NULL, "Should get NULL on delete");
    
    deleted = (bstring)BSTree_delete(map, &test2);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect2, "Should get test2");
    result = BSTree_get(map, &test2);
    mu_assert(result == NULL, "Should delete.");
    
    deleted = (bstring)BSTree_delete(map, &test3);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect3, "Should get test3");
    result = BSTree_get(map, &test3);
    mu_assert(result == NULL, "Should delete.");
    
    // test deleting non-existent stuff
    deleted = (bstring)BSTree_delete(map, &test3);
    mu_assert(deleted == NULL, "Should get NULL");
    
    return NULL;
}

char *test_fuzzing()
{
    BSTree *store = BSTree_create(NULL);
    int i = 0;
    int j = 0;
    bstring numbers[100] = {NULL};
    bstring data[100] = {NULL};
    srand((unsigned int)time(NULL));
    
    for(i = 0; i < 100; i++) {
        int num = rand();
        numbers[i] = bformat("%d", num);
        data[i] = bformat("data %d", num);
        BSTree_set(store, numbers[i], data[i]);
    }
    
    for(i = 0; i < 100; i++) {
        bstring value = BSTree_delete(store, numbers[i]);
        mu_assert(value == data[i], "Failed to delete the right number.");
        
        mu_assert(BSTree_delete(store, numbers[i]) == NULL, "Should get nothing.");
        
        for(j = i+1; j < 99 - i; j++) {
            bstring value = BSTree_get(store, numbers[j]);
            mu_assert(value == data[j], "Failed to get the right number.");
        }
        
        bdestroy(value);
        bdestroy(numbers[i]);
    }
    
    BSTree_destroy(store);
    
    return NULL;
}

char *all_tests()
{
    mu_suite_start();
    
    mu_run_test(test_create); //first call
    mu_run_test(test_get_set); //second
    mu_run_test(test_traverse);
    mu_run_test(test_delete);
    mu_run_test(test_destroy);
    mu_run_test(test_fuzzing);
    
    return NULL;
}

RUN_TESTS(all_tests);