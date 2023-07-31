
# path to the modules directory
DS = ../modules


CC = gcc
CFLAGS += -O2 -Wall
LDFLAGS =


# object files - modules
OBJ = $(DS)/Stack/Stack.o \
	  $(DS)/Queue/Queue.o \
	  $(DS)/PriorityQueue/PriorityQueue.o \
	  $(DS)/RedBlackTree/RedBlackTree.o \
	  $(DS)/DoubleHashingHashTable/DoubleHashingHashTable.o \
	  $(DS)/SeparateChainingHashTable/LinkedLists/list.o \
	  $(DS)/SeparateChainingHashTable/ChainingHashTable.o \
	  $(DS)/BloomFilter/BloomFilter.o \
	  $(DS)/AVLTree/AVLTree.o \
	  $(DS)/SkipList/SkipList.o


# Library name and output
LIB_NAME = LibDataStructures.a

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	ar rcs $@ $^

clean:
	rm -f $(OBJ) $(LIB_NAME)