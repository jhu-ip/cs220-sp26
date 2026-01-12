---
id: notes-CppSTL
layout: default
title: C++ Standard Template Library
---

<h3>The Standard Template Library (STL)</h3>

<ul>
<li>Provides basic containers (data structures that hold data) and algorithms to make our programming jobs much easier! 
</li>      <li>First we use, then learn how to write, classes
</li>      <li>First we do sequence containers: <code>&lt;vector></code>, <code>&lt;list></code> 
</li>      <li>Other provided containers include array, deque, forward_list, stack, queue, priority_queue, set, multiset, map, multimap, unordered_(set/multiset/map/multimap).
</li>      <li>See <a href="http://www.cplusplus.com/reference/stl/">the cplusplus.com STL library documentation</a> for details (make sure to scroll down on the linked page, there is a master table of what containers can do what)
</li>	  </ul>

<h4>Sequence container common operations</h4>

<ul>
  <li> <code>mysequence.front()</code> reference to 1st element 
</li><li> <code>mysequence.back()</code> reference to last element
</li><li> <code>mysequence.push_back(val)</code>  push <code>val</code> on back, return <code>void</code>
</li><li> <code>mysequence.pop_back()</code>  pop element and return <code>void</code> (use <code>back()</code> to get value before pop)
</li></ul>

Requirements of base data type: copy constructor, <code>=</code> , <code>==</code> , <code>&lt;</code>, default constructor for initialization

<h4>Basic template concepts</h4>

<ul>
	<li> Templates define a class or function that can be used with multiple data types
</li>	<li> The actual data type becomes in some sense a parameter
</li>	<li> Example: <code>vector&lt;int&gt; v;        // declare v as a vector of ints</code><br />
	    --put the type of vector elements in <code>&lt;&gt;</code> after the class name
</li>	<li>(Looks very similar to Java's generics but is in fact different in subtle ways)
     </li> </ul>

<h4><a href="http://www.cplusplus.com/reference/vector/vector/">Vector</a> Type</h4>
<ul>
  <li>It's a smart array, an array with lots of extra features
</li><li> Inserts and deletes at back are directly supported and are very efficient
</li><li> Insert or delete in middle are possible but are slow -- have to shift elements
</li><li> Can access elements with <code>v[num]</code> notation, but no range error checking
</li><li> Using <code>v.at(num)</code> is like <code>v[num]</code> but with range checking -- use this!
</li><li> When fills up, will automatically resize to add more memory and copy to new memory (like <code>realloc</code>)
</li><li> Note that <code>string</code> is a lot like a vector of chars so a lot of <code>vector</code> will look like <code>string</code>
</li>
</ul>

Advantages of using <code>vector</code:

<ul>
<li> Good random access performance
</li><li> Supports random access iterators
</li><li> Supports all algorithms (discussed later)
</li></ul>

Disadvantage: lacks fast insert/delete from middle.

Examples of declaring and using vectors:

```cpp
vector<int> v;        // v is an empty vector of ints
vector<int>::size_type vsize;

const int SIZE=5;
int a[SIZE] = {2, 3, 4, 5, 6};
vector<int> v(a, a+SIZE);// initializes v to the contents of array a

vector<int> v(10);       // vector size 10, elements initialized to 0 default
vector<int> v2(10, 5);   // vector size 10, init to 5

if (v.empty())
        v.assign(10, 2);    // size 10, init to 2
v.assign(a, &a[SIZE]);
v.assign(v2.begin(), v2.end());

v.resize(25, 2);         // add elements init to 2, size 25
v.reserve(25);           // capacity 25, no init
```

<h4>Iterators</h4>

<ul>
	<li> Object to help you move through a container, one item at a time
</li>	<li> Iterators are general and flexible compared to just using integer index iteration: can iterate through all forms of C++ containers
</li>	<li>Declare as e.g. <code>vector&lt;int&gt;::iterator vi</code>
</li>	<li>  <code>vector&lt;int&gt;::iterator</code> here is a <em>type</em> for vector iterators packaged with the <code>vector</code> class
</li>	<li> Iterator works by moving a <em>pointer</em> to an element down the collection
</li>  <li>const version <code>vector&lt;int&gt;::const_iterator cvi</code> that only allows reading of the underlying elements
</li><li> <code>vi = v.begin()</code> - moves pointer to first element
</li><li> <code>vi = v.end()</code> - moves to point after last element    
</li><li> Can do addition on iterators to advance through vectors
</li></ul>

Example:

```cpp
#include <vector> 
#include <iostream> 
using namespace std;

int main(void) {
    vector<double>; dv = {1.1,2.2,3.3,4.4,5.5};
    vector<double>::iterator di = dv.begin();
    di++;                  // di now points to 2.2
    di = di + 3;           // similar to pointer arithmetic on arrays; di now at the 5.5
    di = dv.erase(di);     // delete the item pointed to by di, make di point to next element in dv
    // dv now { 1.1 2.2 3.3 4.4 }
    dv.insert(di,3.3);     // insert before di; means at end since di at end now
    // dv now { 1.1 2.2 3.3 4.4 3.3 }

    di = dv.begin();
    while (di != dv.end()) { cout << *di << " "; di++; }
    cout << endl;
}
```


<h4><a href="http://www.cplusplus.com/reference/list/list/">Lists</a></h4><p>

<ul>
<li>Under the hood it is an implementation of a doubly linked list
</li><li>Efficient for insert/delete in the middle
</li><li>Not as efficient for random access; no notation <code>mylist[i]</code>
</li><li>Supported operations beyond vector ops: <code>splice</code>, <code>merge</code>, <code>front()</code>, <code>push_front(val)</code>, <code>pop_front()</code>,
        <code>remove(val)</code>, <code>unique()</code> (must sort first), <code>reverse()</code>
        
</li></ul>


<h4>A few more STL details</h4>

<ul>
  <li> When you have a vector of pointers to dynamically allocated objects, erasing the
element <em>does not</em> delete the object pointed to
</li>  <li> If an element is <code>erase</code>d from a vector, any other iterators currently sitting further down the vector are invalidated -- the data got moved from under them!
</li></ul>

<h4>Algorithms in STL</h4>

<ul>
  <li> <code><a href="http://www.cplusplus.com/reference/algorithm/">&lt;algorithm&gt;</a>
</code> header contains a vast number of useful algorithms: <code>find</code> elements, <code>move</code>, <code>swap</code>, <code>shuffle</code>, <code>sort</code>, etc.
</li>  <li>Warning: there are limitations on the types of iterators that the different algorithms will work on
</li><li> All algorithms act on container elements (data inside), size doesn't change
</li> </ul>


<h4>Searching/sorting algorithms</h4>

<pre>
void sort(is, ie)
void sort(is, ie, bool func(valtype, valtype))
iter find(is, ie, val)    // returns iter to 1st occurrence of val in range
iter find_if(is, ie, bool func(valtype))
bool binary_search(is, ie, val) // container must be sorted first
bool binary_search(is, ie, val, bool func(valtype, valtype))
</pre>

<h4>Sorting Lists</h4>

<ul>
  <li>For vectors and other containers you can use the <code>sort</code> fuction in <code>&lt;algorithm&gt;</code> but linked lists need a specialized sort method
</li>  <li><code>list.sort()</code> relies on &lt; operator to be defined on the type of elements of the list
</li><li> <code>list.sort(cmp)</code> uses predicate comparator function cmp, similar to C's <code>qsort()</code>
</li></ul>

Example:

<pre>
bool compare(const Card & x, const Card & y) { 
  return x.face  &lt;  y.face;
}

sort(hand.begin(), hand.end(), compare);
</pre>

<h4>Associative Containers, briefly</h4>

<ul>
      <li>Associative containers are like array/vector except replace the <em>sequential number</em> indexing with an arbitrary key.
</li>      <li>Examples: <code>set</code>, <code>multiset</code>, <code>map</code>, etc
</li>      <li>They lack sequence-focused operators like <code>front</code>, <code>back</code>, <code>push_front/back</code> etc
</li>      <li>They are still internally ordered so you can iterate over them with an iterator
</li>      <li>Still can <code>insert</code>, <code>erase</code>, etc
</li> <li><b>Map</b>
    <ul>
      <li>Defines a finite function from any type to any type
</li>      <li>Each element of a map is a pair (domain,range)
</li>      <li>In a <code>map</code> each domain element maps to at most one range (use a <code>multimap</code> if you want to allow more than one range value)
</li>      <li>Array syntax overloaded for pleasant lookup/modification: <code>myRating["Star Wars"] = GOOD;</code>
</li>    </ul>
</li></ul>
    
