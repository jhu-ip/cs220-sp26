---
id: notes-exceptions
layout: default
title: Exceptions & Error Handling
---

<h3>Error Handling</h3>

This section also applies to C programs. [Not all covered in Fall 2025.]
  
<code>exit(int)</code>
<ul>
  <li> Must <code>#include &lt;cstdlib&gt;</code>
</li>    <li> Used to cleanly and gracefully exit a program immediately 
</li>    <li> Will flush buffers and close files, and execute destructors
</li>    <li> Return code <code>int</code> is passed to the operating system
<ul>    <li> 0 (but use macro <code>EXIT_SUCCESS</code>) indicates no errors
</li><li>non-zero (macro <code>EXIT_FAILURE</code>) indicates errors
</li>    <li> No return to main, immediate quit of program run
</li></ul>
</li>
</ul>

<code>abort()</code>
<ul>
  <li>End program immediately with no clean-up (no destructors, etc.)
</li></ul>

<code>assert(condition)</code>
<ul>
   <li>Its incredibly important to assert invariants you know should be true -- will find errors earlier
</li>    <li> Must #include &lt;cassert&gt;
</li>    <li> Ignored if macro symbol <code>NDEBUG</code> is defined
</li>    <li> If condition true, nothing happens
</li>    <li> If condition false, program aborts, prints file/line# of error and assertion that failed
</li></ul>

Example:
<pre>
    Point *parray;
    parray = new Point[6];
    if (parray == 0) { 
        cerr &lt;&lt; "not enough memory for point array";
        exit(EXIT_FAILURE);
    }
    assert(parray != 0);
</pre>

<h3>Exceptions</h3>

<h4>What are exceptions?</h4>

<ul>
<li>Essentially they are objects that indicate particular error
  conditions have occurred
</li>  <li>  Throwing an exception (via <code>throw</code> syntax) causes the normal program flow to be interrupted
</li>  <li>  At first glance this is like <code>exit</code> or <code>abort</code> 
</li>  <li>  But, you can <em>catch</em> the exception (via <code>try
  ...catch</code> syntax) and handle it gracefully instead of the whole program stopping
</li>  <li>Exceptions thrown include the type of exception and a value of any type that indicates problem details - built-in types include <code>invalid_argument</code>, <code>underflow_error</code>; see <a href="http://www.cplusplus.com/reference/exception/exception/">documentation</a>  for the full list.
</li>  <li>Exceptions are an important programming tool for more structured handling of errors - in C you have to manually keep passing up error codes from failing functions, makes code hard to read
</li></ul>

<h4>How exceptions are processed at run-time</h4>
<ul>
  <li>  Program <code>throw</code>s an exception right where the error first occurs
</li>  <li>  C++ searches for a <code>try-catch</code> block to <em>handle</em> the exception
</li>  <li>  The <code>throw</code> could have syntactically been inside a <code>try</code> block to quickly handle it
</li>  <li> Or (much more common) some calling function up the call stack was running in a <code>try</code> block
 <ul>
	<li> Unwinds the stack by destroying objects created since it entered
    the try block
</li>  <li>  Destructors for local objects in function throwing exception are called
</li>      </ul>
</li>  <li>  The <code>try-catch</code> block stops the exception from propagating up the stack (catches it) and resumes normal execution
 <ul>
	<li> It's a bit more complex than that, <code>catch</code> declares a type of exceptions to be caught and only that type is caught
</li>	<li>  Also, can rethrow (pretend you didn't catch) the exception by simply saying <code>throw;</code> in the catch block
</li>  <li> If the exception is never caught the program will call <code>std::terminate</code> which calls <code>std::abort</code>.
</li>
</ul>
</li></ul>


Simple example:
<pre>
#include &lt;iostream&gt;

int bust(int n) throw (std::overflow_error) // declare exception raised in bust
{
    std::cout << "calling function bust(" << n << ")" << std::endl;
    if (n >100000) throw std::overflow_error("buuusted!");
    std::cout << "finishing function bust" << std::endl;
    return 0;
};
    
void must(int n) throw (std::overflow_error) // since must does not catch, bust exception also declared here
{
    bust(n);
    std::cout << "finishing running must, bust did not throw exception" << std::endl;
};

int main ()
{
    try
    {  must(33);  }
    catch (std::exception & e)
    { std::cout << "caught exception HERE!" << std::endl; } // doesn't run

    try
    {  must(8723643);  }
    catch (std::exception & e)
    {    std::cout << "caught exception THERE!" << std::endl; }

    std::cout << "program still keeps running since exception caught" << std::endl;
}</pre>


<h4>Options for declaring in the header which exceptions a function can throw</h4>

<ul>
  <li><code>void bust(int n) throw (std::overflow_error)</code> means 
      <ul>
	<li><code>bust</code> can throw and perhaps not internally catch <code>std::overflow_error</code>
</li>	<li>and, <code>bust</code> cannot throw any other exceptions
</li>      </ul>
</li>  <li><code>void  bust(int n) throw()</code> means <code>bust</code> can't throw <em>any</em> exceptions
</li>  <li><code>void bust(int n)</code> -- if there is no <code>throw</code> in the header, <em>any</em> exception can be thrown
</li></ul>

<h4>What C++ does with these declarations</h4>

<ul>
    <li> Nothing is checked at compile time (unlike Java exception declarations)
</li>    <li> If an unlisted exception is thrown, <code>std::unexpected</code> is called at run-time
</li>    <li> If there is no <code>throw</code> list (as opposed to <code>throw ()</code>), <code>std::unexpected</code> will not be called
</li>
</ul>


<h4>Making your own exception objects</h4>

<ul>
  <li>The system exceptions such as <code>std::underflow_error</code> are in fact classes
</li>  <li>Throwing an exception causes the run-time to make an object of the class
</li>  <li>The object records relevant information about the exception
</li>  <li>Many system exceptions are subclasses of library class <code>exception</code>  (<code>#include &lt;exception&gt;</code>)
</li>  <li>You can make your own sort of exception by making your own subclass of <code>exception</code>
</li>  <li>Exception type can in fact be anything (<code>int</code>, <code>char</code>, etc) but not generally recommended, subclass from <code>exception</code> instead
</li>
</ul>

An example of a user-declared exception type:
<pre>
#include &lt;iostream&gt;
#include &lt;exception&gt;

class boom: public std::exception {
   virtual const char* what() const throw() // override what() to customize error string
      {  return "BOOM!";  }
};

int main ()
{
    boom myex;
    try
    {  throw myex;  }
    catch (std::exception & e)
    {
        std::cout << "Exception what code is: " << e.what() << std::endl;
    }
}
</pre>

Observe about the above:
<ul>
  <li>  Every exception object has a message string <code>(const char *)</code>, <code>e.what()</code>
</li>  <li>  Constructors for <code>exception</code> objects have string argument (to specify the message)
</li>  <li>  Catch parameters must be passed by reference to take advantage of inheritance
</li></ul>



<!-- ** Don't use exceptions with templates. ** (I have no idea why I had
this note or if/why it's true...) -->

