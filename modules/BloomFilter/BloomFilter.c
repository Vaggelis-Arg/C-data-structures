#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "BloomFilter.h"



struct bloom_filter{
    unsigned char *bit_array;
    unsigned int size;
    HashFunc *hash;
    unsigned int hash_count;
};



//Function to create a bloom filter
BloomFilter bloom_filter_create(unsigned int size, unsigned int hash_count, HashFunc *hash) {
    
    BloomFilter bf = malloc(sizeof(*bf));
    bf->bit_array = calloc((size << 3) | 1, sizeof(unsigned char));
    assert(bf->bit_array != NULL);
    bf->size = size;
    bf->hash_count = hash_count;
    bf->hash = hash;

    return bf;
}


// Helper functions for bit operations


// Set 1 the (hash % 8) bit of the (hash / 8) bit array position
static inline void bloom_filter_set_bit(BloomFilter bf, unsigned int hash) {
    bf->bit_array[hash >> 3] |= (1 << (hash & 7)); // hash & 7 equals to hash hash % 8 
}


// Get the (hash % 8) bit of the (hash / 8) bit array position
static inline unsigned int bloom_filter_get_bit(BloomFilter bf, unsigned int hash) {
    return (((bf->bit_array[hash >> 3] & (1 << (hash & 7)))) != 0);
}


// Function to insert a key into the bloom filter
void bloom_filter_insert(BloomFilter bf, void *key) {
    assert((bf != NULL) && (key != NULL));
    for(int i = 0 ; i < bf->hash_count ; i++)
        bloom_filter_set_bit(bf, bf->hash[i](key) & (bf->size - 1));
}


// Function to check if a key might be in the bloom filter
bool bloom_filter_check(BloomFilter bf, void *key) {
    bool exists = true;
    for(int i = 0 ; i < bf->hash_count ; i++)
        exists &= bloom_filter_get_bit(bf, ((bf->hash[i](key)) & (bf->size - 1)));
    
    return exists;
}


// Function to reset the bloom filter (Set 0 in every bit of it)
void bloom_filter_reset(BloomFilter bf) {
    memset(bf->bit_array, 0, sizeof(unsigned char) * bf->size);
}


//Function to destroy the bloom filter
void bloom_filter_destroy(BloomFilter bf) {
    free(bf->bit_array);
    free(bf);
}