---
id: notes-CppStrings
layout: default
title: C++ Strings
---

<h3><a href="http://www.cplusplus.com/reference/string/string/">The <code>string</code> class</a></h3>

<code>#include &lt;string&gt;    // different than &lt;cstring&gt; which is C's string.h
</code>
<ul>
  <li> <code>string</code> is the C++ class name for strings
</li><li> C++ strings are much higher-level than C's, spares you the nitty gritty
</li><li> (C strings are still around and you occasionally need them, e.g. for <code>argv</code>)
</li><li>Still, they are not references: more like a <code>struct</code> than a pointer to a <code>struct</code>
</li><li> Different constructors to make new <code>string</code> objects: invoke with function notation, no <code>new</code> keyword
</li></ul>

```cpp
    std::string s1("hello");        // s1 is "hello"
    std::string s2(3, 'x');         // s2 is "xxx"
    std::string s3 = " world";      // calls copy constructor to make fresh copy of "world"
    std::string s4;                 // empty string "" (NOT a null variable!)
                                    // implicitly calls default constructor
    std::string s5(s2);             // calls copy constructor
```

<h4>String conversions</h4>

<ul>
  <li>no constructor for int or char conversions
</li><li>can assign character to string: <code>s1 = 'h';</code>
</li></ul>


<h4>String representation & operations</h4>

<ul>
  <li>    <code>string</code> object is <em>not</em> a pointer to a char array like in C
</li>  <li>    <code>s[5]</code> still can be used to get individual characters from <code>s</code>, no range checking
</li>  <li>    <code>s.at(5)</code> to get individual characters with range checking
</li>    </ul>

```cpp
    s = "wow"           //  for assignment of literals
    cin >> s            //  input from stream - stops at whitespace!
    cout << s           //  output to stream
    getline(is, s)      //  read to end of line from stream is, store in s
    s1 = s2             //  deep copy assignment 
                        //  or s1.assign(s2) s1.assign(s2, start, howmany)
    s1 + s2             //  string concatenation
    s1 += s2            //  same as s1 = s1 + s2, also same as s1.append(s2)
    == != < > <= >=     //  relational operators overloaded, they just work (no strcmp needed)

    s1.size() == s1.length() == number of characters
    s1.capacity()           // how many characters currently allocated (can increase, see reserve below)
    s1.max_size()                 // max for all strings
    s1.empty()                    // returns a bool
    s1.reserve(s1.length() + 5);  //changes capacity

    s1.substr(where, howmany);
    s1.compare(s2);  // like C's strcmp; most of the time use overloaded &lt; &gt; etc instead
    s1.c_str();  // get c-style string (null terminated character array)

```

<h4>Passing strings to functions</h4>

<ul>
<li>Parameter type often best as a reference type in function header <code>void slurpit(string &amp;s)</code>
</li><li>Otherwise you are passing a <em>copy</em> of the string, can be slow
</li></ul>


