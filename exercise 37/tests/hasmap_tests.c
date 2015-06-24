#include "minunit.h"
#include <lcthw/hashmap.h>
#include <assert.h>
#include <lcthw/bstrlib.h>

Hashmap *map = NULL;
static int traverse_called = 0;
struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("xest data 3");
struct tagbstring expect1 = bsStatic("THE VALUE 1");
struct tagbstring expect2 = bsStatic("THE VALUE 2");
struct tagbstring expect3 = bsStatic("THE VALUE 3");

static int traverse_good_cb(HashmapNode *node)
{
    debug("KEY: %s", bdata((bstring)node->key));
    traverse_called++;
    return 0;
}


static int traverse_fail_cb(HashmapNode *node)
{
    debug("KEY: %s", bdata((bstring)node->key));
    traverse_called++;
    
    if(traverse_called == 2) {
        return 1;
    } else {
        return 0;
    }
}


char *test_create() //first one to be called
{
    map = Hashmap_create(NULL, NULL);
    /*
     map is of Hashmap struct
     {
        DArray *buckets;
        Hashmap_compare compare;
        Hashmap_hash hash;
     }
     
     at first map is define within this scope of the file and it is of type struct Hashmap and value of NULL
     
     struct DArray {
        int end;
        int max;
        size_t element_size;
        size_t expand_rate;
        void **contents;
     }
     
     Hashmap_compare is from a typedef of a function
     int (*Hashmap_compare)(void *a, void *b);
     
     Hashmap_hash is from a typedef of a function
     uint32_t (*Hashmap_hash)(void *key);
     
     Hashmap *Hashmap_create(compare->NULL, hash->NULL)
     {
        Hashmap *map = calloc(1, sizeof(Hashmap)); //allocates and initialize a memory of size DArray *buckets (8 because DArray is a struct) + Hashmap_compare compare (8 cause Hashmap_compare is a typedef) + Hashmap_hash hash (8) = 24 bytes total
        check_mem(map);
     
        map->compare = compare == NULL ? default_compare : compare; //ternary,assign a value to compare (must be of a function: int (void *a, void *b)) since the value of the parameter compare is NULL assign default_compare to the field compare note : same signature,, default_compare is int (void *a, void *b) code below it is: return bstrcmp((bstring)a, (bstring)b);
     
        map->hash = hash == NULL ? default_hash : hash;
     //static uint32_t default_hash(void *a) ==default_hash function==
     {
        size_t len = blength((bstring)a);
        char *key = bdata((bstring)a);
        uint32_t hash = 0;
        uint32_t i = 0;
     
        for(hash = i = 0; i < len; ++i)
        {
            hash += key[i];
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
     
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
     
        return hash;
     }
     
     
     
        map->buckets = DArray_create(sizeof(DArray *), DEFAULT_NUMBER_OF_BUCKETS); DEFAULT_NUMBER_OF_BUCKETS 100, DArray_create will allocate a memory for struct DArray and store it to bukets
     
     
     
        map->buckets->end = map->buckets->max; // fake out expanding it ????????
        check_mem(map->buckets);
     
        return map;
     
     error:
        if(map) {
            Hashmap_destroy(map);
        }
     
     return NULL;
     }
     
     
     SUMMARY: i.e Hashmap_create (NULL,NULL)
     map {
        buckets {
            end = 100;
            max = 100;
            element_size = 8;
            expand_rate = 300;
            *contents = NULL; //the first value of **contents
        }
        compare = default_compare;
        hash = default_hash;
     }
     
     */
    mu_assert(map != NULL, "Failed to create map.");
    
    return NULL;
}

char *test_destroy()
{
    Hashmap_destroy(map);
    
    return NULL;
}


char *test_get_set() //second call
{
    int rc = Hashmap_set(map, &test1, &expect1); //pass the map (struct Hashmap) which has a value now since the first call (test_create), poiter to test1 (holds a data unsigned "test data 1") and expect1 pointer (holds a data THE VALUE 1)
    /*
     int Hashmap_set(Hashmap *map, void *key, void *data)
     {
        uint32_t hash = 0; //uint32_t = unsigned int
     
        DArray *bucket = Hashmap_find_bucket(map, key, 1, &hash);
     static inline DArray *Hashmap_find_bucket(Hashmap *map, void *key,int create, uint32_t *hash_out) //passing (map,coid *,1,&hash) void * = &test1
     {
        uint32_t hash = map->hash(key); //map is accessing the field hash with a given parameter key (void * or &test1)
     static uint32_t default_hash(void *a)
     {
        size_t len = blength((bstring)a); //blength will get the length of the unsigned char * "test data 1" i.e 11 not including the \0 a must be typecast to bstring or it will result an incompatible pointer type at the function blength
     
        char *key = bdata((bstring)a); //bdata get the unsigned char * "test data 1"
        uint32_t hash = 0;
        uint32_t i = 0;
     
        for(hash = i = 0; i < len; ++i) //loops 11 times
        {
            hash += key[i]; // first loop: hash = 0 + key[0] at key[0] there is a byte data that is 0x74 ('t') + 0 = 0x74 so hash = 0x74 or 116 unsigned int
            hash += (hash << 10); //hash = 0x74 + (0x74 << 10) << bit shift left 10 bits: 0x74 = 0111 0100  <<10   1 1101 0000 0000 0000 = 0x1D000 + 0x74 = 0x1D074 or 118900
            hash ^= (hash >> 6); // 0x1D074 ^ (0xD074 >> 6) 0001 1101 0000 0111 0100  >>6
            0001 1101 0000 0111 0100
            0000 0000 0111 0100 0001
           =0001 1101 0111 0011 0101  = 0x1D735 or 120629 //follow this through
     
        }
     
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
     
        return hash;
     }
     
        int bucket_n = hash % DEFAULT_NUMBER_OF_BUCKETS;
        check(bucket_n >= 0, "Invalid bucket found: %d", bucket_n);
        *hash_out = hash; // store it for the return so the caller can use it
     
     
        DArray *bucket = DArray_get(map->buckets, bucket_n);
     
        if(!bucket && create) {
            // new bucket, set it up
            bucket = DArray_create(sizeof(void *), DEFAULT_NUMBER_OF_BUCKETS);
            check_mem(bucket);
            DArray_set(map->buckets, bucket_n, bucket);
        }
     
     return bucket;
     
     error:
     return NULL;
     }
     
        check(bucket, "Error can't create bucket.");
     
        HashmapNode *node = Hashmap_node_create(hash, key, data);
        check_mem(node);
     
        DArray_push(bucket, node);
     
        return 0;
     
     error:
        return -1;
     }
     
     */
    
    
    mu_assert(rc == 0, "Failed to set &test1");
    bstring result = Hashmap_get(map, &test1);
    mu_assert(result == &expect1, "Wrong value for test1.");
    
    rc = Hashmap_set(map, &test2, &expect2);
    mu_assert(rc == 0, "Failed to set test2");
    result = Hashmap_get(map, &test2);
    mu_assert(result == &expect2, "Wrong value for test2.");
    
    rc = Hashmap_set(map, &test3, &expect3);
    mu_assert(rc == 0, "Failed to set test3");
    result = Hashmap_get(map, &test3);
    mu_assert(result == &expect3, "Wrong value for test3.");
    
    return NULL;
}

char *test_traverse()
{
    int rc = Hashmap_traverse(map, traverse_good_cb);
    mu_assert(rc == 0, "Failed to traverse.");
    mu_assert(traverse_called == 3, "Wrong count traverse.");
    
    traverse_called = 0;
    rc = Hashmap_traverse(map, traverse_fail_cb);
    mu_assert(rc == 1, "Failed to traverse.");
    mu_assert(traverse_called == 2, "Wrong count traverse for fail.");
    
    return NULL;
}

char *test_delete()
{
    bstring deleted = (bstring)Hashmap_delete(map, &test1);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect1, "Should get test1");
    bstring result = Hashmap_get(map, &test1);
    mu_assert(result == NULL, "Should delete.");
    
    deleted = (bstring)Hashmap_delete(map, &test2);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect2, "Should get test2");
    result = Hashmap_get(map, &test2);
    mu_assert(result == NULL, "Should delete.");
    
    deleted = (bstring)Hashmap_delete(map, &test3);
    mu_assert(deleted != NULL, "Got NULL on delete.");
    mu_assert(deleted == &expect3, "Should get test3");
    result = Hashmap_get(map, &test3);
    mu_assert(result == NULL, "Should delete.");
    
    return NULL;
}

char *all_tests()
{
    mu_suite_start();
    
    mu_run_test(test_create);
    mu_run_test(test_get_set);
    mu_run_test(test_traverse);
    mu_run_test(test_delete);
    mu_run_test(test_destroy);
    
    return NULL;
}

RUN_TESTS(all_tests);