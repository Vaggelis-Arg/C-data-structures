#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

#define DECLARE_VECTOR_ALL(TYPE)      \
DECLARE_VECTOR(TYPE)                  \
DECLARE_VECTOR_FUNCTIONS(TYPE)        \
DEFINE_VECTOR_ALL(TYPE)


#define DECLARE_VECTOR(TYPE)      \
typedef struct vector_##TYPE{     \
    TYPE *array;                  \
    size_t size;                  \
    size_t capacity;              \
} vector_##TYPE;

// VECTOR FUNCTIONS

#define DECLARE_VECTOR_FUNCTIONS(TYPE)                                                                                      \
vector_##TYPE *vector_##TYPE##_create(size_t capacity);                                                                     \
void vector_##TYPE##_free(vector_##TYPE *vector, void (*destroy)(TYPE));                                                    \
TYPE vector_##TYPE##_at(vector_##TYPE *vector, int index);                                                                  \
void vector_##TYPE##_set_at(vector_##TYPE *vector, int index, TYPE data);                                                   \
void vector_##TYPE##_push_back(vector_##TYPE *vector, TYPE data);                                                           \
void vector_##TYPE##_clear_at(vector_##TYPE *vector, int index, void (*destroy)(TYPE));                                     \
void vector_##TYPE##_delete(vector_##TYPE *vector, TYPE data, void (*destroy)(TYPE));                                       \
size_t vector_##TYPE##_partition(vector_##TYPE *vector, int (*compare)(const TYPE*, const TYPE*), size_t low, size_t high); \
void vector_##TYPE##_quicksort(vector_##TYPE *vector, int (*compare)(const TYPE*, const TYPE*), size_t low, size_t high);   \
void vector_##TYPE##_sort(vector_##TYPE *vector, int (*compare)(const TYPE*, const TYPE*));                                 \
size_t vector_##TYPE##_size(vector_##TYPE *vector);                                                                         \
size_t vector_##TYPE##_capacity(vector_##TYPE *vector);                                                                     \
int vector_##TYPE##_search(vector_##TYPE *vector, TYPE data, int (*compare)(const TYPE*, const TYPE*));


#define DEFINE_VECTOR_ALL(TYPE) \
DEFINE_VECTOR_CREATE(TYPE)      \
DEFINE_VECTOR_FREE(TYPE)        \
DEFINE_VECTOR_AT(TYPE)          \
DEFINE_VECTOR_SET_AT(TYPE)      \
DEFINE_VECTOR_PUSH_BACK(TYPE)   \
DEFINE_VECTOR_CLEAR_AT(TYPE)    \
DEFINE_VECTOR_DELETE(TYPE)      \
DEFINE_VECTOR_PARTITION(TYPE)   \
DEFINE_VECTOR_QUICKSORT(TYPE)   \
DEFINE_VECTOR_SORT(TYPE)        \
DEFINE_VECTOR_SIZE(TYPE)        \
DEFINE_VECTOR_CAPACITY(TYPE)    \
DEFINE_VECTOR_SEARCH(TYPE)


#define DEFINE_VECTOR_CREATE(TYPE)                                                                                              \
vector_##TYPE *vector_##TYPE##_create(size_t capacity) {                                                                        \
 vector_##TYPE *v = malloc(sizeof(vector_##TYPE));                                                                              \
    v->array = malloc(sizeof(TYPE) * capacity);                                                                                 \
    v->capacity = capacity;                                                                                                     \
    v->size = 0;                                                                                                                \
    return v;                                                                                                                   \
}


// Free all memory allocated for the vector and its data.
#define DEFINE_VECTOR_FREE(TYPE)                                                                                                \
void vector_##TYPE##_free(vector_##TYPE *vector, void (*destroy)(TYPE)) {                                                       \
    if (vector != NULL) {                                                                                                       \
        if (destroy != NULL) {                                                                                                  \
            for (size_t i = 0; i < vector->size; i++) {                                                                         \
                destroy(vector->array[i]);                                                                                      \
            }                                                                                                                   \
        }                                                                                                                       \
        free(vector->array);                                                                                                    \
        free(vector);                                                                                                           \
    }                                                                                                                           \
}


// Return the value stored at the given index (equivalent to [i] for arrays)
#define DEFINE_VECTOR_AT(TYPE)                                                                                                  \
TYPE vector_##TYPE##_at(vector_##TYPE *vector, int index) {                                                                     \
    return vector->array[index];                                                                                                \
}



// Set the value stored at the given index. It should handle out of bounds indices without crashing.
#define DEFINE_VECTOR_SET_AT(TYPE)                                                                                              \
void vector_##TYPE##_set_at(vector_##TYPE *vector, int index, TYPE data){                                                       \
    if(index >= vector->capacity){                                                                                              \
        fprintf(stderr, "Index does not exist in the vector array\n");                                                          \
        return;                                                                                                                 \
    }                                                                                                                           \
    else{                                                                                                                       \
        vector->array[index] = data;                                                                                            \
        if(index >= vector->size){                                                                                              \
            vector->size = index;                                                                                               \
        }                                                                                                                       \
    }                                                                                                                           \
}

// Add a new value at the end of the vector. This can grow the size of the vector.
#define DEFINE_VECTOR_PUSH_BACK(TYPE)                                                                                           \
void vector_##TYPE##_push_back(vector_##TYPE *vector, TYPE data) {                                                              \
    if(vector->size == vector->capacity){                                                                                       \
        vector->array = realloc(vector->array, 2 * vector->capacity * sizeof(TYPE));                                            \
        vector->capacity *= 2;                                                                                                  \
    }                                                                                                                           \
    vector->array[vector->size++] = data;                                                                                       \
}


// Clear the value stored at the given index. It should handle out of bounds indices without crashing.
#define DEFINE_VECTOR_CLEAR_AT(TYPE)                                                                                            \
void vector_##TYPE##_clear_at(vector_##TYPE *vector, int index, void (*destroy)(TYPE)) {                                       \
    if (index < 0 || index >= vector->size) {                                                                                   \
        fprintf(stderr, "Invalid index: %d\n", index);                                                                          \
        return;                                                                                                                 \
    }                                                                                                                           \
    if (destroy != NULL) {                                                                                                      \
        destroy(vector->array[index]);                                                                                          \
    }                                                                                                                           \
    for (int i = index ; i < vector->size - 1 ; ++i) {                                                                          \
        vector->array[i] = vector->array[i + 1];                                                                                \
    }                                                                                                                           \
    --vector->size;                                                                                                             \
}


// Delete the specified item from the vector (if found).
#define DEFINE_VECTOR_DELETE(TYPE)                                                                                              \
void vector_##TYPE##_delete(vector_##TYPE *vector, TYPE data, void (*destroy)(TYPE)) {                                         \
    int index = -1;                                                                                                             \
    for (size_t i = 0 ; i < vector->size ; ++i) {                                                                               \
        if (vector->array[i] == data) {                                                                                         \
            index = i;                                                                                                          \
            break;                                                                                                              \
        }                                                                                                                       \
    }                                                                                                                           \
    if (index != -1) {                                                                                                          \
        if (destroy != NULL) {                                                                                                  \
            destroy(vector->array[index]);                                                                                      \
        }                                                                                                                       \
        for (size_t i = index ; i < vector->size - 1 ; i++) {                                                                   \
            vector->array[i] = vector->array[i + 1];                                                                            \
        }                                                                                                                       \
        --vector->size;                                                                                                         \
    }                                                                                                                           \
}


// Helper function for QuickSort - Partition
#define DEFINE_VECTOR_PARTITION(TYPE)                                                                                              \
size_t vector_##TYPE##_partition(vector_##TYPE *vector, int (*compare)(const TYPE*, const TYPE*), size_t low, size_t high) {       \
    if (low >= high || high >= vector->size) {                                                                                     \
        return low;                                                                                                                \
    }                                                                                                                              \
    TYPE pivot = vector->array[high];                                                                                              \
    size_t i = low - 1;                                                                                                            \
    for (size_t j = low; j < high; j++) {                                                                                          \
        if (compare(&vector->array[j], &pivot) < 0) {                                                                              \
            i++;                                                                                                                   \
            TYPE temp = vector->array[i];                                                                                          \
            vector->array[i] = vector->array[j];                                                                                   \
            vector->array[j] = temp;                                                                                               \
        }                                                                                                                          \
    }                                                                                                                              \
    TYPE temp = vector->array[i + 1];                                                                                              \
    vector->array[i + 1] = vector->array[high];                                                                                    \
    vector->array[high] = temp;                                                                                                    \
    return i + 1;                                                                                                                  \
}


// Helper function for QuickSort - Recursive QuickSort
#define DEFINE_VECTOR_QUICKSORT(TYPE)                                                                                            \
void vector_##TYPE##_quicksort(vector_##TYPE *vector, int (*compare)(const TYPE*, const TYPE*), size_t low, size_t high) {       \
    if (low < high) {                                                                                                            \
        size_t pi = vector_##TYPE##_partition(vector, compare, low, high);                                                       \
        if (pi > 0)                                                                                                              \
            vector_##TYPE##_quicksort(vector, compare, low, pi - 1);                                                             \
        vector_##TYPE##_quicksort(vector, compare, pi + 1, high);                                                                \
    }                                                                                                                            \
}



// Sort the elements in the vector using the QuickSort algorithm and a custom compare function.
#define DEFINE_VECTOR_SORT(TYPE)                                                                                                  \
void vector_##TYPE##_sort(vector_##TYPE *vector, int (*compare)(const TYPE*, const TYPE*)) {                                      \
    size_t size = vector->size;                                                                                                   \
    if (size > 1) {                                                                                                               \
        vector_##TYPE##_quicksort(vector, compare, 0, size - 1);                                                                  \
    }                                                                                                                             \
}



// Return the size of the vector
#define DEFINE_VECTOR_SIZE(TYPE)                                                                                                \
size_t vector_##TYPE##_size(vector_##TYPE *vector) {                                                                            \
    return vector->size;                                                                                                        \
}


// Return the capacity of the vector
#define DEFINE_VECTOR_CAPACITY(TYPE)                                                                                            \
size_t vector_##TYPE##_capacity(vector_##TYPE *vector) {                                                                        \
    return vector->capacity;                                                                                                    \
}


// Search the vector for an item using a compare function. Returns the index of the first occurrence if found, otherwise -1.
#define DEFINE_VECTOR_SEARCH(TYPE)                                                                                              \
int vector_##TYPE##_search(vector_##TYPE *vector, TYPE data, int (*compare)(const TYPE*, const TYPE*)) {                        \
    for (size_t i = 0; i < vector->size; i++) {                                                                                 \
        if (compare(&vector->array[i], &data) == 0) {                                                                           \
            return i;                                                                                                           \
        }                                                                                                                       \
    }                                                                                                                           \
    return -1;                                                                                                                  \
}

#endif