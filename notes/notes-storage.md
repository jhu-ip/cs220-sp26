---
id: notes-storage
layout: default
title: Storage Classes & gdb
---

There are many different types of variable storage classes and memory usages in C and C++. Here is an overview, along with basic usage of gdb for debugging our programs.

<h3>Using gdb for debugging</h3> 

See the posted tutorials and cheat sheet. Here are some basics:
<ol>
  <li>Compile using <code>-g</code> to add debug info:
<code>gcc -g -o program_name my_c_code.c</code>
</li>  <li>Running: <code>gdb program_name</code>
</li>  <li>You are now in GDB with prompt <code>(gdb)</code>; type <code>break main:1</code> to set a breakpoint at line 1 of <code>main()</code>
</li>  <li>Type <code>run</code> to run the program
</li>  <li>Now, typing <code>next</code> (or just <code>n</code>) will run
  through a line of code if you set a breakpoint, skipping over
  function calls
</li><li>Similarly, typing <code>step</code> (or just <code>s</code>) will
  execute statement by statement, including into function calls
</li><li>Also, if you type just a return/enter key, gdb will repeat the
  previous command, letting you step through statements quickly
</li>  <li>Typing <code>print i+1</code> will print value of <code>int</code> variable <code>i</code>, plus one
</li></ol>

<h3>Storage classes/variable types </h3>

Recall that <em>lifetime</em> and <em>scope</em> of a variable are not always the same. Lifetime is how long the variable stays alive (persists in memory) at runtime. Scope is what parts of code can see the definition and access the variable.

Different types of storage classes:
<ul>
<li> Local variables: local to a block or function - scope and lifetime are only during execution of that block
</li><li> Global (external) variables: at the top of the program, scope and lifetime are throughout the program file
</li><li><code>static</code> variables essentially have local scope but global lifetime - more below
</li></ul>

<h4>Static variables</h4>
The <code>static</code> qualifier can be used with any type of variable declaration, e.g.
            <code>static int  intarray[10];</code>
<ul>            
<li> It is a <em>storage class</em> -- how the data is stored
</li><li> Its like a <code>private static</code> field in Java
</li>      <li> <code>intarray</code> location exists for duration of
            program<br>
-- but, <code>intarray</code> can only be accessed where it is in scope:
</li><li> Contents of variable persist in memory even when not in local use
</li><li> Static variables are automatically initialized to 0 by compiler
 (not reinitialized each time function w/var declared in it starts)
</li></ul>

The program below provides examples of several storage types, and also what
  happens when a local variable and a global variable have the same name.

```c
#include <stdio.h>

// a global variable
int v = 100;

// void f();
void f1(void);
void f2(int);

int main(void) {
    // f(3, 5); compiles if the forward declaration were f()
    f1();

    f2(10);

    printf("global v hasn't changed\n");
    printf(" val: %d\n", v);          // we can access the global here
    printf(" loc: %p\n", (void*)&v);  // where global v lives
    printf("size: %lu\n", sizeof(v)); // v has a size (in bytes)
    printf("\n");

    return 0;

}

void f2(int a) {
    printf("a: %d\n", a);
    f1();
}

void f1(void) {
    static int i;  // only created & initialized once, first time function is called
    printf("static i: %d\n", ++i);    // static variable has longer life

    printf("access global v\n");
    printf(" val: %d\n", v);          // we can access the global here
    printf(" loc: %p\n", (void*)&v);  // where global v lives
    printf("size: %lu\n", sizeof(v)); // v has a size (in bytes)
    printf("\n");
 
    // declare a variable in a different scope but with the same name
    double v = 45.0;
    printf("local v 'shadows' global v\n");
    printf(" val: %f\n", v);          // local v "shadows" global v
    printf(" loc: %p\n", (void*)&v);  // local v has its own address
    printf("size: %lu\n", sizeof(v)); // and size
    printf("\n");
}
```

<h4><code>const</code></h4>
<p>
Indicates data is <code>const</code>ant, the value cannot change after initialization.
<ul>
  <li> Added to ANSI C (not originally part of C)
</li>  <li> Important to use to mark immutable data
</li>  <li> <code>const</code> type qualifier can be applied to any variable declaration, e.g. <code>const int i</code>
</li>  <li> Question "Should this variable ever be modified" answers No?  <strong>add <code>const</code></strong> to its declaration
</li>  <li> Generally must be initialized when declared (with <code>=</code>, or its a function parameter)
</li></ul>

<code>const</code> can be used at different points in more complex types, with different meanings
<ul>
  <li> To make a <code>const</code> (non-modifiable) pointer: "<code>int * const iptr = &i"</code>
 </li><li> Local array variable declarations act like <code>const</code> pointers; the memory addresses of the array storage cannot be changed
</li>  <li> To make a (mutable) pointer <em>to</em> <code>const</code> (non-modifiable) data: "<code>const int * iptr"</code>
</li>  <li> Lastly, <code>const</code> ptr to <code>const</code> data:<code> const int * const iptr</code>
</li>  <li>Read declarations from right to left (inside out) to get it straight
</li></ul>


<h4>Memory segments</h4>

During execution our program variables are stored in different sections of memory, depending on their declaration type.

<ul>
<li>The <em>stack</em> holds local function variables -- called <em>automatic</em> memory in C. These are freed upon function return - don't try to return an array declared in a function. <code>auto int x;</code> in a function is same as <code>int x;</code> - default is <code>auto</code>.
	</li>
<li>The <em>data segment</em> holds global variables (declared outside any function) and static variables.
</li>    <li> The <em>heap</em> holds variables that are dynamically allocated at runtimewith an unbounded lifetime. The programmer explicitly allocates and deallocates this memory - see <a href='notes-pointers'>Notes: Pointers and Dynamic Memory Allocation</a>.
</li>	<li> Registers are specific positions in memory. The programmer can declare <code>register int x;</code> to suggest <code>x</code> be stored in a register.
</li></ul>
