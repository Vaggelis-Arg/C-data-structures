# Priority Queue

The [Priority Queue](https://en.wikipedia.org/wiki/Priority_queue) with [Heap](https://en.wikipedia.org/wiki/Heap_(data_structure)) is a versatile data structure designed to efficiently manage elements with varying priorities. It guarantees prompt retrieval of the highest-priority element, making it ideal for applications where urgency is paramount. Employing a binary heap, this implementation optimizes priority queue operations, providing impressive average time complexities for dynamic data handling. In scenarios where elements demand order based on their priorities, the Priority Queue with Heap stands out as a reliable solution. By employing a binary heap, a balanced binary tree with efficient operations, this priority queue ensures that the most critical element is always readily accessible. The heap-based structure facilitates rapid insertion, removal, and retrieval of elements, providing an invaluable tool for real-time data management.


## Features
- Effective Priority Management: The Priority Queue guarantees swift access to the highest-priority element, enabling seamless handling of critical data.
- Optimal Time Complexities: Leveraging a binary heap, the implementation achieves outstanding average time complexities for common operations like insertion and deletion.
- Customizable Comparator: Tailor the Priority Queue to your specific data requirements by providing a custom comparator function.
- Generic and Flexible: The Priority Queue accepts elements of any data type, thanks to the use of void pointers, making it highly adaptable to various scenarios.


## Useful matrix

<img align="right" width=400 alt="Priority Queue picture" src="https://users.cecs.anu.edu.au/~Alistair.Rendell/Teaching/apac_comp3600/module2/images/Heaps_HeapStructure.png">

In the Priority Queue implemented with the heap the following are valid:
| To Find                 | Use:       | Provided:      |
|------------------------|------------|----------------|
| The left child of 𝐴[𝑖]  | 𝐴[2𝑖]      | 2𝑖 ≤ 𝑛          |
| The right child of 𝐴[𝑖] | 𝐴[2𝑖 + 1] | 2𝑖 + 1 ≤ 𝑛      |
| The parent of 𝐴[𝑖]      | 𝐴[𝑖/2]     | 𝑖 > 1           |
| The root                | 𝐴[1]       | A is nonempty   |
| Whether 𝐴[𝑖] is a leaf  | True       | 2𝑖 > n          |


### Time complexity of the implemented functions

| Function                | Time Complexity |
|-------------------------|-----------------|
| PQ_initialize           | O(1)            |
| PQ_empty                | O(1)            |
| PQ_size                 | O(1)            |
| PQ_insert               | O(log n)        |
| PQ_remove               | O(log n)        |
| PQ_print                | O(n)            |
| PQ_destroy              | O(n)            |
