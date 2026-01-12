---
id: day24_questions
layout: default
title: Day 24 Recap Questions
reference solutions:
  1. A collection of unique keys, each with an associated value. `pair` is exactly two, `tuple` may be more.
  2. std::pair or std::tuple (or user-defined class type or struct)
  3. With a const_iterator, you are not allowed to change the contents.
  4. std::vector, std::map, std::pair, std::tuple, std::list
  5. std::sort, std::find, std::count
  6. [NEW] < (for comparisons), == (for find) [also = which is always defined, copy constructor and default constructor for class types]
  7. [NEW] Read values into a vector, sort the vector, create an empty vector, define an iterator to start at the front and a reverse iterator at the back, alternate pushing back into the new vector from each iterator, starting with the forward one. Use the size / 2 to control the iterations (or check that the next value != the most recently pushed one).
---

1. What is a `map` in C++ STL? What is the difference between `pair` and `tuple`?
2. How do you return multiple values in C++?
3. What's the difference between an `iterator` and a `const_iterator`?
4. Name some useful templated data containers provided by STL.
5. Name some useful algorithms provided by `<algorithm>`.
6. What operators must be defined on base types used with STL containers and algorithms?
7. Describe the approach you would take (using the STL) to arrange a collection of real numbers such that half the collection is in increasing order, half is ordered decreasing, and they are interleaved, for example: 1.1, 9.9, 2.2, 8.8, 3.3, 7.7, 4.4, 6.6, 5.5.