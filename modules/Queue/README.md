# Queue

The [Queue](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)) is a linear data structure that follows the First-In-First-Out (FIFO) principle, meaning that the element that is added first is the one that is removed first. It can be visualized as a real-life queue of people waiting in line. The Queue of the present folder is implemmented using a linked list.


## Features

- **Generic**: The Queue is implemented as a generic data structure using void pointers, allowing you to store elements of any data type.
- **Basic Operations**: The Queue supports fundamental operations like enqueue (adding an element to the back), dequeue (removing an element from the front), checking if it is empty, obtaining the size, and peeking (viewing the front element without removing it).
- **Dynamic Size**: The Queue can dynamically grow and shrink as elements are added and removed, making it flexible to handle varying amounts of data.
- **Efficiency**: The enqueue and dequeue operations have a time complexity of O(1) on average, providing efficient insertion and removal of elements.

### Time complexity of the implemented functions

<img align="right" width=420 alt="Queue picture" src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/52/Data_Queue.svg/1200px-Data_Queue.svg.png">

| Function       | Time Complexity |
|----------------|-----------------|
| Queue_create   | O(1)            |
| Queue_size     | O(1)            |
| Queue_empty    | O(1)            |
| Queue_insert   | O(1)            |
| Queue_remove   | O(1)            |
| Queue_print    | O(n)            |
| Queue_destroy  | O(n)            |
