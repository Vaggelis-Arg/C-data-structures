# Stack

A [stack](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)) is a linear data structure that follows the Last In, First Out (LIFO) principle. It means that the element added last to the stack will be the first one to be removed. It is like a stack of plates, where you can only add or remove plates from the top. The stack implementation of the present folder is using linked lists.

## Operations

A stack typically supports the following operations:

1. **Push**: Add an element to the top of the stack.
2. **Pop**: Remove and return the element from the top of the stack.
3. **Peek (or Top)**: Get the element at the top of the stack without removing it.
4. **isEmpty**: Check if the stack is empty.
5. **Size**: Get the number of elements currently in the stack.
6. **Clear**: Remove all elements from the stack, making it empty.

### Time complexity of the implemented functions

<img align="right" width=550 alt="Stack picture" src="https://media.geeksforgeeks.org/wp-content/cdn-uploads/20221219100314/stack.drawio2.png">

| Function                    | Time Complexity              |
|-----------------------------|------------------------------|
| `stack_create`              | O(1)                         |
| `stack_push`                | O(1)                         |
| `stack_pop`                 | O(1)                         |
| `stack_size`                | O(1)                         |
| `stack_top`                 | O(1)                         |
| `stack_copy`                | O(n)                         |
| `stack_print`               | O(n)                         |
| `stack_n_th_item`           | O(n)                         |
| `stack_destroy`             | O(n)                         |


## Implementation

The stack can be implemented using various data structures, such as arrays or linked lists. Each implementation has its advantages and disadvantages.

### Array-based Stack

In the array-based implementation, a fixed-size array is used to store the elements. When the stack is full, it cannot accept any more elements until some elements are removed. This implementation has constant time complexity for push and pop operations, but it may require resizing the array when the capacity is exceeded.

### Linked List-based Stack

In the linked list-based implementation, a singly linked list is used to store the elements. This implementation allows dynamic resizing and can grow or shrink as needed. However, it requires additional memory for storing the pointers, which may add overhead.


