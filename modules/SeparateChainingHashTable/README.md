# Separate Chaining Hash Table

The [Separate Chaining](https://en.wikipedia.org/wiki/Coalesced_hashing) [Hash Table](https://en.wikipedia.org/wiki/Hash_table) is a data structure that provides fast key-value storage and retrieval. It uses a hash function to map keys to specific positions in an array, and each array element contains a linked list to handle collisions. This implementation resolves hash collisions through separate chaining, where multiple items with the same hash value are stored in the same slot as a linked list.


## Features

<img align="right" width=320 alt="Chaining Hash Table picture" src="https://www.eecs.umich.edu/courses/eecs380/ALG/niemann/s_fig31.gif">

- Efficient key-value storage and retrieval.
- Handles hash collisions using separate chaining with linked lists.
- Dynamic resizing to maintain a suitable load factor for optimal performance.
- Supports generic data types through void pointers.

### Time complexity of the implemented functions

| Function                      | Time Complexity (Average Case) | Time Complexity (Worst Case) |
| ----------------------------- | ------------------------------ | ---------------------------- |
| `SChashtable_create`          | O(1)                           | O(1)                         |
| `SChashtable_size`            | O(1)                           | O(1)                         |
| `SChashtable_resize`          | O(n)                           | O(n)                         |
| `SChashtable_insert`          | O(1)                           | O(n)                         |
| `SChashtable_search`          | O(1)                           | O(n)                         |
| `SChashtable_remove`          | O(1)                           | O(n)                         |
| `SChashtable_destroy`         | O(n)                           | O(n)                         |
| `SChashtable_print`           | O(n)                           | O(n)                         |