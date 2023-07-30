# Vector

A [Vector](https://en.wikipedia.org/wiki/Vector) is a dynamic array that allows you to store and manage a collection of elements in a contiguous block of memory. It automatically resizes when the number of elements exceeds its capacity. This implementation provides a set of operations for managing the Vector efficiently.

## Features
- Efficient insertion and deletion at the end (amortized O(1) time complexity)
- Constant-time access to elements by index (O(1))
- Dynamic resizing when the Vector is full (O(n))
- Supports element insertion and deletion at any position (O(n))
- Automatic memory management for added convenience
- Generic implementation using only macros

### Time complexity of the implemented functions

| Function                           | Time Complexity                                 |
|------------------------------------|-------------------------------------------------|
| vector_TYPE_create                 | O(1)                                            |
| vector_TYPE_free                   | O(n)                                            |
| vector_TYPE_at                     | O(1)                                            |
| vector_TYPE_set_at                 | O(1)                                            |
| vector_TYPE_push_back              | O(1) (when Vector needs resize it's O(n))       |
| vector_TYPE_clear_at               | O(n)                                            |
| vector_TYPE_delete                 | O(n)                                            |
| vector_TYPE_sort                   | O(n log n)                                      |
| vector_TYPE_size                   | O(1)                                            |
| vector_TYPE_capacity               | O(1)                                            |
| vector_TYPE_search                 | O(n)                                            |
