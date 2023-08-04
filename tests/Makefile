# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wpedantic -std=c11
LDFLAGS :=

# Source files directories
SRC_DIR := ../modules

# Source files for Data Structures test
AVL_SOURCE := $(SRC_DIR)/AVLTree/AVLTree.c AVLTree_test.c
BF_SOURCE := $(SRC_DIR)/BloomFilter/BloomFilter.c BloomFilter_test.c
DH_HASHTABLE_SOURCE := $(SRC_DIR)/DoubleHashingHashTable/DoubleHashingHashTable.c DH_Hashtable_test.c
DLL_SOURCE := $(SRC_DIR)/DoubleLinkedList/DoubleLinkedList.c DoubleLinkedList_test.c
PQ_SOURCE := $(SRC_DIR)/PriorityQueue/PriorityQueue.c PriorityQueue_test.c
QUEUE_SOURCE := $(SRC_DIR)/Queue/Queue.c Queue_test.c
RBT_SOURCE := $(SRC_DIR)/RedBlackTree/RedBlackTree.c RedBlackTree_test.c
SC_HASHTABLE_SOURCE := $(SRC_DIR)/SeparateChainingHashTable/ChainingHashTable.c $(SRC_DIR)/SeparateChainingHashTable/LinkedLists/list.c ChainingHashTable_test.c
SKIP_LIST_SOURCE := $(SRC_DIR)/SkipList/SkipList.c SkipList_test.c
STACK_SOURCE := $(SRC_DIR)/Stack/Stack.c Stack_test.c
VECTOR_SOURCE := Vector_test.c

# Object files for Data Structures tests
AVL_OBJECTS := $(AVL_SOURCE:.c=.o)
BF_OBJECTS := $(BF_SOURCE:.c=.o)
DH_HASHTABLE_OBJECTS := $(DH_HASHTABLE_SOURCE:.c=.o)
DLL_OBJECTS := $(DLL_SOURCE:.c=.o)
PQ_OBJECTS := $(PQ_SOURCE:.c=.o)
QUEUE_OBJECTS := $(QUEUE_SOURCE:.c=.o)
RBT_OBJECTS := $(RBT_SOURCE:.c=.o)
SC_HASHTABLE_OBJECTS := $(SC_HASHTABLE_SOURCE:.c=.o)
SKIP_LIST_OBJECTS := $(SKIP_LIST_SOURCE:.c=.o)
STACK_OBJECTS := $(STACK_SOURCE:.c=.o)
VECTOR_OBJECTS := $(VECTOR_SOURCE:.c=.o)

# Executable for Data Structures tests
AVL_EXECUTABLE := AVLTree_test
BF_EXECUTABLE := BloomFilter_test
DH_HASHTABLE_EXECUTABLE := DH_Hashtable_test
DLL_EXECUTABLE := DoubleLinkedList_test
PQ_EXECUTABLE := PriorityQueue_test
QUEUE_EXECUTABLE := Queue_test
RBT_EXECUTABLE := RedBlackTree_test
SC_HASHTABLE_EXECUTABLE := ChainingHashTable_test
SKIP_LIST_EXECUTABLE := SkipList_test
STACK_EXECUTABLE := Stack_test
VECTOR_EXECUTABLE := Vector_test

.PHONY: all clean

all: $(AVL_EXECUTABLE) $(BF_EXECUTABLE) $(DH_HASHTABLE_EXECUTABLE) $(PQ_EXECUTABLE) $(QUEUE_EXECUTABLE) $(RBT_EXECUTABLE) $(SC_HASHTABLE_EXECUTABLE) \
$(SKIP_LIST_EXECUTABLE) $(STACK_EXECUTABLE) $(VECTOR_EXECUTABLE) $(DLL_EXECUTABLE)

# Compile Data Structures tests
$(AVL_EXECUTABLE): $(AVL_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
$(BF_EXECUTABLE): $(BF_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
$(DH_HASHTABLE_EXECUTABLE): $(DH_HASHTABLE_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
$(DLL_EXECUTABLE): $(DLL_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
$(PQ_EXECUTABLE): $(PQ_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
$(QUEUE_EXECUTABLE): $(QUEUE_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
$(RBT_EXECUTABLE): $(RBT_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
$(SC_HASHTABLE_EXECUTABLE): $(SC_HASHTABLE_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
$(SKIP_LIST_EXECUTABLE): $(SKIP_LIST_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
$(STACK_EXECUTABLE): $(STACK_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
$(VECTOR_EXECUTABLE): $(VECTOR_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Compile C source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(AVL_EXECUTABLE) $(AVL_OBJECTS) $(BF_EXECUTABLE) $(BF_OBJECTS) $(DH_HASHTABLE_EXECUTABLE) $(DH_HASHTABLE_OBJECTS) $(DLL_EXECUTABLE) \
	$(DLL_OBJECTS) $(PQ_EXECUTABLE) $(PQ_OBJECTS) $(QUEUE_EXECUTABLE) $(QUEUE_OBJECTS) $(RBT_EXECUTABLE) $(RBT_OBJECTS) $(SC_HASHTABLE_EXECUTABLE) \
	$(SC_HASHTABLE_OBJECTS) $(SKIP_LIST_EXECUTABLE) $(SKIP_LIST_OBJECTS) $(STACK_EXECUTABLE) $(STACK_OBJECTS) $(VECTOR_EXECUTABLE) $(VECTOR_OBJECTS)