---
id: day26_questions
layout: default
title: Day 26 Recap Questions
reference solutions:
  1. An alias for an existing variable
  2. To have output parameters in functions (instead of having to use pointers.) Also when you want to pass a structure to a function without incurring the cost of a copy.
  3. Reference variable can't be NULL, must be initialized immediately, can't be changed
  4. [NEW] 16 16 16
  5. new or new[] and delete or delete[]
  6. [NEW]  should be `delete[]` not `delete`
---

1. What is a C++ reference?

2. When should you use C++ references?

3. What is the difference between a pointer and a reference?

4. What is the output of the following?

	```c
	#include <iostream>
	
	void modify(int& a, int& b) {
	    a = a + b;
	    b = a * 2;
	}
	
	int main() {
	    int x = 3, y = 5;
	    int& ref = x;   
	
	    modify(ref, y); 
	    ref = y;        
	
	    std::cout << x << " " << y << " " << ref << std::endl;
	    return 0;
	}
	```

5. How do you dynamically allocate and deallocate memory in C++?
6. What is wrong with the following code?

	```c
	#include <iostream>
	
	using std::cout;
	using std::endl;
	
	int main() {
	  double *d_array = new double[5];
	  for(int i = 0; i < 5; i++) {
	    d_array[i] = i;
	  }
	
	  delete d_array;
	  return 0;
	}
	```
