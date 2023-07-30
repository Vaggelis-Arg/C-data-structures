# Double Hashing Hash Table

The [Double Hashing](https://en.wikipedia.org/wiki/Double_hashing) [Hash Table](https://en.wikipedia.org/wiki/Hash_table) is a data structure that provides a key-value storage and retrieval mechanism. It uses two independent hash functions for collision resolution, which helps improve the efficiency of handling hash collisions and provides faster average lookup times. Designed to store key-value pairs, the Double Hashing Hash Table excels in delivering rapid and constant-time access to values based on their corresponding keys. This data structure leverages the strength of two independent hash functions, each responsible for computing unique probe sequences. As a result, it ensures a well-distributed distribution of elements, effectively reducing the occurrence of hash collisions and preserving exceptional efficiency, even in scenarios with high table occupancy.


## Features
- Efficient key-value storage and retrieval: The Double Hashing Hash Table boasts constant-time average case complexity for fundamental operations, such as insertion, deletion, and retrieval.
- Advanced collision resolution: By utilizing two distinct hash functions, this hash table elegantly resolves collisions, mitigating clustering issues commonly faced by other methods and maintaining superior performance across various scenarios.
- Dynamic resizing: The hash table automatically adjusts its size when required, optimizing memory utilization and preventing performance degradation due to increased load factors.
- Versatile implementation: Built with void pointers, the hash table adapts to a wide range of key-value data types, enhancing its versatility and applicability.

### Time complexity of the implemented functions

<img align="right" width=320 alt="Double Hashing Hash Table picture" src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/7d/Hash_table_3_1_1_0_1_0_0_SP.svg/1200px-Hash_table_3_1_1_0_1_0_0_SP.svg.png">

| Function                | Average Case Time Complexity | Worst Case Time Complexity |
|-------------------------|------------------------------|----------------------------|
| DHhashtable_create      | O(1)                         | O(1)                       |
| DHhashtable_size        | O(1)                         | O(1)                       |
| DHhashtable_resize      | O(n)                         | O(n)                       |
| DHhashtable_insert      | O(1)                         | O(n)                       |
| DHhashtable_search      | O(1)                         | O(n)                       |
| DHhashtable_remove      | O(1)                         | O(n)                       |
| DHhashtable_print       | O(n)                         | O(n)                       |
| DHhashtable_destroy     | O(n)                         | O(n)                       |