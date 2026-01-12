---
id: day33_questions
layout: default
title: Day 33 Recap Questions
reference solutions:
  1. when a pointer/reference to a base class is used to point to/reference a derived object, the compiler “squints” and only looks at the base’s subset of the information, effectively "slicing" off the parts specific to the derived class
  2. [EDIT] a way to indicate that a function in a derived class is supposed to override one in a base class (the base class uses the `virtual` notation); we use it at the end of the function prototype in the derived class
  3. when a function in a derived class has the same name but different parameters than one in its base class, the one in the base class is hidden
  4. include a pure virtual function (prototype = 0, no implementation provided), or do not provide a public constructor
  5. No, but you can declare a pointer (or reference) to an abstract class type that can be set to a concrete object of a derived class type
  6. [NEW] Any time it has virtual member functions, but especially if it (base class) has a non-trivial destructor. Otherwise the base destructor might not get called when a derived class object is destroyed. First derived, then base (opposite constructors).
---

1.	Explain what object slicing is in C++.
2.	What is the `override` specifier in C++ and where do we use it?
3.	Explain what function hiding is in C++.
4.	In C++, how do you make an abstract class?
5.	Can we create an object from an abstract class?
6.  When should a class have a `virtual` destructor? Why? What is the order of execution for the base and derived destructors when destroying a derived class object? 
