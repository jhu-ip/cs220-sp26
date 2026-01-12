---
id: day28_questions
layout: default
title: Day 28 Recap Questions
reference solutions:
  1. A constructor that takes arguments
  2. No
  3. A pointer to the current object instance; when a local variable hides an instance variable
  4. [NEW] Non-default constructor called for ID 10, Default constructor called, Non-default constructor called for ID 20
  5. A method called by C++ when an object's lifetime ends or it is otherwise deallocated
  6. False, the destructor code must do that explicitly
---

1. What is a non-default (or "alternative") constructor?

2. If we define a non-default constructor, will C++ generate an implicitly defined default constructor?

3. What is `this` and when do we use the `this` keyword?

4. Trace the output of the following code and explain which constructors are called at each step and why?

	```c++
	#include <iostream>
	
	class Student {
	public:
	    Student() {
	        std::cout << "Default constructor called" << std::endl;
	    }
	    Student(int id) {
	        std::cout << "Non-default constructor called for ID " << id << std::endl;
	    }
	};
	
	int main() {
	    Student s1(10);
	    Student* s2 = new Student;
	    Student* s3 = new Student(20);
	    delete s2;
	    delete s3;
	    return 0;
	}
	```

5. What is a destructor?

6. A destructor will automatically release memories that are allocated in the constructor- true or false?
