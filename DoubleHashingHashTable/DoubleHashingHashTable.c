/* File: DoubleHashingHashTable.c */
/* This file contains an implementation of hash table using double hashing technic */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "DoubleHashingHashTable.h"



#define MAX_LOAD_FACTOR 0.7


// The numbers in the following array are considered to be good hash table primes (https://planetmath.org/goodhashtableprimes)
static int prime_numbers[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241,
	786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};


static int primes_index = 0;


typedef enum {
    EMPTY, OCCUPIED, DELETED
} State;


typedef struct {
    void *key;
    void *value;
    State state;
} hashtable_node;


struct hashtable {
    hashtable_node *table;
    size_t capacity;
    size_t size;
    size_t deleted_items;
    CompareFunc compare;
    PrintFunc print;
    DestroyFunc destroy_key;
    DestroyFunc destroy_value;
    HashFunc hash_function; // First hash
    HashFunc hash_function_2; // Second hash
};


Hashtable *hashtable_create(CompareFunc compare, DestroyFunc destroy_key, DestroyFunc destroy_value, PrintFunc print, HashFunc hash, HashFunc hash2) {
    assert(compare != NULL && destroy_key != NULL && destroy_value != NULL && print != NULL && hash != NULL && hash2 != NULL);
    Hashtable *h = malloc(sizeof(*h));
    assert(h != NULL);

    h->capacity = prime_numbers[primes_index];

    h->table = calloc(h->capacity, sizeof(*h->table));
    assert(h->table != NULL);

    h->size = h->deleted_items = 0;

    h->compare = compare;
    h->destroy_key = destroy_key;
    h->destroy_value = destroy_value;
    h->print = print;
    h->hash_function = hash;
    h->hash_function_2 = hash2;

    return h;
}


// Function which returns the size of the hash table (how many items does it currently store) or -1 if given hash table does not exist
size_t hashtable_size(Hashtable *h) {
    if(h == NULL){
        fprintf(stderr, "Given hash table does not exist\n");
        return -1;
    }
    return h->size;
}


// Hash function : returns the hash value according to the given key 
static size_t hashtable_hash(Hashtable *h, void *key) {
    assert(h != NULL && key != NULL);
    return h->hash_function(key) % h->capacity;
}


// Hash function : returns the secondary hash value according to the given key
size_t hashtable_secondary_hash(Hashtable *h, void *key) {
    assert(h != NULL && key != NULL);
    size_t hash_value = h->hash_function_2(key) % h->capacity;
    return hash_value != 0 ? hash_value : 1;
}


// Check if given number is prime 
static bool isprime(size_t n) {
	if((n % 2 == 0 && n != 2) || (n % 3 == 0 && n != 3))
		return false;
	int divisor;
	for(divisor = 5 ; divisor*divisor <= n ; divisor += 6)
		if((n % divisor == 0) || (n % (divisor + 2) == 0))
			return false;
	return true;
}


// Resizes the hash table and rehashes the keys of the nodes which are currently occupied
static Hashtable *hashtable_resize(Hashtable *h) {
    size_t old_capacity = h->capacity;
    hashtable_node *old_table = h->table;

    // Update the capacity of the hash table
    if(++primes_index < sizeof(prime_numbers) / sizeof(int))
        h->capacity = prime_numbers[primes_index];
    else
        // If the primes index has exceeded the size of the array which holds the prime numbers, we should find the next prime number manually
        while(!isprime(++(h->capacity)));

    h->table = calloc(h->capacity , sizeof(*h->table));
    assert(h->table != NULL);

    h->size = 0;

    // We insert only entries which store indeed an element (eliminate deleted nodes)
    for(int i = 0 ; i < old_capacity ; i++)
        if(old_table[i].state == OCCUPIED)
            hashtable_insert(h, old_table[i].key, old_table[i].value);

    free(old_table);
    return h;
}


// Inserts a [key - value] pair into the hash table (Implementing ADT Map)
Hashtable *hashtable_insert(Hashtable *h, void *key, void *value) {
    if(h == NULL){
        fprintf(stderr, "Given hash table does not exist\n");
        return NULL;
    }
    bool already_in_hashtable = false, first_probe = true;
    hashtable_node *node = NULL;
    size_t pos, step_size = hashtable_secondary_hash(h, key);

    // Search until we find empty position to nsert the given data
    for(pos = hashtable_hash(h, key) ; h->table[pos].state != EMPTY ; pos = (pos + step_size) % h->capacity) {
        
        // Found position in which an item has been deleted
        // Do not end the loop, because the given data might already exist in the hash table
        // Continue until the next empty position, or until you find that a node with the same key is already inserted into the hash table 
        if(h->table[pos].state == DELETED) {
            if(node == NULL)
                node = &h->table[pos];
        }
        // Found item eith the same key
        else if(h->compare(h->table[pos].key, key) == 0) {
            already_in_hashtable = true;
            node = &h->table[pos];
            break;
        }

        if (pos == hashtable_hash(h, key)) {
            if(first_probe)
                first_probe = false;
            else
                // Hashtable positions where the given item could be inserted using double hashing are all occupied or deleted
                // Do linear probing until you find an empty position (an empty position exists for sure, because the load factor is 0.7
                // which means that the 30% of the position at least are empty)
               step_size = 1;
        }
    }

    if(node == NULL)
        node = &h->table[pos];

    // If there does already exist an item with the same key into the hash table, just update it's value
    if(already_in_hashtable){
        if(node->value != value && h->destroy_value != NULL){
            h->destroy_value(node->value);
            node->value = value;
        }
        else {
            h->destroy_value(value);
        }
        return h;
    }
    
    if(node->state == DELETED)
        h->deleted_items--;

    // Update node
    h->size++;
    node->state = OCCUPIED;
    node->key = key;
    node->value = value;

    // Check if the hash table needs to be resized
    double load_factor = ((double)(h->size + h->deleted_items)) / ((double) h->capacity);
    if(load_factor > MAX_LOAD_FACTOR)
        hashtable_resize(h);

    return h;
}


// Function which searches a value according to the given key and returns the value if it finds the key, otherwise it returns NULL 
void *hashtable_search(Hashtable *h, void *key) {
    if (h == NULL) {
        fprintf(stderr, "Given hash table does not exist\n");
        return NULL;
    }
    bool first_probe = true;
    size_t step_size = hashtable_secondary_hash(h, key);
    for (size_t i = hashtable_hash(h, key) ; h->table[i].state != EMPTY ; i = (i + step_size) % h->capacity) {
        if ((h->table[i].state == OCCUPIED) && (h->compare(h->table[i].key, key) == 0))
            return h->table[i].value;
        if (i == hashtable_hash(h, key)) {
            if(first_probe)
                first_probe = false;
            else
               step_size = 1;
        }
    }
    return NULL;
}


// Deletes node with given key from the hash table using double hashing for probing
bool hashtable_remove(Hashtable *h, void *key) {
    if (h == NULL) {
        fprintf(stderr, "Given hash table does not exist\n");
        return false;
    }

    size_t step_size = hashtable_secondary_hash(h, key);
    bool first_probe = true;

    for (size_t i = hashtable_hash(h, key) ; h->table[i].state != EMPTY ; i = (i + step_size) % h->capacity) {
        if ((h->table[i].state == OCCUPIED) && (h->compare(h->table[i].key, key) == 0)) {
            if (h->destroy_key != NULL)
                h->destroy_key(h->table[i].key);
            if (h->destroy_value != NULL)
                h->destroy_value(h->table[i].value);
            h->table[i].state = DELETED;

            h->deleted_items++;
            h->size--;
            return true;
        }

        if (i == hashtable_hash(h, key)) {
            if(first_probe)
                first_probe = false;
            else
               step_size = 1;
        }
    }

    return false;
}


// Function which prints the values of the hash table
void hashtable_print(Hashtable *h) {
    if(h == NULL){
        fprintf(stderr, "Given hash table does not exist\n");
        return;
    }
    if(h->size == 0) {
        printf("Hash table has no items\n");
        return;
    }
    printf("Hash Table values:\n");
    for(size_t i = 0 ; i < h->capacity ; i++) {
        if(h->table[i].state == OCCUPIED){
            h->print(h->table[i].value);
            printf(" ");
        }
    }
    printf("\n");
}


// Destroy hash table - free the memory which is allocated by the hash table
void hashtable_destroy(Hashtable *h) {
    for(int i = 0 ; i < h->capacity ; i++) {
        if(h->table[i].state == OCCUPIED) {
            if(h->destroy_key != NULL)
                h->destroy_key(h->table[i].key);
            if(h->destroy_value != NULL)
                h->destroy_value(h->table[i].value);
        }
    }
    free(h->table);
    free(h);
}