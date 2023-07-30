# Bloom Filter

The [Bloom Filter](https://en.wikipedia.org/wiki/Bloom_filter) is a probabilistic data structure used to efficiently test the membership of an element in a set. It offers a space-efficient representation of a large set of items, with low false negatives (items that are in the set but are incorrectly reported as not present) and no false positives (items that are not in the set but are incorrectly reported as present). So, a Bloom Filter is particularly useful when you need to quickly check whether an element is likely to be a member of a set without requiring the actual elements to be stored. This property makes it valuable for cases where memory efficiency is crucial, such as in caching, spell checkers, and network routers.


## Features
- Space-efficient representation: The Bloom Filter uses a compact array of bits to represent the presence or absence of elements, making it memory-efficient compared to traditional data structures.
- Fast membership test: Bloom Filters perform membership tests in constant time (O(1)) regardless of the number of elements in the filter.
- Low false negatives: The probability of a false negative can be controlled by adjusting the size of the Bloom Filter and the number of hash functions used.
- No false positives: Bloom Filters guarantee no false positives for elements that have not been inserted into the filter.
- Generic implementation: The Bloom Filter is implemented using void pointers, allowing it to handle various data types.

### Time complexity of the implemented functions

<img align="right" width=420 alt="bloom filter picture" src="https://cdnd.selectdb.com/assets/images/Bloom_filter.svg-9ad88beea5ebb916ea2d0ac27eb5a5cf.png">

| Function                 | Time Complexity |
|--------------------------|-----------------|
| bloom_filter_create      | O(1)            |
| bloom_filter_set_bit     | O(1)            |
| bloom_filter_get_bit     | O(1)            |
| bloom_filter_insert      | O(k)            |
| bloom_filter_check       | O(k)            |
| bloom_filter_reset       | O(n)            |
| bloom_filter_destroy     | O(1)            |

Here, "k" represents the number of hash functions used in the Bloom filter, and "n" represents the size of the Bloom filter.