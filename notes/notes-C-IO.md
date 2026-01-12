---
id: notes-C-IO
layout: default
title: C Input/Output
---

<h3>I/O Functions</h3>

<p>See the list of functions on this 
  <a href="http://www.cplusplus.com/reference/cstdio/">reference website</a>.  

<h4>Standard input/output</h4>

<p>We must <code>#include &lt;stdio.h&gt;</code> to use this library.  The standard
     (built-in) streams are defined there: 
<ul>
  <li><code>stdin</code>: keyboard or input redirect input
</li>  <li><code>stdout</code>: standard  output (to console by default)
</li>  <li><code>stderr</code>: standard error output (to console by default)
</li>
</ul>

<h3>Output in C</h3>

<p>
Prerequisite: <code>#include &lt;stdio.h&gt;</code> in header to access library functions; <a href="http://www.cplusplus.com/reference/cstdio/">Reference for <code>stdio.h</code></a>

  <ul>
   	<li> <code>putchar('d')</code> to output characters
</li>	<li> <code>puts("some string")</code> to output strings
</li>	<li> <code>printf("<em>format string</em>", <em>args</em>...)</code> for fancier output
</li>		<li> formats: <br>
&nbsp;&nbsp;&nbsp;	<code>%i %d %f %c %s %n %ld %lf</code> for basic types<br>
&nbsp;&nbsp;&nbsp;			<code>%o</code> octal printing of ints<br>
&nbsp;&nbsp;&nbsp;			<code>%x</code> hex printing of ints
</li>		<li> field widths<br>
&nbsp;&nbsp;&nbsp;
			<code>%<em>cols</em>.<em>decf</em> </code>- eg. <code>%.2f</code>, <code>%.6f</code><br>
&nbsp;&nbsp;&nbsp;
			right justified by default, use <code>%-</code> to left justify <br>
&nbsp;&nbsp;&nbsp;
			<code>-</code> and cols works for %d and %s also
</li>		<li>See Kernighan Appendix B or <a href="http://www.cplusplus.com/reference/cstdio/printf/">this reference</a> for details
</li>	      </ul>

<h3>Input in C</h3>

<h4>Character-based Input</h4>

<ul>
	<li> <code>stdio</code> function <code>getchar()</code> reads one character from a file
</li>	<li> Returns <code>EOF</code> if at end of file
</li>    <li> Value of <code>EOF</code> is -1<br>
&nbsp;&nbsp;&nbsp; <code>getchar()</code> returns an <code>int</code> type for this reason (automatically cast to <code>char</code> if needed)
</li>    <li> Type ctrl-d in a Unix system to produce an <code>EOF</code> from keyboard (ctrl-Z (Enter) on a PC)
</li>  </ul>


<h4>Formatted Input</h4>

  <ul>
    <li>The <code>scanf</code> function works similarly to the printf
    output function for reading formatted input.
</li>    <li>  We use a format
    string followed by the <emph>memory locations</emph> (<em>addresses</em>) we are
    reading into. 
</li>    <li>We indicate this for most variables by preceding the
    variable name with an ampersand character (<code>&amp;</code>) to
    indicate "address of" the variable.  
</li>    <li>An exception is strings
    because they are arrays, and as we'll learn soon, array names are
    the memory address where the array starts. </p>
</li>  </ul>

Here is a list of the most common conversion specifications:<pre>
    %d integer  
    %ld long 
    %c char
    %s string
    %f float (real number type)
    %lf double, Lf long double
</pre>

There are also many fancy input format options, see <a href="http://www.cplusplus.com/reference/cstdio/scanf/">scanf documentation</a> for details:
<ul>
<li>Scan set notation: <code>%[a-zA-Z]</code> - inputs as long as chars in set, <code>[^0-9]</code> is "all except"
 inverse
</li><li> Use character literals to requre but skip over them, eg <code>%d-%d-%d</code> would successfully read <code>2-3-4</code>
</li><li> Use <code>%*c</code> to skip any character (<code>*</code> skips assigning any value)
</li></ul>

<p>Here is a short example:
```c
#include &lt;stdio.h&gt;
int main()
{
    int number;
    float x;
    double y;
    char word[20];
    scanf("%d", &number);
    scanf("%f %lf", &x, &y);
    scanf("%s", word);
}
```

<p>Note that we don't need <code>&amp;</code> in front of word because
        as an array it is an address already.  We also don't use a
        subscript since we're reading into the whole array.  When
        reading a string, scanf only reads up to first whitespace
        (space, tab, ret).  <emph>You must make sure memory is
        allocated for it and big enough to hold the characters that
        are input!</emph>
</p>


<h3>Sequential Files</h3>

<ul>
<li>Declare as: <code>FILE *fptr;</code> (<code>FILE</code> is the type of files, defined in <code>&lt;stdio.h&gt;</code>)
</li><li>Must open file for use, giving it pointer, name, and mode
   <code> fptr = fopen("name.txt", "w")</code>  (returns NULL if error)
</li><br />
<li>types of file openings:
    <ul>
      <li>    <code>"r"</code> - reading
     </li> <li>    <code>"w"</code> - create or overwrite file for writing
     </li> <li>    <code>"a"</code> - open or create file for appending to end
     </li> <li>    <code>"r+"</code> - open for update (read and/or write)
     </li> <li>    <code>"w+"</code> - create (overwrite) file for read &/or write
     </li> <li>    <code>"a+"</code> - open for read or write to end
   </li> </ul>
</li><br />
<li>Close a file when done: 
    <code>fclose(fptr);</code> - very important to permanently save file!
</li><br />
<li>Test for end of file: 
    <code>feof(fptr)</code> returns 1 if end, 0 otherwise
</li><li><code>fflush(fptr)</code> - flush the buffer - usually for output
</li><li><code>rewind(fptr)</code> - set <code>fptr</code> to the beginning of file

</li><br />
<li>The I/O functions above have more general versions for working with files, not  just <code>stdin/stdout</code>: put an <code>f</code> prefix on the name and add <code>fileptr</code> parameter:
    <ul>
      <li> <code>fprintf(fileptr, formatstring, ...);</code>
     </li> <li><code>fscanf(fileptr, formatstring, ...);</code>
     </li> <li><code>fgetc(fileptr)</code>; note <code>fgetc(stdin) == getchar()</code>
      </li><li><code>fputc('c',fileptr)</code>; note  <code>fputc('c', stdout) == putchar('c')</code>
  </li>    <li><code>fputs(str,maxlength,fileptr)</code>; note <code>maxlength</code> is there to prevent buffer overrun holes
</li>      <li><code>fgets(str,maxlength,fileptr)</code>
</li>    </ul>
</li>
</ul>
  
<h3>Binary Files</h3>

  <ul>
<li>Mostly declared/used the same way as text files
</li><li>Add a <code>"b"</code> to the end of open mode passed to <code>fopen</code><br>
-- e.g. <code>FILE fptr = fopen("items.dat","w+b");</code> opens a binary file in <code>"w+"</code> mode.
</li><li>Replace string read/write (e.g. <code>fscanf/fprintf</code>) with binary data read/write (<code>fread/fwrite</code>)
</li><li> <code>fread</code> and <code>fwrite</code> can write raw binary data
    <ul>
      <li> <code>12</code> as binary is hex <code>0xC</code>
</li>      <li> <code>12</code> as text is two characters, hex <code>0x3132</code>
</li>      <li> Note how binary <code>12</code> takes 1/4th the bits to represent
</li>      <li> Pictures, movies, music formats are generally binary to save space
</li>    </ul>
</li><li> <code>fwrite</code> directly writes a C variable contents to a file:<br />
<code>fwrite (varptr, sizeof(vartype), n, fptr);</code>
  <ul>
      <li><code>varptr</code> points to the data to write, <code>vartype</code> is its type, <code>n</code> is how many, <code>fptr</code> is a <code>*FILE</code>
</li>      <li>Example <code>int i = 5; fwrite(&amp;i,sizeof(int),1,fptr);</code> writes <code>0x00000005</code> to the file <code>fptr</code> points to.
</li>      <li>When <code>n &gt; 1</code> it writes an array: <code>int a [] = {5,6,7}; fwrite(a,sizeof(int),3,fptr);</code> writes <code>0x000000050000000600000007</code>
</li>      <li>(Well, it probably actually writes <code>0x050000000600000007000000</code> because your computer is likely using <a href="http://en.wikipedia.org/wiki/Endianness">little endian</a> format. 
</li></ul>
<li>On Unix you can use the shell command <code>hexdump -C items.dat</code> to view the file <code>items.dat</code> as binary data.)
</li>   
<li> Reading <code>fread(varaddr, sizeof(vartype), n, fptr);</code> is the inverse of writing
<ul>
<li>Example <code>int i; fread(&amp;i,sizeof(int),1,fptr);</code>
    would read the value <code>5</code> (from above) into <code>i</code> if the file was rewound to the beginning
</li></ul>
</li>
</li></ul>


<h3>Random access files</h3>

<ul>
<li>Any <code>FILE* fptr</code> is always pointing to a spot in the file where it is going to next read/write
</li><li>With random access you are explicitly moving this pointer around
</li><li><code>fseek(fptr,nbytes, SEEK_SET);</code> sets fptr to position
    <ul>
      <li><code>SEEK_SET</code> means basis point we offset from is file start (absolute)
</li>      <li><code>SEEK_CUR</code> means point to offset from is the current location (relative)	
</li>      <li><code>nbytes</code> is the # of bytes to offset; <code>(n-1)*sizeof(vartype)</code> is the kind of expression usually put there (like in malloc)
</li>    </ul>
<li><code>fseek</code> from the file start (with <code>SEEK_SET</code>) is very similar to how pointer arithmetic does array offsets.  But, pointer arithmetic automatically factors in the <code>sizeof</code> information.
</li><li> <code>ftell(fptr)</code> return the current file pointer position (# bytes offset from 0 == beginning)
</li>
</li>
</ul>

<!-- formatting issues

Here is a small complete example.

```c
#include &lt;stdio.h&gt;
int main(void) {
    FILE *fptr = fopen("test.dat","w+b");
    int i = 4, a[] = {5,6,7};
    fwrite(&i,sizeof(int),1,fptr);
    fwrite(a,sizeof(int),3,fptr);

    fseek(fptr, 0, SEEK_SET);
    
    fread(&i,sizeof(int),1,fptr);
    printf("i is %d\n",i);
    
    fread(a,sizeof(int),3,fptr);
    printf("a[0 1 2] is %d %d %d\n",a[0],a[1],a[2]);
    
    fseek(fptr, 2*sizeof(int), SEEK_SET);
    fread(&i,sizeof(int),1,fptr);
    printf("offsetting + 2 from file start gets to 3rd integer written, %d\n",i);
    
    fseek(fptr, (-2)*sizeof(int), SEEK_CUR);
    fread(&i,sizeof(int),1,fptr);
    printf("backup -2 from here puts us reading 2nd integer, %d\n",i);

    close(fptr);

    return 0;
}
```
-->