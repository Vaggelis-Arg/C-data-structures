# Skip List

[Skip List](https://en.wikipedia.org/wiki/Skip_list) is a data structure that provides an efficient alternative to balanced binary search trees for maintaining a sorted list of elements. It is a probabilistic data structure that uses multiple linked lists with different skip probabilities to achieve logarithmic average time complexity for search, insertion, and deletion operations.


## Features
- Efficient search, insertion, and deletion in average logarithmic time complexity (O(log n)).
- Simple and easy to implement compared to balanced binary search trees.
- No need for rotations and rebalancing during insertions and deletions, making it easier to maintain.
- Scalable and adaptable for use cases where dynamic resizing is needed.

### Time complexity of the implemented functions

<img align="right" width=480 alt="Skip List picture" src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/86/Skip_list.svg/800px-Skip_list.svg.png">

| Function                       | Time Complexity   |
|--------------------------------|-------------------|
| `skiplist_initialize`          | O(1)              |
| `skiplist_get_size`            | O(1)              |
| `link_get_value`               | O(1)              |
| `skiplist_insert`              | O(log n)          |
| `skiplist_search`              | O(log n)          |
| `skiplist_delete`              | O(log n)          |
| `skiplist_print`               | O(n)              |
| `skiplist_merge`               | O(n log n)        |
| `skiplist_destroy`             | O(n)              |



## Implementation Details
The Skip List is composed of multiple levels, with each level representing a separate linked list. The bottom level is a standard linked list containing all the elements in sorted order. Higher levels consist of a subset of the elements from the lower level, forming shortcuts or "skips" between nodes.

Each node in a level contains a forward pointer that connects to the next node in the same level. Additionally, it may have an additional forward pointer that connects to a node in the next higher level. The higher-level nodes are skipped with a certain probability, effectively reducing the search space and improving the average time complexity.

The Skip List maintains a tower of linked lists, with the bottom level having all the elements and the top level containing just one element, which is the largest element in the list. The top-level elements act as sentinels that prevent unnecessary boundary checks.

## Limitations
- Skip List requires additional memory compared to simple linked lists.
- While Skip List provides efficient average-case time complexity, its worst-case time complexity for search, insert, and delete operations is O(n).
- Skip List is not well-suited for applications where strict determinism and worst-case performance guarantees are required.

## Readings
The following paper should be very useful: https://drum.lib.umd.edu/handle/1903/544