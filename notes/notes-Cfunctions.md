---
id: notes-Cfunctions
layout: default
title: C Functions
---

<h3>Programmer Defined Functions</h3>

<h4>Function Prototypes</h4> 

Prototypes are function headers without bodies (similar to method declarations in Java interfaces). They let the compiler know a function exists so we can use it without the definition having yet appeared. They serve as code specifications as well, so the compiler knows what a legal call looks like and another programmer knows how that function should be defined.

<ul>
  <li>format is <code><em>return_type fun_name(arg_type_1, arg_type_2, etc)</em>;</code><br>
 example is <code>int randInt(int, int)</code> (notice no variable <em>names</em> needed)
</li><li>Put prototypes after <code>#include</code>s, before <code>main</code>
</li><li>(or put them in a seperate file; this is discussed below)
</li></ul>

<h4>Function Definitions</h4> 

The general format is
<code><em>return_type fun_name(arg_type_1 var_1, arg_type_2 var_1, etc)</em></code>, for example <code>int randInt(int a, int b).</code>


Where can they go?

<ul>
  <li>The actual funcion can go anywhere if there is a prototype declared; otherwise it must appear before any call to it
  </li><li>Function definitions must not be embedded within each other
</li> </ul>

<p>
Return type <code><em>return_type</em></code>

<ul>  
<li> Use <code>void</code> for <code><em>return_type</em></code> if no return value (return statement optional)
</li><li> Default return type is <code>int</code> if none specified
which is usually a bad idea; explicitly declare it <code>int</code> if its an int
</li></ul>

<p>
Parameter list format: 

<ul><li>include type and local name of each variable, comma separated
</li><li> <code>int</code> is default type if none listed (again bad idea); parameter list <code>(float x, y)</code> means first parameter is a <code>float</code> and second parameter is an <code>int</code>
</li><li>Function definitions are all <em>global</em>; they cannot be nested inside other function definitions
</li></ul>

<p>
Function call format

<ul>
  <li> All arguments are passed by value (copied)
</li> <li> Array contents are implicitly passed by reference when the entire array name (memory address) is given as a parameter; see the Carrays Notes for more details
</li></ul>

<h3>Program Structure and Compilation</h3>

<p>
Generally we want to separate function declarations (prototypes) from their definitions into two related files.

<ul>
  <li>C header files (<code>*.h</code>) hold function prototypes (and type declarations)
</li><li>C code files (<code>*.c</code>) contain global variables (to be avoided) and function definitions
</li></ul>

<h4>Preprocessor directives</h4>

The <code>#include</code> directive is used for both language libraries and programmer defined function header files. See also the next section on Compilation for other pre-processor options.

<ul>
<li>	<code>#include &lt;clib.h&gt;</code> -- in effect insert the specified C library file <code>clib.h</code> contents <em>here</em>
</li><li>	<code>#include "header.h"</code> -- in effect insert the programmer defined file <code>header.h</code> contents <em>here</em>
</li><li> <code>#define THING value</code>	 - <code>THING</code> is a macro abreviation for <code>value</code>
</li></ul>

<h4>Compilation</h4>

<ul>
<li> Need to include all <code>.c</code> files to make the executable as in <code>gccc my_funcs.c my_main.c</code> creates executable <code>a.out</code>
</li><li> Here is a standard hack to prevent multiple inclusion of header files
</li></ul>

<code>#ifndef MY_FUNCS_H</code>  // MYFUNCS_H is a flag for the my_funcs.h header file<br />
<code>#define MY_FUNCS_H</code> // define it if its undefined, and load it<br />
// function prototypes go here  <br />
<code>#endif</code> // if the flag was previously defined, no headers loaded


<h4>Object files</h4>

<ul>
  <li>Separation into separate <code>*.c</code> and <code>*.h</code> files supports separate compilation
</li>  <li><code>gcc -c my_funcs.c</code> (note the <code>-c</code> option) produces <em>object file</em> <code>my_funcs.o</code>
</li>  <li>Can then compile a main program that only has to <code>#include my_funcs.h</code> file, <code>my_funcs.c</code> doesn't need to be recompiled:
      <code>gcc -c my_main.c</code> creates object file <code>my_main.o</code>
</li>  <li>Then to create a runnable program, feed all the <code>.o</code> files to <code>gcc</code> as in <code>gcc my_main.o my_funcs.o</code> to create executable <code>a.out</code>
</li>  <li>If you leave out any <code>.o</code> file you will get a link error usually labelled as "undefined reference to functionName"
</li></ul>

<h4>make and Makefiles</h4> 

We use a tool called <code>make</code> along with a special type of file called a <code>Makefile</code> to keep track of all the parts of a program and define their dependences and rules for separate compilation and linking. 

<ul>
  <li><code>make</code> automatically figures out for you which files need to be recompiled and does only that
</li>  <li>Saves you from bad behavior where you forgot to recompile a code file that changed
</li></ul>

<p>
The Unix <code>make</code> program does the making.

<ul>
  <li>For the simplest use of <code>make</code>, the dependencies and directives are in a file <code>Makefile</code> and you type <code>make</code> at the command line to read in that file and compile what is needed
</li><li>To see what will get executed based on a <code>Makefile</code> in the current directory, type <code>make</code> to build an executable, then use the Unix <code>touch</code> shell command to "touch" a file, i.e. update the last written date and fool <code>make</code> into thinking the file was edited.  Here is an example session. Notice how only the changed files, and anything dependent on it, are recompiled/relinked.
</li></ul>

<pre>
% make
gcc -std=c99 -pedantic -Wall -Wextra -O -g   -c -o my_main.o my_main.c
gcc -std=c99 -pedantic -Wall -Wextra -O -g   -c -o my_funcs.o my_funcs.c
gcc   my_main.o my_funcs.o   -o program
% make
make: `my_main' is up to date.
% touch my_main.c 
% make
gcc -std=c99 -pedantic -Wall -Wextra -O -g   -c -o my_main.o my_main.c
gcc my_main.o my_funcs.o -o program
%
</pre>


<h3>Library Functions</h3>

Below are some commonly used function libraries in C. Also see Notes on I/O library (stdio.h), characters (ctype.h) and string (string.h).

<h4>Assert</h4>

Assertions are particularly useful in functions to check the validity of parameter values. When an assertion fails, the program will stop running. If it passes (results in true), then the program keeps going.

	<ul>
  <li> <code>#include &lt;assert.h&gt;</code>
</li>  <li> <code>assert(<em>boolean expr</em>);</code>
</li></ul>

<h4>Math</h4>

The math library has many useful functions. These generally have <code>double</code> arguments and return <code>double</code> values.
  <ul>
    <li> Use <code>#include &lt;math.h&gt;</code>
</li><li> Need to compile with <code>gcc -lm</code> option
</li>    <li>Some of the most common are <code>sqrt(x)</code>, <code>pow(x,y)</code>, <code>exp(x)</code>, <code>log(x)</code>, <code>ceil(x)</code>, <code>floor(x)</code>, <code>sin(x)</code>.
</li>  </ul>
  
<h4>Random numbers</h4> 

The built-in library is very limited, but we can manipulate the results with some common arithmetic expressions to generate different types and ranges of values. Below are a few examples.

<ul>
  <li> <a href="http://www.cplusplus.com/reference/cstdlib/rand/"><code>rand()</code></a> - generates integer between 0 and <code>RAND_MAX</code> (>= short int)
</li><li> <code>#include &lt;stdlib.h&gt;</code>
</li><li> <code>n = a + rand() % b;</code> to get random int between a and a+b-1, assuming all <code>int</code> variables
</li><li> <code>n = a + rand() % (b-a+1);</code> to get random int between a & b inclusive
</li><li> <code>float x = (float) (rand() / RAND_MAX);</code> to get random float between 0 and 1
</li></ul>

We usually explicit "seed" the random generator to generate a new starting value and resulting "random" sequence each time the program is run.

<ul>
  <li>If you don't seed it the numbers will be the same each program run
</li><li> <code>#include &lt;time.h&gt;</code> and use the <code>time()</code> function to seed to the current time of day (in milliseconds)</ul> 
</li>  <li>Seed with <code>srand</code> function <code>srand(time(NULL))</code>; comment this out while debugging to make your results repeatable
</li></ul>


