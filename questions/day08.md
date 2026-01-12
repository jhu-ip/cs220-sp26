---
id: day08_questions
layout: default
title: Day 8 Recap Questions
reference solutions:
  1. to avoid multiple inclusion
  2. compiling translates; linking joins multiple compiled sources together
  3. -c creates .o files (remember -compile, compared to -o for output to another file)
  4. name of a rule to be executed
  5. saves time, prevents errors, only changed files get recompiled
  6. [NEW] See day08-Makefile
  
---

1.	Why do we need header guards?
2.	What is the difference between compiling and linking?
3.  What compiler flag do we use to create object files and what extension do those files have?
4.  What is a `target` in a Makefile?
5.	What are the advantages of using Makefiles?
6. You are given the following two C source files where both files include the header `math_utils.h`:
<ul>
<li>main.c (contains the main() function)</li>
<li>math_utils.c (contains helper functions on basic math operations)</li>
</ul>

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b>Task:</b> Write a simple <em>Makefile</em> that:

<ul><li>Compiles main.c and math_utils.c into object files.</li>
<li>Links them together into an executable called program.</li>
<li>Supports a clean rule that removes all object files and the executable.</li>
</ul>
