#ifndef CODE_HASHTABLE_H
#define CODE_HASHTABLE_H

#include <stdbool.h>


typedef struct bloom_filter *BloomFilter;

// Function which returns a hash value according to the given key
typedef size_t (*HashFunc)(void *);

//Function to create a bloom filter
BloomFilter bloom_filter_create(const unsigned int size, const unsigned int hash_count, HashFunc *hash);

// Function to insert a key into the bloom filter
void bloom_filter_insert(BloomFilter bf, void *key);

// Function to check if a key might be in the bloom filter
bool bloom_filter_check(BloomFilter bf, void *key);

// Function to reset the bloom filter (Set 0 in every bit of it)
void bloom_filter_reset(BloomFilter bf);

//Function to destroy the bloom filter
void bloom_filter_destroy(BloomFilter bf);


#endif //CODE_HASHTABLE_H