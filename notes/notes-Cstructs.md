---
id: notes-Cstructs
layout: default
title: C-Structs
---

<h3>Structs</h3>

We need some more powerful compounding data structures besides arrays  
  <ul>
    <li><em>Structures</em> let us define custom data types with multiple named data elements.
</li>    <li>Unlike arrays, the different elements can have different types
</li>    <li>They are behaviorally similar to classes with only fields, no methods
</li>  </ul>



<h4>Declaring & using struct variables</h4> 

There are two steps needed for declaring them. First we define a new <code>struct</code> type:

```c
struct sname {
  // field declarations
};
```

For example:

```c
struct person {
 char * first, * last;
 int age;
};
```

Next, declare variables of the <code>struct</code> type

```c
struct person p1, p2; // notice how "struct" precedes name
```

We can both define a struct and declare variables <code>p1</code> and <code>p2</code> at the same time. This is not used too often:

```c
struct person {
  char * first, *last;
  int age;
} p1, p2;
```

Once declared, the dot operator is used to access struct fields: <code>p1.age = p1.age + 1</code>.

<h4>Initializing structs</h4>

Can initialize struct variables during declaration:
<ul>
    <li>Use <code>{ ... }</code> as with array initialization, and list of <code>.value</code>s for all components:	<code>struct person joe = { .first = "Joe", .last= "Schmoe", .age = 33 };</code>

</li><li>Fields are initialized in order top to bottom if not specified.
</li><li>If fewer values than parts, remainder are initialized to 0 or NULL<br />
	<code>struct person joe = {"Joe", "Schmoe"}; <br />
    // joe.first == "Joe", joe.last == "Schmoe", joe.age == 0 
</code>
</li>  </ul>


<h4>Passing structs to functions</h4>

  <ul>
    <li>Struct variables are passed by <em>value</em> to functions by default: all components are <em>copied</em>!<br>
--means changes to struct in function body won't be seen by calling function
</li>    <li>To avoid copying, pass a pointer but as const (<code>const person *p</code>) so function can't change struct contents
</li>    <li>Can pass whole structure, or just an element of structure
</li>  </ul>


<h4>Pointers to structs</h4>

Pointers to structs are commonly used. A very common expression is <code>(*<em>sptr</em>).<em>part</em></code> as in this example.

```c
struct person *ppp = malloc(sizeof(struct person));
(*ppp).age = 33;
```

In fact its so common, it has a shortcut:

```c
ppp->age = 33 ; //same as (*ppp).age = 33;
```

NOTE: operators <code>() [] . -></code> have the highest precedence (<a href="http://en.cppreference.com/w/c/language/operator_precedence">full C operator precedence reference</a>)<br>
	-- <code>*ppp.age = 33</code> is a compile error, need parens <code>(*ppp).age = 33;</code>

  <h4>Composing structs with other types</h4>

  <ul>
    <li>Both within a struct and outside it, any type (operator) is possible
</li>    <li>Structs can be used inside other type operators: Array of some struct, array of pointers to some struct
</li>    <li>Any type can also be the type of a field <em>inside</em> a struct: <code>int</code>, arrays, pointer to an array of structs, etc.
</li>  </ul>


<h4>Type abbreviations via <code>typedef</code></h4>

We use <code>typedef</code> to declare type abbreviations for easier typing / reading:

```c
typedef void * blackhole; // new <em>type</em> blackhole defined
blackhole myblackhole; // declares myblackhole as a blackhole, i.e. as a void *
```

This is especially common with <code>struct</code> definitions:

```c
typedef struct {      // note the struct itself is anonymous -- no name given here
  int n1, n2, n3;
} SSN;                // SSN is the type abbreviation
SSN myssn;            // no "struct" needed when declaring, "struct" is part of SSN
```

<h4>Sizes of structs</h4>

<ul>
  <li>Each struct at runtime is a contiguous block of memory
</li>	  <li>e.g. each <code>struct person</code> above will be a 12- or 20-byte block of memory depending on whether pointers are 4- or 8-byte.
</li>	  <li>Plus, for computer efficiency the size is often rounded up to the next biggest word.
</li>	  <li>So, <code>sizeof(struct person) == 12</code> or <code>24</code>
</li>	</ul>

<h3>Enum types</h3>

We can also define a data type to represent a small set of discrete values. Suppose you had a game with playing cards, hearts/clubs/spades/diamonds. <em>Don't</em> just use the strings <code>"Hearts"</code> etc or 1/2/3/4 in the code for these different suits. Instead you can <code>#define</code> them

```c
#define HEARTS 1
#define CLUBS 2
#define SPADES 3
#define DIAMONDS 4
```
<code>Enum</code> version of this is more compact and also defines a data type called <code>suit</code> that can be used to declare variables, parameters, etc.

```c
enum suit {HEARTS=1,CLUBS,SPADES,DIAMONDS}
```

Same numerical abbreviation but makes a new type <code>suit</code> for the values (which is really an integer under the covers). The <code>=1</code> makes the encoded numbers start at <code>1</code> not <code>0</code>, which is the default. Each subsequent label gets the next integer value. 
