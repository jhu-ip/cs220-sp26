---
id: day07_questions
layout: default
title: Day 7 Recap Questions
reference solutions:
  1. sizeof(array_name) / sizeof(int) - this will only work for statically allocated arrays declared in the same scope as the sizeof invocation.
  2. no - sizeof(array_name) vs. strlen(array_name)
  3. declaration is the function header only; definition is header + body
  4. no, C does not support this (unlike Java and C++)
  5. array contents are passed by reference; array parameter type is int[]
  6. const ar[]
  7. [NEW] 2 4 6 8 10 
  8. tricky to conceive; might use extra space
  9. function will call itself forever until the program crashes
  10. [NEW] 
     `Base case`:` if n == 0, return 0.
     `Recursive case`:` return n % 10 + sum_of_digits(n / 10)`
---

1. How do you get the number of elements of an integer array?
2. Is the size of a string array the same as the string length?	
3. What is the difference between a function declaration and a function definition?
4. Can you have two functions with the same function name in a program?
5. How does passing an integer array to a function differ from passing a single integer variable into a function?
6. How can you make an array that is passed into a function not modifiable?
7. What is the output of the following code segment:
```c
#include <stdio.h>
void func(int arr[], int size) {
    for (int i = 0; i < size; i++) 
        arr[i] = arr[i] * 2;
}
int main() {
    int numbers[5] = {1, 2, 3, 4, 5};
    func(numbers, 5);
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    return 0;
}
```

8. What is the down-side to recursion?
9. What happens if your recursive function does not have a base case?
10. Write both the base case and the recursive case for the function `int sum_of_digits(int n)` that returns the sum of the digits of n (n>=0).