---
id: notes-CppIO
layout: default
title: C++ I/O
---

<h3>Input/Output in C++</h3>

C++ has a very simple system for I/O.

<ul>
<li>The bit shift operators <code>&lt;&lt;</code> and <code>&gt;&gt;</code> are overloaded to perform output (stream insertion) and input (stream extraction), respectively
</li><li>C++ overloads meanings of other operators as well, e.g. "<code>+</code>" can concatenate strings (more on this later)
</li>
  <li>Stream extraction operator <code>&gt;&gt;</code> will read into any primitive data type; type read is based on type of variable, not a format string
</li><li> Uses all forms of whitespace to tokenize
</li><li> Invalid input (wrong data type) puts stream in error condition
</li><li> <code>&lt;&lt;</code> and <code>&gt;&gt;</code> are binary operators, result is modified stream, allows chaining
</li><li> Using <code>cin</code> as loop control:  
    value is <code>true</code> boolean if stream is in good state, <code>false</code> otherwise:<br />
<code>while (cin &gt;&gt; n) process(n);<br />
while (cin.get(ch)) process(ch);
</code>
</li><li> Output buffer automatically flushed with <code>\n</code>, <code>endl</code>, <code>read</code>, or buffer full
</li><li><code>std::cerr</code> is a third stream used mainly for error or debugging output
</li></ul>

Here are some examples:

```cpp
std::cin >> thing1 >> thing2;    // read thing1 then thing2 from cin, standard input stream
std::cout << thing1 << thing2;   // write thing1 then thing2 to cout, standard output stream (no spaces included)
std::cout << '\n' << std::endl;  // output newline, newline and flush buffer
std::cin.get(ch);                // read one character

// equivalent form if appropriate using declarations were given:

cin >> thing1 >> thing2;
cout << thing1 << thing2;
cout << '\n' << endl;
cin.get(ch);
```

<h3>Files in C++</h3>

<h4>Stream Classes</h4>

Inheritance is used for different file access modalities, where '*f*' streams are for files (<code>ifstream, ofstream, fstream</code>). C++ also enables using IO operations to read from or write to *<code>stringstream</code>s, using strings instead of files. 

<pre>
                              ios
                            /     \
                    istream         ostream
            /----/     /     \    /     \     \----\
istringstream     ifstream  iostream  ofstream    ostringstream
                                /    \
                          fstream    stringstream
</pre>

<h4>Using File Streams</h4>

Open mode flags for files are in the same sprit as C:
<ul>
    <li><code>ios::app</code> is append to end, C's <code>"a"</code>
</li>    <li><code>ios::in</code> is read, C's <code>"r"</code>
</li>    <li><code>ios::out</code> is write, C's <code>"w"</code>
</li>    <li><code>ios::binary</code> is binary mode, C's <code>"b"</code>
</li>  </ul>

Flags can be combined (via logical or, <code>|</code>, not via the strings <code>"bw+"</code> of C). Example:

```cpp
#include <iostream>
#include <fstream> // file stream library
int main(void) {
    // open for read only
    // ios::in optional here, class ifstream makes it implicit
    std::ifstream ifile("files.txt", std::ios::in);

    // open for write, append to end
    // ios::out optional here, ofstream makes it implicit
    std::ofstream ofile("out.txt", std::ios::out | std::ios::app);
    char ch;
    int num;
    do {
        ifile.get(ch);
        ifile >> num;        // same I/O << and >> syntax as for std::cin/cout/cerr
        ofile << ch << " " << num;
    } while (!ifile.eof());
    ifile.close();
    ofile.close();
    return 0;
}
```

Random access (block I/O) files are treated the same as in C. Member functions, manipulators & operators for iostreams (see below) can be used
with iofstreams for sequential files also, not random access files.

<h4><code>stringstream</code></h4>

This is a string buﬀer that contains a sequence of characters, similar to a file stream.

<ul>
<li> str() function can be used to get the content of the buﬀer
</li><li> str(string) sets the content of the buﬀer to the string
argument
</li><li> << and >> operators can be used with stringstream to
insert/extract content
</li><li> use member function .str() to get the string out of the object
</li><li>Versions specifically for input or output may also be used: <code>istringstream, ostringstream</code>
</li></ul>

```cpp
#include <string>
#include <iostream>
#include <sstream>
int main() { 
  std::stringstream ss;
  ss << "Hello" << ' ' << 35 << " world";
  std::string word1, word2;
  int num;
  ss >> word1 >> num >> word2;
  std::cout << word1 << ", " << word2 << '!' << std::endl;
  std::cerr << ss.str() << std::endl;
  return 0;
}
```

<h3>Formatted output in C++</h3>

Several methods for adding formatting to I/O

 <pre>
#include &lt;iostream>
#include &lt;iomanip>   // I/O manipulators library
using std::cin; using std::cout;
using std::setw; using std::endl;
using std::setfill; using std::setprecision;
using std::fixed; using std::showpoint;

int main()
{
    // inline manipulators examples from iomanip library
    
    // setw(#) to set field width
    cout &lt;&lt; setw(8) &lt;&lt; 100/29 &lt;&lt; endl; // right justify in 8 char field
    cout &lt;&lt; setw(6) &lt;&lt; "jo" &lt;&lt; endl; // right justify in 6 field width

    // setfill to change fill character
    setfill('*');
    cout &lt;&lt; setfill('*') &lt;&lt; setw(5) &lt;&lt; "jo" &lt;&lt; endl; // fill with * not ' '
    //  setfill is persistent, remains until reset or changed
    cout &lt;&lt; setfill(' ') ;           // sets fill back to space

    // setprecision/fixed/showpoint to change numerical formatting
    cout &lt;&lt; setprecision(3) &lt;&lt; 100/29 &lt;&lt; endl;    // <=3 digits after decimal
    cout &lt;&lt; fixed;        // forces fixed precision # of digits
    cout &lt;&lt; showpoint;    // force decimal when precision=0
    cout &lt;&lt; 10.2344 &lt;&lt; endl;
    
    // alternative to above: use I/O member function flags
    // flags determine how output is displayed
    // changes are persistent
    cout.setf(std::ios::fixed); // set fixed flag
    cout.setf(std::ios::showpoint);
    cout.precision(3);    // 3 digits after decimal point
    cout &lt;&lt; 12.3 &lt;&lt; endl;
    cout.unsetf(std::ios::fixed);

    // to save fill flag before changing and restore:
    char oldfill = cout.fill('*');
    cout &lt;&lt; setw(4) &lt;&lt; "jo" &lt;&lt; endl; // **jo
    cout.fill(oldfill);
    cout &lt;&lt; setw(4) &lt;&lt; "jo" &lt;&lt; endl; //   jo
} </pre>

[See also operator overloading notes (to be added).]