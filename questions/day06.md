---
id: day06_questions
layout: default
title: Day 6 Recap Questions
reference solutions:
  1. yes, stdout is the name for the default output
  2. when checking a condition that must be true to proceed
  3. int to double is fine, it will get promoted. double to int is compiler warning(?) and should be avoided or explicitly typecast first.
  4. values from primitive type function call arguments are copied into the parameter variables when the call is executed
  [NEW] 5. Inside update_values`:` x = 15, y = 14 
     After function calls`:` m = 5, n = 7 
     Result = 12
  6. add `(int argc, char* argv[])` parameters for the count of arguments and the strings themselves
  7. [NEW] See day06.c
  
  
---

1.	Is `fprintf(stdout, "xxx")` the same as `printf("xxx")`?
2.	When should we use assertions instead of an *if* statement?
3.	What will happen if you pass an `int` variable to a function that takes a `double` as its parameter?  What will happen if a `double` is passed to an `int` parameter?
4.	What is "pass by value"?
5. What is the output of the following code:
```c
#include <stdio.h>
void update_values(int x, int y) {
    x = x + 10;
    y = y * 2;
    printf("Inside update_values: x = %d, y = %d\n", x, y);
}
int compute_sum(int a, int b) {
    update_values(a, b);
    return a + b;
}
int main() {
    int m = 5, n = 7;
    int result = compute_sum(m, n);
    printf("After function calls: m = %d, n = %d\n", m, n);
    printf("Result = %d\n", result);
    return 0;
}
```
6.	How do you change the *main* function so that it can accept command-line arguments? 
7. Write a short C program that takes two integers from the command line and prints their sum, difference, and product.