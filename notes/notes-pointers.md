---
id: notes-pointers
layout: default
title: Pointers & Dynamic Memory Allocation
---

Pointers in C and C++ give us direct access to memory locations. One of the most common usages is to provide a pass by reference mechanism for function parameters. They are also used with dynamic memory allocation which enables creating memory spaces as needed during program execution. Freeing the memory explicitly when done using it is also the programmer's job in these languages.

Also see the <a href='notes-Carrays.html'>Arrays</a> and <a href='notes-Cstrings.html'>Strings</a> notes for material related to pointers and those structures.

<h3>Pointers</h3>

These are variables that hold memory addresses, providing indirect access to the referenced location.

<ul>
	  <li> Declaration: <code><em>sometype</em> *<em>ptrvarname</em></code>, e.g. <code>int *toi</code> or <code>char *args[]</code>
</li>  <li> <code><em>ptrvarname</em></code> is a variable that contains a memory <em>address</em>, a number which refers to that raw memory location
</li>  <li> That memory address in turn should contain a value of type <code><em>sometype</em></code>
</li>  <li> <code>NULL</code> means "points at nothing" (<code>#include &lt;stdlib.h&gt;</code> to get <code>NULL</code> defined; it is in fact <code>0</code>).
</li></ul>

<h4>Operators for pointers</h4>

We use two operators in conjunction with pointers. The <code>&</code> operator when applied to a variable returns that variable. This enables us the access the address of a variable in order to store it in a pointer variable. The <code>*</code> operator is called the dereferencing operator; it returns value being pointed to, that stored in the memory location held by the pointer variable. The following code snippet demonstrates these basic operations. Both operators have unary operator precedence, but one tier below <code>()</code> and <code>[]</code> operations.

```c
int a, *toa;  // a is a plain int, toa is a pointer to (memory address of) an int
toa = &a; // toa contains the memory address of a -- its a "pointer to a"
printf("%d",*toa)  // dereference above toa to get the underlying int and print it out
```


<h4>Pointers and parameter passing</h4>
<ul>
  <li> Pointers can be used to "encode" call by reference in C - C has no primitive call by reference
</li>    <li> Pass variable address to pass a pointer (reference) to the variable
	- must use * as part of function prototype and definition parameter
</li>    <li> use *var within function to get or change value being referenced
</li></ul>

Swap example using pointers to pass by reference:

```c
void swap(int * a, int * b) 
// a and b are pointers to integers: addresses of memory locations containing ints
{
	int temp = *a; // dereference a (follow the pointer) to get to underlying integer
	*a = *b;       // "*a =" follows the pointer to get the integer's location, puts what b points to there.
	*b = temp;
}

int main()
{
    int x = 10, y = 5;
    swap(&x, &y);  // pass addresses which are of type "int *"
    printf("%d %d\n", x, y);  // now 5, 10
}
```

<h4>Pointer arithmetic</h4>

<ul>
  <li><code>+</code>, <code>-</code>, <code>+=</code>, <code>-=</code> for other pointers or integers
</li>    <li> Most often used on pointers that are arrays
</li>    <li> Doesn't add the actual number, it adds that number times <code
>sizeof</code> the base type
</li>    <li>e.g. for variable <code>int * p</code>, code "<code>p+1</code>" will in fact generate <code>p+4</code>  <br>
-- 4 bytes ahead will sit the next 32-bit <code>int</code>.
</li>    <li> <code>ptr1 = ptr2</code> assignment works for <code>ptr1/2</code> of same type
</li>    <li>  <code>ptr1 == ptr2</code> etc makes sense to compare ptrs ("do they point to the same memory location?"), and <code>ptr == NULL</code>
</li></ul>

<h4>Pointers to pointers</h4>
<ul> 
<li> When passing a pointer to functions, if want pointer to change, must pass
  address of pointer (pointer to pointer).  
</li><li>Gets confusing to keep track of "which level" you are on -- watch out!
</li></ul>


<h3>Dynamic Memory Allocation in C</h3>

Real Programs need dynamic memory. Arrays we have used up to now must have fixed size from when program launched. Often we need to let program data storage grow unboundedly (up to available memory on the computer). The solution is dynamic memory allocation.
	      
<ul>
  <li>C takes a low-level view of dynamic memory: allocate blocks and free blocks of memory<br>
-- compare to Java/Python/etc where you just say <code>new</code> or invoke class constructor to allocate space for new objects, and a garbage collector frees for you
</li>  <li>Dynamic memory is allocated on a <em>heap</em> (which is a huge dynamically growable array)
</li>  <li>Data persists until it is explicitly <code>free</code>d
</li>  <li>Can return <code>char*</code> from functions, unlike <code>char[]</code>
</li>
</ul>

<h4>Memory Allocation functions</h4>

<code>void * <a href="http://www.cplusplus.com/reference/cstdlib/calloc/">calloc</a> (size_t <em>numels</em>, size_t <em>sizeofel</em>)</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;e.g. <code>int * arr = calloc (10,sizeof(int)); // arr[0] .. arr[9] are fresh 0'd array elements after this statement
</code>

<ul>
<li> Makes array of <code>numels</code> with each element having size <code>sizeofel</code>; initialize all to 0's
</li>    <li> <code>calloc</code> returns a pointer to this new memory block
</li>    <li> Return type is <code>void *</code> and by C type promotion rules its OK to assign <code>void *</code> to any type of pointer
</li>    <li>If <code>NULL</code> (empty pointer) is returned, no space was allocated
</li>    <li><strong>Alert</strong>: its very easy to <code>calloc</code> too little or too much space if you pass in incorrect sizes
</li>    <li>Aside: <code>size_t</code> is C's data type for sizes of things (the result type of <code>sizeof</code>); it should be an <code>int</code> that can hold up to the size of the machine's memory, so it will be an unsigned 32 or 64-bit <code>int</code> depending on your machine.
    </li><li>Aside 2: in older C style the result of calloc etc would need to be <em>typecast</em>; this is no longer needed or recommended.
</li></ul>

<code>void * <a href="http://www.cplusplus.com/reference/cstdlib/malloc/">malloc</a> (size_t <em>size</em>)</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;e.g. <code>char * str = malloc(sizeof(char) * 10); // can copy a 9-character string into fresh str now
</code>
<ul>    <li> Creates memory block of given total <code><em>size</em></code>
</li>    <li> Returns pointer to start of memory
</li></ul>


<code>void * <a href="http://www.cplusplus.com/reference/cstdlib/realloc/">realloc</a> (void *<em>ptr</em>, size_t <em>size</em>)</code>
<ul
>    <li>Copies memory pointed to by <code><em>ptr</em></code> to new place with new <code><em>size</em></code>
</li><li>Returns a pointer to this new copy; frees memory pointed to by <code><em>ptr</em></code>
</li>    <li> <code><em>ptr</em></code> should be a previously *<code>alloc</code>'d value
</li>    <li> <code><em>size</em></code> is as in <em>malloc</em>, for calloc-style use a size (<code><em>numels</em> * <em>sizeel</em></code>)
</li>    <li> If new size is bigger, new space uninitialized
</li></ul>

For all of the *<code>alloc</code> functions above, if allocation fails the function returns null. We should explicitly check for this:

```c
char * memory = malloc(400000);
if (!memory)  // remember null == 0, 0 is false
   printf("Failed to allocate the amount of memory you requested\n");
```

<h4>Deallocating memory</h4><p>

<code>void <a href="http://www.cplusplus.com/reference/cstdlib/malloc/">free</a>(void *<code><em>ptr</em></code>)</code>
<ul>
  <li> deallocates the memory at address <code><em>ptr</em></code>
</li>    <li> <code><em>ptr</em></code> must be a previously *alloc'd return value
</li>    <li> <code><em>ptr</em></code> is no longer pointing to valid storage after <code>free</code>
</li>    <li>A primary source of errors in C code is either <code>free</code>ing memory you are still using, or not <code>free</code>ing memory you are finished with, and using up all your computer memory eventually (a <em>leak</em>) -- not a problem in Java/Python/etc since they have a garbage collector
</li></ul>

<h3>Valgrind</h3>

<ul>
<li> <code>valgrind</code> checks for memory leaks: <code>malloc</code>'d (or <code>calloc</code>'d or <code>realloc</code>'d) storage that is not <code>free</code>'d
</li><li> Also finds invalid memory reads and writes (ie, accessing past end of array)
</li><li> It reports "still reachable" when you forgot to call <code>free</code> but you could have
</li><li> A report of "definitely lost" means you cannot call <code>free</code> because the pointer needed to be deallocated in a helper function, it can't be done in main.
</li> <li> imagine if the Chrome browser called <code>func()</code> 1000 times a second: it would eat up all your memory and then crash
</li> <li>Your submitted programs <em>must not have memory leaks</em>!
</li> <li>See the <a href="http://valgrind.org/docs/manual/quick-start.html">Valgrind.org quickstart guide</a> for more information.
</li>
</ul>


<h3>Dynamic Memory Allocation in C++</h3>

This section will be added later.
