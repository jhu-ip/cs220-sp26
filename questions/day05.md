---
id: day05_questions
layout: default
title: Day 5 Recap Questions
reference solutions:
  1. junk
  2. [NEW] float mults[] = {1.1, 2.2, 3.3, 4.4, 5.5};
  3. a standard assignment of integer values to characters, "American Standard for Code for Information Interchange". Unicode is extended version for universe (all languages).
  4. [NEW] prints `D 68 d`; no because C will truncate an int to fit into a char type; recommended for clarity and to avoid warnings(?)
  5. "\0" special character to denote the end of the string; 0 in ASCII
  6. 2 ("ab")
  7. [CHANGED] >= length(string1) + length(string2) + 1 (for null) 

---

1. When we declare an array in C, what are the initial values?
2. How would you declare and initialize an array containing the first five multiples of 1.1 (ie, 1.1, 2.2, through 5.5)?
3. What is the ASCII (Unicode) table?
4. What is printed by this code segment? Are the typecast and parentheses in line 2 necessary? recommended?
```c
char ch = 'A';
ch = (char) (ch + 3);
printf("%c %d %c", ch, ch, tolower(ch));
```
5. What is a null terminator? What is its ASCII value?
6. Consider c-string `"ab\0cd\0"` - what is the reported string length?
7. How large must we declare string1 to be in order for the code `strcat(string1, string2);` to succeed? 

