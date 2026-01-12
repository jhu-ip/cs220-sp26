---
id: notes-control
layout: default
title: Control Structures
---

In general control structures in C are very similar to those in Java.
The <code>for</code> loop is very different than in Python.  Remember
when writing boolean expressions that all numbers are booleans in C:
zero is false, all else is true!  Anywhere a statement appears in
these generic forms, a block statement enclosed in curly braces ({})
could be used instead.

<h4>Decision statements</h4>

Here are generic forms of the decision statements. 
```c
  if (boolean expr) 
    true-statement;  // or { block }

  if (boolean expr)
    true-statement;  // or { block }
  else
    false-statement; // or { block }

  switch (integer expr) {
  case c1: stmt1;  // execution starting point for c1
  case c2: stmt2;
           break;  // exits switch block
  case c3: 
  case c4: stmt3; 
           stmt4;  // executes stmt3, stmt4 and stmtlast for c3 or c4 matches
  default: stmtlast;   // if no case matches
  }
```

<h4>Loops</h4>

Here are generic forms of the three loop types in C.
```c
  while (boolean expr) 
    true-statement;  // or { block }, repeats to while

  do {
    statement-always-executes-at-least-once;
  } while (boolean expr);  // repeat while true

  for (init; boolean expr; update) 
    true-statement;  // or { block }
```
is equivalent to
```c
  init;
  while (boolean expr) {
    true-statement;
    update;
  }
```


<h4>Loop invariants</h4>

These are statements that should be true at the start of every
  iteration.  We can use <code>assert</code> statements to check if
  they are good (true):
```c
  // need #include assert.h for assert function
  // need #include math.h for pow function and compile with -lm option to link math library

  int i = 0;
  int val = 1;
  while (i < 15 ) {
    assert(val == pow(2,i));
    i++;
    val *= 2;
  } 
```


