#include <stdio.h>
#include <stdlib.h>
#include "acutest/acutest.h"
#include "../modules/BloomFilter/BloomFilter.h"

// Define the hash functions
long unsigned int DJB2_hash(void *k){
    char *key = (char *)k;
    unsigned int hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

long unsigned int SDBM_hash(void *k) {
    char *key = (char *)k;
    unsigned int hash = 0;
    int c;

    while ((c = *key++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

long unsigned int h1(void *k) {
    char *key = (char *)k;
    unsigned int hash = 0;
    int c;

    while ((c = *key++))
        hash += c;

    return hash;
}

void test_bloom_filter_create() {
    // Define the hash functions
    HashFunc hash_functions[] = {DJB2_hash, SDBM_hash, h1};

    // Test creating a bloom filter
    BloomFilter bf = bloom_filter_create(64, 3, hash_functions);
    TEST_CHECK(bf != NULL);

    bloom_filter_destroy(bf);
}

void test_bloom_filter_insert_and_check() {
    // Define the hash functions
    HashFunc hash_functions[] = {DJB2_hash, SDBM_hash, h1};
    BloomFilter bf = bloom_filter_create(64, 3, hash_functions);

    // Test inserting and checking a key
    int key = 42;
    bloom_filter_insert(bf, &key);
    TEST_CHECK(bloom_filter_check(bf, &key));

    // Test checking a non-inserted key
    int non_inserted_key = 123;
    TEST_CHECK(!bloom_filter_check(bf, &non_inserted_key));

    bloom_filter_destroy(bf);
}

void test_bloom_filter_reset() {
    // Define the hash functions
    HashFunc hash_functions[] = {DJB2_hash, SDBM_hash, h1};
    BloomFilter bf = bloom_filter_create(64, 3, hash_functions);

    // Insert a key and reset the bloom filter
    int key = 42;
    bloom_filter_insert(bf, &key);
    TEST_CHECK(bloom_filter_check(bf, &key));
    bloom_filter_reset(bf);
    TEST_CHECK(!bloom_filter_check(bf, &key));

    bloom_filter_destroy(bf);
}

TEST_LIST = {
    {"test_bloom_filter_create", test_bloom_filter_create},
    {"test_bloom_filter_insert_and_check", test_bloom_filter_insert_and_check},
    {"test_bloom_filter_reset", test_bloom_filter_reset},
    {NULL, NULL} // End of the test list
};