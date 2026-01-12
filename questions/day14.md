---
id: day14_questions
layout: default
title: Day 14 Recap Questions
reference solutions:
  1. Open the file with "rb"/"wb" attributes and use fread/fwrite instead of fscanf/fprintf.
  2. [NEW] `FILE *fp = fopen("img.dat", "wb"); if (fp == NULL) { perror("Error opening file for writing");  return 1; } fwrite(ray1, sizeof(int), 1000, fp); fclose(fp);` to do the writing and `fp = fopen("img.dat", "rb"); if (fp == NULL) { perror("Error opening file for reading"); return 1; } fread(ray2, sizeof(int), 1000, fp); fclose(fp);` to do the reading.
  3. `^`, which is mutually exclusive. i.e. only true if and only if one of the two is true, but not both.
  4. it will perform the operation bit by bit. (extra - You cannot. They are not defined for floats. A compilation error will occur.)
  5. 1 [(00001111 >> 2) || 00000111 <==> 00000011 || 00000111 <=> 3 || 7 <==> 1]
  6. 7 [(00001111 >> 2) | 00000111 <==> 00000011 | 00000111 <=> 00000111 <==> 7]
---

1.	How do we read/write binary files in C?
2. Write the necessary syntaxes to open a binary file named `img.dat` and write all the values of an int array named `ray1` of size `1000` into the file. Next, read all those values into a separate array named `ray2`. Assume `ray1` and `ray2` are properly defined and initialized.
3.	What character represents the bitwise XOR operation? How does it differ from the OR operation?
4.	What happens if you apply the bitwise operation on an integer value? (extra: what if we apply to floats)
5.	What is the result of `(15 >> 2) || 7`?
6.	What is the result of `(15 >> 2) | 7`?
