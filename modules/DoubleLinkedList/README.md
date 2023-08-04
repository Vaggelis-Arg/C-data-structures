# Double Linked List

A [double linked list](https://en.wikipedia.org/wiki/Doubly_linked_list) is a data structure that consists of a sequence of elements, where each element points to the next and the previous element in the sequence. This data structure allows efficient insertion and deletion of elements at both the beginning and the end of the list.


## Features

- Supports insertion and deletion of elements at both the beginning and the end of the list.
- Provides functions to access the first and last elements of the list.
- Allows iteration over the elements in the list using forward and backward pointers.
- Provides a function to check if the list is empty.

### Time complexity of the implemented functions

<img align="right" width=400 alt="Priority Queue picture" src="https://i.stack.imgur.com/UIhLj.png">

| Function             | Time Complexity      |
|----------------------|----------------------|
| DLL_Create           | O(1)                 |
| DLL_Size             | O(n)                 |
| DLL_IsEmpty          | O(1)                 |
| DLL_GetFirst         | O(1)                 |
| DLL_GetLast          | O(1)                 |
| DLL_GetNode          | O(n)                 |
| DLL_GetData          | O(1)                 |
| DLL_GetPrev          | O(1)                 |
| DLL_GetNext          | O(1)                 |
| DLL_AddBefore        | O(1)                 |
| DLL_AddAfter         | O(1)                 |
| DLL_AddFirst         | O(1)                 |
| DLL_AddLast          | O(1)                 |
| DLL_Remove           | O(n)                 |
| DLL_print            | O(n)                 |
| DLL_freelist         | O(n)                 |
