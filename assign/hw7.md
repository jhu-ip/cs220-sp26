---
id: hw7
layout: default
title: Homework 7
---

<div class='admonition success'>
<div class='title'>Caution</div>
<div class='content'>
<ul>
<li>You are expected to work individually.</li>
<li>Due: <strong>Friday November 14th at 11pm (Baltimore time).</strong></li>
<li>This assignment is graded out of 70 points.</li>
</ul>
</div>
</div>

## Learning Objectives

<div class='admonition success'>
<div class='title'>Learning Objectives</div>
<div class='content'>
<ul>
<li>operator overloading</li>
<li>C++ templates </li>
<li>linked structures</li>
<li>dynamic memory</li> 
<li>rule of three</li> 
<li>recursion. </li>
</ul>
</div>
</div>


<div class='admonition success'>
<div class='title'>Starter Files</div>
<div class='content'>
<p>
This homework comes with five starter source files: CTree.h, CTree.cpp, Tree.inc, CTreeTest.cpp, and TTreeTest.cpp. You should get these files from the public repository under homework/hw7. Make sure you have a copy of these files before you start writing any code. 
</p>
</div>
</div>

### Part 1: CTree

Complete the code for a class called `CTree` that implements an ordered tree of characters. A tree is a data structure that begins with a *root* node containing data (a character in this case), and then links to zero or more *children* nodes. Each child node in turn contains data and may have its own children. We refer to all the children of a particular node as *siblings* of each other. Other family terminology such as *parent* node, *descendents*, *ancestors*, etc. apply in the expected ways.

In an ordered tree, siblings are always sorted according to some criterion (ASCII ordering in this case.) Our tree will also be special because the children of any particular node must contain unique data; i.e., there are no repeated elements among siblings. Your class must be declared and implemented in files `CTree.h` and `CTree.cpp`, respectively. We give you a complete `CTree.h`. We also give you starter `CTree.cpp` and `Tree.inc` which contain an implementation of the `toString()` method (discussed later.)

Visually, we may think of a character tree in a top-down fashion as depicted here. In this case 'a' is the root node of the entire tree, but each node is the root of the subtree below it. As such, trees are naturally recursive data structures. Note that the topmost root node in a tree should not have siblings.
 
```plain
           a
    /      |       \
  b        p         t
 /     /   |   \   /   \
l     a    p    t  e    o
|     |    |            |
e     r    l            m
      |    | 
      t    e
```

Your CTree class has private data to store a character and its children information. Really we will treat each node of the tree as a (sub)tree itself. That way we only need one class instead of separate node and tree classes, and will be able to use recursion for much of the work. However, the implementation picture is somewhat more complicated since we don't know how many children any given node in the tree will have. Therefore, we will basically use a linked list to keep track of the children of a node, transforming the picture above into the following:

```plain
    a
    | 
    b   -   p         -         t
    |       |                   | 
    l       a   -  p  -  t      e   -    o
    |       |      |                     |
    e       r      l                     m
            |      |
            t      e
```

This is known as a [left-child right-sibling representation](https://en.wikipedia.org/wiki/Left-child_right-sibling_binary_tree). Each node keeps a link to its first child, which then links across to the next sibling in the chain, and also down to its own first child, if it has one. The last node in a chain holds a `nullptr`.  Each node should also keep a link to its preceding node: that is, the parent if the node is a first child, or its left sibling if the node is not a first child. We are giving you the header file for this class in order to help with setting up the recursive structure properly.

Minimally, here are the functions that your CTree must have, keeping in mind that at all times the siblings of any node must be ordered and unique. You are welcome to create helper functions and variations as well. You should only use the assignment `=`, equals `==`, less than `<` and output `<<` operators on chars to implement these functions. 

* A constructor that is passed the character to store in the root node of a new tree.

* A copy constructor. (Hint: first implement the `createDuplicateTree` friend method and use it when implementing the copy constructor.)

* A destructor that clears all the children of the current node and all the siblings to the right of the current node, freeing that dynamically allocated memory. (Hint: use recursion!)

* An `addChild` function, which is passed the character data to be stored in the child. This function returns false if it fails (which could happen because the data is already a child of this tree node) and true if it succeeds. Remember that the class must keep the children ordered.

* An (overloaded) `addChild` function, which is passed the root of an existing tree to be stored as a child of this node. This function returns false if the root is invalid (has prev or siblings), or if the data in the root node is already a child of the tree node. Otherwise it adds the node in order and returns true. Note that this function will not make a copy of the tree argument, but rather attach it directly. This is important to keep in mind when freeing memory.

* Two private `addSibling` functions. One is passed a character to be stored in a new node, and the other is passed the root of an existing tree. Each of these functions returns false if it fails (because the data is already a sibling to the right of this tree node, or the root node is invalid) and true if it succeeds. The note regarging the subtree being attached directly and not copied applies here, too.

<div class='admonition caution'>
<div class='title'>Caution</div>
<div class='content'>
Remember that siblings must always be ordered. 
<ul>

<li><strong>Hint:</strong> the character version can simply create the node, call the other version and then return the resulting value.</li>

<li><strong>Note:</strong> these functions can be useful in implementing the public add functions.</li>
</ul>
</div>
</div>

* A `toString()` function, which we give you already implemented in the startetr code. This function creates and returns a string of all the elements in the nodes of the tree in pre-order traversal separated by newline characters (see below.)

* An overloaded `=` (assignment) operator which creates copies of the right-hand side's children and siblings onto the left-hand side. (Hint: use the `createDuplicateTree` method here, too.)

* An overloaded `+=` operator that does the same thing as `addChild`. The difference is that instead of returning a boolean, it returns the resulting CTree. You should not change the function signature of `operator+=` function, but you should make a call to the `addChild` function when implementing it.

* An overloaded `==` operator that checks if two CTrees are equal. Two CTrees are considered equal if they match node by node (i.e. if their structure and node values are identical) when comparing from the given nodes downward and to the right. Elements to the left or above the given nodes are not compared. You should not change the signature of the `operator==` function in the header file. (Hint: first implement the friend `treeCompare` function and then use it in implementing this operator.)

* An overloaded `<<` operator that inserts the value returned by `toString` to the output stream. In fact, when implementing this, you should make a call to the `toString()` function of the parameter object. Also, note this function is not a member of the CTree class. You need to implement this as a separate function in your cpp file. Note that it is not declared as a friend in `CTree.h` since it will not make use of private members of the CTree class.

<div class='admonition success'>
<div class='title'>Tip</div>
<div class='content'>
<p>
The CTreeTest.cpp has examples of how these operators are to be used. Look for the relevant test functions.
</p>
</div>
</div>

We recommend that you implement the friend helper functions declared in the provided `CTree.h`: `treeCompare` and `createDuplicateTree` to facilitate the implementation of the `==` operator, copy constructor, and `=` operator as mentioned in the hints corresponding to those items above. You should also add tests for these functions to the relevant test file, though you will not be graded on this aspect. If you choose not to implement these friend functions because you've taken a different approach to implementing the associated operations, you may remove their declarations from the starter code.

#### Tree traversal

The provided `toString()` implementations do a pre-order traversal of the tree. This means that as they move through the tree, the first node visited is the root, then they go through that node's children (recursively depth-first), and finally its siblings. A simple (non-object-oriented) recursive depth-first traversal starting at some parameter node would look as follows. You may want to use this as inspiration when thinking about the other recursive algorithms you need to implement.

```text
DFtraverse(node) {
    process data at node
    if node has children, 
       do a depth-first traversal from its first child
    if node has siblings (to the right), 
       do a depth-first traversal from its next sibling
}
```

#### Testing

You are given a file named `CTreeTest.cpp` that tests your CTree implementation. Once you are done implementing `CTree.cpp`, you should compile and run `cTreeTest` to make sure that all test cases pass. You are encoraged to add more tests to check your implementation, though there are no homework points associated with doing so.

### Part 2: Templated Tree

For the second and final part of the assignment you will generalize the CTree from Part 1 to create a templated ordered tree with unique siblings. Note that you will write your own header file for this part. Your tree class must be called Tree and be declared in `Tree.h`. The implementation of functions longer than one line should occur outside of the class. You may place them in `Tree.inc` and then `#include` this file in `Tree.h` after the class declaration. If your programming environment is giving you issues with using `.inc` files, you may alternatively place your implementation in the `.h` file after the class declaration.

<div class='admonition caution'>
<div class='title'>Caution</div>
<div class='content'>
<p>
Remember to keep data private, and use const protection whenever you can.</p>
</div>
</div>

Your Tree class must contain the same public functions and overloaded operators as the CTree class, except that the parameters for the data stored in each node will now be of some generic type instead of char.

Because the templated tree will need to keep siblings in order and unique, each base type is assumed to have the equals `==` operator and the less than `<` operator defined on them in addition to the `<<` operator invoked in the provided `toString()` method in `Tree.inc`. These operators and assignment `=` are the only operators your templated Tree implementation may use. If your implementation in `CTree.cpp` uses other operators, you will need to rewrite those functions when porting them for the templated tree. 

#### Testing

As in Part 1, you are given a file named `TTreeTest.cpp` that tests your implementation (for the templated version). Once you are done implementing `Tree.h` and `Tree.inc`, you should make and run `tTreeTest` to make sure that all test cases pass. 

Note that the CTree class declares the CTreeTest class as a friend. This means that all member functions of CTreeTest have access to CTree's private members. Similarly, your templated tree class should declare the TTreeTest class as a friend so its tests can be run.

### Makefile & Compiling

Create and submit a Makefile with two rules (aside from the `clean` rule): 
1. a rule that creates a target executable called `cTreeTest` for the first part of this homework (the `char` version.)
2. a rule that creates a target executable called `tTreeTest` for the second part of this homework (the templated version.) 

These two targets should compile with no errors or warnings using `g++` with our typical flags: `-Wall -Wextra -std=c++11 -pedantic`. 

<div class='admonition caution'>
<div class='title'>Caution</div>
<div class='content'>
<p>
Do not use any special libraries that require different or additional compiler options.</p>
</div>
</div>

<div class='admonition danger'>
<div class='title'>Danger</div>
<div class='content'>
<p>
The autograder does an automatic check to see if it can compile the two targets. Thus, it is very important that you make sure your submission successfully compiles, otherwise your final score for the entire homework assignment will be 0.</p>
</div>
</div>

### Git log and README

In the assignments folder of your private repository, create a new subfolder named `hw7`. Do your work in that subfolder and use `git add`, `git commit` and `git push` regularly. Use `git commit` and the associated commit message to document your work. e.g. if you just modified `CTree.cpp` to add a child functionality, you might do `git add CTree.cpp`; `git commit -m "addChild functions added!"`; `git push`.

Your submission includes a copy of the output of `git log` showing at least five commits to the repository. Save the git log output into a file called `gitlog.txt` i.e., by doing `git log > gitlog.txt`.

Also, please submit a file called `README` not `README.txt` or `README.md`, etc. -- just `README` including information about what extra helper functions you added (if any) and anything the graders should know about your submission. In the `README` you should:

<ul> 
<li>Write your name and JHED ID at the top of the file</li>
<li>Briefly justify the structure of your program; why you defined the functions you did, etc.</li>
</ul>

### Specific Requirements

* Do not eliminate anything from `CTree.h` file. You can add more private (helper) functions if you want, but your `CTree.cpp` file should at least provide an implementation for all the functions that are declared in `CTree.h` file. The only exception to this are the friend functions `treeCompare` and `createDuplicateTree` which, as discussed above, you may delete if you take a different approach.
* Your program should only use new and delete for dynamic memory allocation/deallocation. Do not make use of C functions such as `malloc`, `calloc`, `free`, etc. for that purpose.
* Other than the member variables (class attributes) already provided in the starter code, all variables must be declared inside functions. No variables should be global or extern.
* Do not use `auto`.
* Use header guards in all `.h` files.
* Do not use `using` in `.h` or `.inc` files.
* In `.cpp` files , you may import individual symbols using statements like `using std::string`. Do not use `using namespace ID`, either in headers or in source files.

### Other Hints and Suggestions

* Make use of `gdb` to debug.
* Run `valgrind` to make sure there is no memory leakage or invalid memory usage.
* The test files given to you are very minimal sample test files. There are no homework points directly associated with writing tests. However, to maximize your score on this assignment, you are encouraged to write additional tests so that your functions are tested thoroughly.

### Your submission to Gradescope

Create a `.zip` file named `hw7.zip` containing your source/header files, `Makefile`, `gitlog.txt`, and `README`. Do not include any `.txt` files  and never submit any executable or object files!

Copy the `hw7.zip` file to your local machine (using `scp` or `pscp`), and submit it to Gradescope. When you submit, Gradescope conducts a series of automatic tests. These do basic checks, e.g. to check that you submitted the right files. If you see error messages (in red), address them and resubmit. You may resubmit any number of times prior to the deadline; only your latest submission will be graded. Review the course syllabus for late submission policies (grace period and late days.)

<div class='admonition danger'>
<div class='title'>Danger</div>
<div class='content'>
<p>Remember that if your final submitted code does not compile, you will
earn a zero score for the assignment.</p>
</div>
</div>

<div class='admonition info'>
<div class='title'>Info</div>
<div class='content'>
<p>Two notes regarding automatic checks for programming assignments:</p>
<ul>
<li>Passing an automatic check is not, itself, worth points. (There might
be a nominal, low point value like 0.01 associated with a check, but
that won’t count in the end.) The checks exist to help you and the
graders find obvious errors.</li>
<li>The automatic checks cover some of the requirements set out in the
assignment, but not all. It is up to you to test your own work and ensure
your programs satisfy all stated requirements. Passing all the automatic
checks does not mean you have earned all the points.</li>
</ul>
</div>
</div>

### Coarse grading breakdown

* Submission and style: 10 points
* CTree implemetation: 40 points
* Templated Tree implementation: 20 points

