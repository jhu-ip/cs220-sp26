---
id: notes-Cstrings
layout: default
title: C-Strings
---

<h3>Strings</h3>

<ul>
	<li> Strings are nothing but an array of characters - there is no primitive <code>string</code> type in C.
</li>	<li> Special null character <code>'\0'</code> needed at the end of every string
</li>	<li> <code>"string literal"</code> is legal, compiler will make a <code>const</code> array of chars to hold it for you.
</li>	<li> No string <code>+</code> concatenation like in Java or Python
</li>	<li> <code>#include &lt;string.h&gt;</code> to access library functions; <a href="http://www.cplusplus.com/reference/cstring/">Reference for <code>string.h</code> functions</a>
</li> 	  <li> <code>strlen(s)</code> returns number of chars before <code>'\0'</code>
</li>	</ul>

<h3>String library functions</h3>
<ul>
  <li>These functions show off pointers and <code>const</code> well
</li><li> They use pointer types <code>char *</code> for strings, not array types <code>char []</code>
</li><li> Memory must previously be allocated by you if you are passing a reference where the function will put a result.
</li><li> The functions use <code>const</code> to indicate arguments they don't change
</li></ul>

<h4><code>stdlib.h</code> string conversion functions</h4>
<ul>  <li> <code>double atof(const char *s)</code>
</li>  <li> <code>int atoi(const char *s)</code>
</li>  <li> <code>double strtod(const char *s, char **endp)</code>
</li></ul>
      
<h4><code>stdio.h</code> string i/o functions</h4>
<ul>  <li> <code>puts(s)</code>
</li>  <li> <code>gets(s)</code> - very insecure, don't use - may overwrite memory not allocated to your program!
</li>  <li> <code>fgets(s, MAXSIZE, stdin)</code> - use this instead; must allocate memory for s first!
</li></ul>


<h4>Common <code>string.h</code> string manipulation functions</h4>
<ul>
  <li> <code>strlen(const char *str)</code> - length of string
</li> <li> <code>char *strcpy(char *dest, const char *orig)</code>
</li><ul>
<li> copy from string <code>orig</code> to string <code>dest</code>
</li><li> return <code>dest</code>
</li>	</ul>
    <li> <code>strncpy(dest, orig, howmany)</code> only copies <code>howmany</code> characters
</li>    <li> <code>char *strcat(char *orig, const char *more)</code>
<ul>    <li> concatenate <code>more</code> to end of <code>orig</code> (orig = orig + more)
</li>    <li> return <code>orig</code>
</li></ul>
</li>  <li> <code>int strcmp(const char *s1, const char *s2)</code>
      <ul>
	<li> compare <code>s1</code> to <code>s2</code>
</li>    <li> return <code>0</code> if same, <code>&lt;0</code> if <code>s1 &lt; s2</code>, <code>&gt;0</code> if <code>s1 &gt; s2</code>
</li></ul>
</li></ul>


Dynamically allocating space for strings and putting them in an array:

```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void addstring(char **stringarray, char *newstring, int * numptr)
{   printf("allocating %lu bytes for %s\n",strlen(newstring)+1,newstring);
    stringarray[*numptr] = malloc(strlen(newstring)+1);
    strcpy(stringarray[(*numptr)++],newstring);
}

int main()
{
    int numstrings = 0;
    char *sarray[100];

    addstring(sarray, "hi", &numstrings);
    addstring(sarray, "ho", &numstrings);
    addstring(sarray, "wee", &numstrings);
    for (int i=0; i < numstrings; i++) {
       printf("%s\n",sarray[i]);
       // must also free the strings to prevent memory leaks
       free(sarray[i]);
    }
}
```

See also the <a href='notes-pointers.html'>Pointers & Dynamic Memory Allocation</a> notes resource.
