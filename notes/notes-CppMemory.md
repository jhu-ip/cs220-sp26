---
id: notes-CppMemory
layout: default
title: Dynamic Memory in C++
---

See also <a href='notes-pointers.html'>Pointers</a> and Pass by Reference in <a href='notes-CppBasics.html'>C++ Basics</a>.

<h3>Dynamic Memory Management in C++</h3>

Declaring class objects on the stack works similarly to primitive types:
<ul>
    <li>Declare as <code>MyClass c;</code>      
</li>     <li> Implicitly calls the default constructor of <code>MyClass</code>
</li>      <li> Object is allocated on the stack
</li>      <li> Explicit freeing not required, object deallocated when block in which it is declared ends
</li>	</ul> 

Dynamic allocation and deallocation of variables on the heap requires the use of keywords <code>new</code> and <code>delete</code>:

```cpp
int * ip = new int;            // allocate memory for integer
MyClass * c = new MyClass();   // allocate object and return pointer to address
delete c;                      // free the heap memory for the object
delete ip;                     // free the heap memory for the integer
```

<ul>
  <li>C++ replaces low-level C functions <code>malloc/free</code> with built-in C++ syntax using keywords <code>new/delete</code>
</li>	  <li> This example explicitly calls a default constructor (the <code>()</code> are optional) to create an object with <code>new</code>, but other constructors could be called instead if defined for the class type
</li>	  <li> <code>delete</code> is C++'s analogue to C's <code>free</code> - it deallocates heap memory
</li></ul>


<h4>Dynamic arrays</h4>

We also use <code>new/delete</code> to manage heap memory for arrays in C++. Arrays of primitive type elements are fairly straightforward. Elements in a dynamically allocated array of primitive type are not initialized by default (similar to <code>malloc</code>).

```c
  int *iray = new int[n];         // makes array of n ints on heap
  // ...
  delete [] iray;                 // frees memory of array, note use of [ ] in statement!
```

Arrays of objects are initialized automatically using (necessary) default constructors: <code>MyClass * array = new MyClass[6];</code>

<ul>
	<li> Makes 6 different MyClass objects, sequentially stored in array, calls default constructor to initialize each one
</li>	<li> This will ONLY call the default constructor on each
</li>	<li> If want to call alternate constructor, we need to do separately afterwards as in the below example
</li>  <li> Alternate constructor call creates a temporary MyClass object and copies it into array through assignment operator
</li>  <li> Note the lack of <code>new</code> here - <code>MyClass(7, 'd')</code> object is stack allocated (not a pointer to a MyClass object)
</li></ul>
	    
```cpp
MyClass * array = new MyClass[6];
for (int i=0; i < 6; i++)
    array[i] = MyClass(7, 'd'); // fresh object made, overwrites new objects above

delete [] array;    // remember to delete with [] for any array on the heap
```

