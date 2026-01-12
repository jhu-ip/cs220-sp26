---
id: day32_questions
layout: default
title: Day 32 Recap Questions
reference solutions:
  1. [EDIT] "Many forms" - blanket term for all types of ways that classes and functions have different versions that can be executed (inheritance, overloading, overriding, etc.).
  2. [EDIT] Constructors and an explicitly defined assignment operator.
  3. Only member functions of the class and member functions of derived class have access to the field/function.
  4. [NEW] Call the base class constructor as the first thing in the derived class initializer list.
  5. [NEW] When a call to a [overridden] member function will cause a different function to be executed depending on the run-time class of object that invokes the function. Must use `virtual` when declaring the function. [Without virtual, you can override but not get dynamic binding.]
  6. [NEW] base, child, base, child ; without 'virtual' in BaseClass we get base, child, base, base
  7. Yes
---
1.	What is polymorphism?
2.	What two types of functions are not inherited by a derived class?
3.	What does `protected` access imply for a class field or function?
4.  How do we initialize the private fields that are inherited from a Base class in a constructor of a Derived class?
5.	What is dynamic binding and how do we enable it?
6.  What is the output of the below code? What if we remove "virtual" from compute() in the BaseClass?

    ```cpp
    class BaseClass {
    public:
      virtual void compute() { std::cout << "base "; }
    };
    class ChildClass : public BaseClass {
    public:
      virtual void compute() { std::cout << "child "; }
    };

    int main() {
       BaseClass b;
       b.compute();
       ChildClass c;
       c.compute();
       BaseClass *p;
       p = &b;
       p->compute();
       p = &c;  // allowed because each ChildClass object "IS-A" BaseClass object
       p->compute();
    }
    ```
7.	Can a child class have multiple parents?
