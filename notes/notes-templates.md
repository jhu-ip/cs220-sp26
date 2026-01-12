---
id: notes-templates
layout: default
title: Templates in C++
---

<h3>Template Definitions</h3>

We can define our own function and class templates to be instantiated
and used with multiple different types, similar to the STL
algorithms and classes.

<h4>Function Templates</h4>

<ul>
  <li> Can use to define generic function with abstract param types
</li><li> Use <code>template&lt;class Tname&gt;</code> before prototype and function definition
</li><li> Use <code>Tname</code> as type in function
</li><li> Compiler generates the actual functions by substituting types of
    arguments in the various function calls
</li></ul>

Example:

```cpp
template <class T>        // generic class type name T
T cubeit(T num)           // header using type T
{
    return num * num * num;   // assumes * operation defined for type T
}

int main(void) {
  cubeit(3);
}
```

<h4>Class Templates</h4>

For a simple type templated class declare as follows:

<pre>
template &lt;class T&gt;
class MyTemplatedClass
{
	T mydata;
public:
	int myfun(int x);
	// ...
};
</pre>

and declare member functions as follows:

<pre>
template &lt;class T&gt;
int MyTemplatedClass&lt;T&gt;::myfun(int x) { ... }
</pre>

<ul>
	  <li> Use <code>template&lt;class T&gt;</code> at start of class prototype <em>and</em> before every function implementation for the class
</li><li> Can use <code>T</code> as type in class member definitions
</li><li> Use <code>MyTemplatedClass&lt;T&gt;</code> in function implementation as whole class name
</li><li> Use <code>MyTemplatedClass&lt;type&gt;</code> with real <code>type</code> or class in order to create an object
</li>	</ul>

In C++, the <b>class definition and the function implementations must
  be in the same file</b>! You can do this in either a .h, .cpp, or
  even .hpp file. That file must then be compiled with any other code
  using the templated class. Another approach is to put the template
  implementations in a separate file (*.inc) and then #include that at the end
  of your .h template header file.

Using multiple template parameters
<pre>
  template &lt;class T1, class T2&gt;
  class C2 {
       public:
             C2() { };
             C2(T1 a, T2 b) { thing1=a; thing2=b; };
       private:
             T1  thing1;
             T2  thing2;
  };

  //usage
  C2&lt;int, float&gt;  a1;  // nothing is initialized
  C2&lt;double, int&gt; a2(2.3, 4);
</pre>

Templates <em>also</em> support data parameters too, not just types.
<pre>
    template &lt;int Maxsize&gt;  // Maxsize is int template parameter
    class Mstring {
            public:
                  Mstring() { str[0] = '\0'; }; 
            private:
                  char str[Maxsize];
    };

    // usage
    Mstring&lt;20&gt; name;  // copy of Mstring with 20 replacing Maxsize
    Mstring&lt;10&gt; city;  // copy of Mstring with 10 replacing Maxsize

    int i=5;
    //  Mstring&lt;i&gt; zip; // ILLEGAL - must use constant!!

    const int max=5;
    Mstring&lt;max&gt; zip; // LEGAL, max is const-declared
</pre>

The example above is not a practical use of templates however. It wastes space because it makes a copy for each size. Also because they are different types technically, we can't compare name and city variables to each other.
