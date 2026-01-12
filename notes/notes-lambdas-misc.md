---
id: notes-lambdas-misc
layout: default
title: Lambdas & Miscellany
---

These notes are a collections of miscellaneous topics, mostly new to C++11 version, not all of which are explicitly covered in the course. 

  The 2011 update of the C++ language standard introduced a whole bunch of new 
  features; we've  used some, but also we've been doing things
  the "old fashioned" way, for two reasons.  First, C++ has been around a long
  time and there's a lot of legacy code out there that you'll need to understand.
  And second, some of the features can be confusing, or can hide and obscure
  what's really going on, if you don't already understand what they're shorthand for.

  We'll give a brief overview of some of these features here; we won't have
  time to go into depth on everything, so for a more detailed and comprehensive
  look, check out <a href="http://www.stroustrup.com/C++11FAQ.html">Stroustrup's
  C++11 FAQ</a>.


<h3>lambdas (covered)</h3>
  <ul>
    <li> C++11 introduced a new syntax for something called a "lambda".  If
      you've never seen any functional programming, you can think of it as a
      small, un-named, one-off function.  It's basically the function equivalent
      of a string-literal.  You use square braces followed by a function
      signature to write a lambda.
</li>    <li> You can use one in place of a function pointer, which is particularly nice
      for things like qsort.  E.g.:
      
      <pre>
std::vector&lt;Person&gt; vec;
// ...
// sort by name field
std::sort(vec.begin(), vec.end(), [](Person a, Person b) { return a.name&lt;b.name; }); 
      </pre>

</li>    <li> You can also let a lambda "capture" local variables, by putting the
      names of those variables inside the brackets, with either an &amp; (to
      capture by reference), or a = (to capture by value).  In either case, the
      (reference or copy) local variable will be accessible inside the body of
      the lambda; by default, nothing gets captured, but you can use an &amp;
      with no name to say "capture everything that's in scope".  E.g.:

<pre>
std::vector&lt;Person&gt; vec;
std::vector&lt;int&gt; indicies;
// ...
// sort indicies by the name of the person corresponding to that index
std::sort(indicies.begin(), indicies.end(), [&amp;vec](int a, int b) { return vec[a].name&lt;vec[b].name; }); 
</pre>
</li>  </ul>

  <h3>Other Features</h3>

In no particular order...

  <h4>auto</h4>

<ul>
    <li> C++11 introduces the keyword <code>auto</code> (technically, it was
      already a keyword, but the old meaning was never actually used).
      Basically, you can use it in place of a typename to ask the compiler to
      figure out the proper type for you.  
</li>    <li> Note that this is still a compile-time
      decision; the type can't change, it's not dynamic.  It's just a way to have
      the compiler figure out the correct thing to write (it's basically equivalent
      to just writing the correct thing yourself).
</li>    <li> The main reason to use this is either when the type name would be really
      long and annoying to type out (e.g. iterators), or when writing complex
      templates where you can't figure out the right type until the template gets
      instantiated (but it's still clear to the compiler for any given template
      instance).
</li></ul>      

Examples:

<pre>
int a = 7; // a is an int
auto b = 7; // b is also an int
auto c = 7.0; // c is a double
std::vector&lt;std::string&gt; v; // v is a vector of strings
auto iter = v.begin(); // iter is a std::vector&lt;std::string&gt;::iterator

template &lt;class T, class U&gt;
void printMul(const T &amp;left, const U &amp;right) {
    auto result = left * right; 
    // result is whatever type we get when we apply the multiplication 
    // operator to a T and a U
    std::cout &lt;&lt; result;
}
</pre>

<h4>Type aliasing (aka template alias)</h4>

As an alternative to <code>typedef</code>, C++11 gives us another way to specify a name for a type:

<pre>
using sviter = std::vector&lt;std::string&gt;::iterator;
</pre>

The advantage of this over <code>typedef</code> is that it plays nice with templates, so we can have some template arguments specified, and some blank, to do something like:

<pre>
template&lt;class T&gt;
using Vec = std::vector&lt;T,My_alloc&lt;T&gt;&gt;; // always use my custom allocator

Vec&lt;int&gt; v = {1, 2, 3, 4, 5}; // type of v is std::vector&lt;int, My_alloc&lt;int&gt;&gt;
</pre>

<h4>nullptr</h4>

We've used this one; if you're not using -std=c++11, it won't work.
      In that case, you can still use the old C-style <code>NULL</code> macro.
      The main difference is that NULL is literally a <code>macro</code> for 0, 
      whereas <code>nullptr</code> actually has a pointer type (i.e. it's not an
      integer).  This means the compiler can do proper typechecking: e.g.

<pre>
int *ip = NULL; // fine, i is a null pointer
int i = NULL; // fine, i is 0
int *jp = nullptr; // fine, j is a null pointer
int j = nullptr; // error; won't compile due to incompatible types
</pre>

  <h4>range-for</h4>

 As a shortcut for writing a for-loop using an iterator, we can write a
      for-all loop similar to the way we can in Java or Python.  The following
      two loops both print out all the elements of a vector:

<pre>
std::vector&lt;int&gt; vec = {1, 2, 3, 4, 5};

for (auto x : vec) { // type of x will be int
  std::cout &lt;&lt; x;
}

// is the same as

for (auto itr = vec.begin(); itr != vec.end(); itr++) { // type of itr will be an iterator
  std::cout &lt;&lt; *itr;
}
</pre>

 Note that the range-for loop gives us copies of the elements, rather
        than an iterator; we don't need to de-reference, and we can't
        increment/decrement.  If we want to change the values of the elements,
        we need to use references.  For example, to add one to each element of
        the vector, we could do:

<pre>
for (auto &amp;x : vec) { // type of x will be a reference to an int
  x++;
}
// vec is now {2, 3, 4, 5, 6}
</pre>

  <h4>"Raw" string literal</h4>

<ul>
    <li> Writing strings that are supposed to have literal copies of escape
      sequences is a pain.  E.g. to print the actual string "word\t\\\t", we
      would need to do something like <code>cout &lt;&lt;
      "word\\t\\\\\\t"</code>.  It's often hard to be sure we typed what we
    meant, and it's hard for someone reading the code to figure out what this
    line prints.
</li>    <li>
      C++11 gives us a way to write a string where all "special" characters are
      ignored and treated as normal characters: use R"()" around your string,
      instead of just "", and it will be interpreted as literal charecters.
      Note that if you do this, there's no way to put e.g. an endline in your
      string.
</li>    <li> the above string would then be just <code>R"(word\t\\\t)"</code>
</li></ul>
<pre>
std::string s1 = "word\\t\\\\\\t";
std::string s2 = R"(word\t\\\t)"; // s1 and s2 contain the same characters
</pre>

  <h4>delegating constructors</h4>

In C++11, one constructor for a class is allowed to call another constructor
      for that class; in earlier versions of the language, this was not allowed.  So,
      for instance you can now have a default constructor that works by
      calling another with a default value, e.g.:

<pre>
Class C{
  private:
    int data; // should be in range 0-10

  public:
    C(int x) {
      // squash x to be in the range 0-10
      x = x &lt;0 ? 0 : x;
      x = x &gt;10 ? 10 : x;
      data = x;
    }

    C() : C(7) {} // default to a value of 7
};
</pre>

  <h4>override and final</h4>

<ul>
    <li> C++ doesn't require any special notation to indicate that a method is
      overriding another method (though the method must be marked
      <code>virtual</code> in the base class).  This can lead to subtle bugs,
      where you think you've overriden a method, but haven't actually because
      the function signatures don't quite match.  Common problems are when one
      method is const, but the other leaves off the const specifier, or when
      the parameters aren't the same types in the same order, or when we forgot
      to put "virtual" in the base class.
</li>    <li> C++11 gives us the keyword <code>override</code>, which can be used
      to tell the compiler we think a given method should be overriding something
      in the base class.  This way, the compiler can check for us, and give us an
      error message if we aren't actually overriding something.  Essentially, this
      is a feature to make debugging inheritance and dynamic binding problems
      much easier.
</li>    <li> Using <code>override</code> is completely optional, but it's extremely good practice;
      you should basically always use it as a matter of convention.
</li>    <li> We also have the keyword <code>final</code>, which can be added to the
      end of a method declaration to indicate that sub-classes should not be
      allowed to override that method.  Note that this is stronger than just
      saying it's not virtual; with a non-virtual method, the sub-class can have
      a method of the same name, but it won't be an override.  With a
      virtual-final method, the sub-class is not allowed to have a method with a
      matching signature.
</li></ul>

<pre>
class A {
  public:
    virtual void f(int) const;
    virtual int g(double);
    virtual int h() const final;
};

class B : public A {
  public:
    void f(int) override; // compiler will give us an error because we forgot const
    int g(double) override; // okay, no problems
    int h() const; // error, can't override because it was declared final
};
</pre>

<h4>Initializer lists</h4>

Prior to C++11, there were different ways of initializing variables depending
      on their type. 

<pre>
int x = 7;
int y[4] = { 1, 2, 3, 4};
std::vector&lt;int&gt; v(4, 1); //make a vector with 4 ints, each with value 1
</pre>

In C++11, we can now use the curly-brace notation safely, regardless of the
 type of the thing we're initializing.  The following is equivalent to the previous example:

<pre>
int x{7};
int y[4] {1, 2, 3, 4};
std::vector&lt;int&gt; v{1, 1, 1, 1};
</pre>

You can also use empty braces to say you want a default initializer, which 
      works even for basic types:
<pre>
int a{}; // a is 0
double b{}; // b is 0.0
int *p{}; // p is nullptr
char buf[12]{}; // buf contains 12 null characters (i.e. 12 copies of '\0')
std::string s{}; // equivalent to std::string s, calls default constructor for class
</pre>

  <h4>Class default initializers</h4>
<ul>
    <li> In earlier versions of C++, the only way to initialize (non-static)
      class member variables was in a constructor.
</li>    <li> In C++11, you can specify default values in the actual class definition.  E.g. the following two class definitions are equivalent:
</li>
</ul>

<pre>
class C {
  private:
    int x;
  public:
    C(): x(7) {} // default constructor initializes x to 7
};

class C {
  private:
    int x = 7;
  public:
    C() {} // x is automatically initialized to 7
};
</pre>


  <h4>default and delete</h4>

 C++11 introduces the keywords <code>default</code> and <code>delete</code> as a way of controlling which of the "free" class methods you actually want to use.  Normally, you get a default constructor, as well as (shallow) copy constructor and operator methods.  You can use =default to explicitly declare that you're using the default versions, or =delete to explicitly prevent the default versions from being used.  E.g.:

<pre>
class D {
  public:
    D() = default; // automatic default constructor
    D(const D &amp;) = delete; // no automatic copy constructor
};
</pre>

  <h4>move vs. copy, rvalues</h4>

Sometimes, making copies of things is wasteful; e.g. copying a
      temporary value that's about to go away may be very expensive; it would be
      better to just "steal" the original version of that object for the
      assignment.  E.g.:

<pre>
std::string s1 = "this is a long string";
std::string s2 = f(s1);
</pre>

<ul>
<li> In this case, assuming that f() returns a string, the string that
      gets constructed inside f() will be copied into s2, and that "temporary"
      version of the string will then get discarded.
</li>    <li> C++11 gives us a way to handle this case efficiently; if we know that
      it's safe to do so, we can just "move" the original object, rather than
      making a copy of it.
</li>    <li> The thing on the right hand side of an assignment operator is often
      called an "rvalue" (the thing on the left is called an "lvalue").
      Generally speaking, anything that is (or could be) an lvalue is not safe
      to move, but an rvalue is (because it will be discarded before the next
      line of code is run anyway).
</li>    <li> In C++11, we can indicate an rvalue reference with a double-ampersand;
      that is &amp;x refers to an lvalue reference (i.e. a normal one), but
      &amp;&amp;x means that x is an rvalue reference.
</li>    <li> Mostly, this is useful because it lets us write "move" style operations in
      our classes:
</li></ul>

<pre>
class E {
  // ...
  E(const E&amp;); // copy constructor
  E(E&amp;&amp;); // move constructor
  E&amp; E=(const E&amp;); // copy assignment
  E&amp; E=(E&amp;&amp;); // move assignment
};
</pre>

 Remember swap? This makes it a lot more efficient! But we may need to
      tell the compiler it's safe to treat things as r-values, which we do with
      a special function called move():

<pre>
template&lt;class T&gt;
void swap(T &amp;a, T &amp;b) {
  T tmp = move(a); // a is probably broken after this
  a = move(b); // b is probably broken after this, but a is fixed
  b = move(tmp); // tmp is probably broken after this, but b is fixed
}
</pre>

 Note that this swap method will work for any class that has a
      move-assignment operator defined; if we don't define move-assign, this
      won't work!  Fortunately for you, the STL has been re-written so that it
      all takes advantge of move semantics, meaning that all sorts of stuff got
      more efficient overnight without even needing any changes to user code.


  <h4>static_assert</h4>

<ul>
    <li> Normal assert statements do a runtime check, and cause the program to exit if it fails.
</li>    <li> C++11 introduces a "static assert", which does a compile-time check, and produces a compiler error if it fails.
</li>    <li> Note that this is useful for a different kind of thing; it's not going to work with dynamic things, only things that can be determined one way or the other at compile time.
</li>    <li> It's basically another tool to let you write tests that will fail early if there's a problem, letting you avoid the situation where the problem causes subtle errors that only manifest later. 
</li>    <li> It also lets you specify the error message to print if it fails. E.g.:
</li></ul>

<pre>
struct S { X m1; Y m2; };
static_assert(sizeof(S)==sizeof(X)+sizeof(Y),"unexpected padding in S");
</pre>

  <h4>noexcept</h4>
<ul>
    <li> If a function you declare with <code>throws()</code> actually tries to
      throw an error, the program will end, but it will properly unwind the
      stack, call destructors, etc.  Basically, you can still throw, but the
      exception can't be caught.
</li>    <li> In C++11, we can also declare the function to be <code>noexcept</code>,
      which will cause the program to terminate abruptly if an exception is
      thrown inside that method, equivalent to calling abort().  Basically,
      exceptions truly cannot propagate from this method, the program will die
      abruptly before letting it happen.
</li>    <li> Most of the time, we don't really need this behavior, but it's
      important to know what it means and how it works.  noexcept is also more
      efficient than throws().
</li>  </ul>

<pre>
int func(int a, int b) noexcept;
</pre>

