# Red-Black Tree

The [Red-Black Tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree) is a self-balancing binary search tree that maintains balance during insertion and deletion operations. It guarantees that the height of the tree remains logarithmic, ensuring efficient search, insertion, and deletion operations with a time complexity of O(log n).


## Features

- Self-balancing: The Red-Black Tree ensures that the tree remains balanced after each insertion or deletion operation, which prevents it from becoming skewed and maintains the logarithmic height.
- Logarithmic Height: The height of the Red-Black Tree is guaranteed to be logarithmic, resulting in efficient operations.
- Binary Search Tree Property: The Red-Black Tree follows the binary search tree property, where each node has at most two children, and for each node, all nodes in its left subtree have keys less than the node's key, and all nodes in its right subtree have keys greater than the node's key.
- Faster Insertion and Deletion: The self-balancing property of the Red-Black Tree ensures that the height of the tree remains logarithmic, leading to faster insertion and deletion operations compared to unbalanced binary search trees.


## Properties of Red-Black Tree

1. Each node is colored either red or black.
2. The root node is always black.
3. All leaves (NULL nodes) are considered black.
4. Every red node has only black children.
5. All paths from a node to its descendant leaves contain an equal number of black nodes, which ensures that the tree remains balanced.

### Time complexity of the implemented functions

<img align="right" width=480 alt="Red-Black Tree picture" src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/41/Red-black_tree_example_with_NIL.svg/316px-Red-black_tree_example_with_NIL.svg.png">

| Function                     | Time Complexity   |
|------------------------------|-------------------|
| `RBT_insert`                 | O(log n)          |
| `RBT_delete`                 | O(log n)          |
| `RBT_search`                 | O(log n)          |
| `RBT_select_k_th_item`       | O(log n)          |
| `RBT_empty`                  | O(1)              |
| `RBT_count_items`            | O(n)              |
| `RBT_inorder_traversal`      | O(n)              |
| `RBT_preorder_traversal`     | O(n)              |
| `RBT_postorder_traversal`    | O(n)              |
| `RBT_min_value`              | O(log n)          |
| `RBT_max_value`              | O(log n)          |
| `RBT_destroy`                | O(n)              |
