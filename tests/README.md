## C-data-structures Project - Tests

This project contains a collection of data structures implemented in C. This README file focuses on the compilation process for the test suite of these data structures.

### Compilation

To compile the tests for the data structures, you can use the provided Makefile. The Makefile is configured to build test executables for each data structure.

#### Prerequisites

Ensure that you have the following installed on your system:

- GCC (GNU Compiler Collection)

#### Compilation Steps

1. Open a terminal or command prompt.

2. Navigate to the root directory of the project (where the Makefile is located).

3. To build all the test executables for the data structures, use the following command:

```bash
make all
```

This will compile all the test files for each data structure and generate corresponding executable files.

Test Executables
The Makefile generates individual test executables for each data structure. Below is a list of the data structure test executables that will be generated:

- AVLTree_test
- BloomFilter_test
- DH_Hashtable_test
- DoubleLinkedList_test
- PriorityQueue_test
- Queue_test
- RedBlackTree_test
- ChainingHashTable_test
- SkipList_test
- Stack_test
- Vector_test

### Running Tests
After successfully compiling the test executables, you can run them to verify the correctness and functionality of the data structures.

To execute a particular test, simply type the name of the corresponding executable in the terminal and press Enter. For example, to run tests for the AVL tree, use:

```bash
./AVLTree_test
```

Similarly, you can run tests for other data structures by executing their respective test executables.


### Cleaning Up
To remove the compiled object files and executables, you can use the following command:
```bash
make clean
```

This will delete all the generated object files and test executables, leaving the project directory clean.


That's it! You should now have the data structures test suite compiled and ready to run. Feel free to explore and test the functionalities of each data structure.