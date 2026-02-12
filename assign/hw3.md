---
id: hw3
layout: default
title: Homework 3
---

<div class='admonition caution'>
<div class='title'>Caution</div>
<div class='content'>
<ul>
<li>You are expected to work individually.</li>
<li><strong>Due: Fri Feb 20, 11pm (Baltimore time).</strong></li>
<li><em>This assignment is worth 60 points.</em></li>
</ul>
</div>
</div>


## Learning Objectives
<div class='admonition success'>
<div class='title'>Objectives</div>
<div class='content'>
<p>To practice with:</p>
<ul>
<li>2D arrays</li>
<li>strings</li>
<li>file I/O</li>
<li>command-line arguments</li>
<li>Makefiles</li>
<li>program organization</li>
<li>testing with <code>assert</code></li>
</ul>
</div>
</div>

<div class='admonition danger'>
<div class='title'>Individual Assignment</div>
<div class='content'> <br/>
This is an individual
assignment. This means you must not show your working code to another
student, but may discuss with each other the assignment
requirements and expectations. We strongly recommend utilizing office
hours for help! You may collaborate with others and/or AI systems on
*small* snippets of code, not your entire assignment. Remember to
document these mini-collaborations with comments in your code as
specified in the syllabus.
</div>
</div>

### Project Scaffolding ("Starter Code")

In the class public git repository, the folder `/homework/hw3/` contains several files you must use as a starting point for this assignment. From within the public repo, type `git status` to confirm your local copy is in good shape, then type `git pull` to copy this folder. Then copy these files to your personal cs220 repository to begin your work. If you compile the files as posted, you'll see a number of `unused parameter` errors reported, because the files contain incomplete function definitions. As you work on filling in the function definitions, you'll eventually eliminate these warnings. By the time you submit your code for grading, none of these warnings (or any others) should be reported.


### The Problem: Best Word Search

This program will find the valid word (based on a provided word list) in a 2D grid of characters that has the highest total point value, based on Scrabble letter points (https://en.wikipedia.org/wiki/Scrabble_letter_distributions). In order to do this, your program will accept two command-line arguments: the name of a text file containing the character grid and the name of a text file containing words that will be considered valid. 

The program only needs to search for words that are contained in one row, in the forward only direction. In this respect the problem is much simpler than a traditional word search in which words may appear in multiple directions and dimensions. However, you have the additional twist of needing to find the highest point word in the grid, without knowing in advance what words the grid contains. Instead your program will need to efficiently search for each possible substring of each row to see if it appears in the word list. If it does, compute the total point value and save this as the best so far if it is higher than any previous words. Ties: in the case of multiple words with the same highest value, the first one found should be the result, where the searching begins from the top row, left-most character.

We have specific requirements detailed below regarding the structure of your solution code (see Implementation Requirements), test code that must be submitted (see Testing) and use of a makefile (see Makefile). Please read through the entire homework description (including Hints) before you begin. 


### Required Program Functionality

Unless otherwise noted, your program should exit with return value 0.

The program expects two filenames as command-line arguments.
If either or both are missing, the program should print "Error: program usage requires two files names - grid and word list" to `stdout`, advance to the next line, and exit with return value `1`.

If either or both cannot be opened for reading, the program should print "Error: could not open input file" to `stdout`, advance to the next line, and exit with return value `2`.

A proper grid file contains an initial line with two integers indicating the number of rows (N) and columns (M) in the grid. This is followed by N lines of M lower case alphabet letters each. Note that N and M can be different values but are always less than or equal to 20 (MAX_GRID). You can assume there are no spaces between the letters in a row. Anything below the character grid in the input file can be ignored.

There are only 2 types of invalid grids that your program must detect and report. [Note that many other error conditions may exist, but you are not required to handle them.] In either of the following cases, your program should print "Error: malformed grid file" to `stdout`, advance to the next line, and exit with return value `3`:

* if the number of rows and columns cannot be read from the first line
* if any expected letters are missing

Valid words should be read only once from the second text file and stored in your program. Words must be all lower case with at most 15 letters and no spaces. Each line of the file contains a unique word in alphabetical order. You can assume there are at most 500000 words in the file. The program should continue reading words until it reaches the end of the file. Although many different types of errors may occur when collecting this input, your program only needs to detect whether any word is longer than 15 characters. In this case, your program should print "Error: malformed words file" to `stdout`, advance to the next line, and exit with return value `4`. [Hint: read into a very large string and then copy to your list if valid.]

<div class='admonition info'>
<div class='title'>Note</div>
<div class='content'>
You may assume the contents of the input grid file and the input word list are in lower case!
</div>
</div>

For each appearance of a valid word found in the grid, your program should print to `stdout` a line of text containing the matched word, the row number of the end of the word, the column number of the end of the word, and the total point value of the word using the format of this example:

`--- found word: par with 5 pts ending at 3,2`

Number the rows and columns shown in the output starting with 0.

If multiple copies of a valid word are present in the grid, the program must report each of them. Also note that some words found may be substrings of longer words on that line, for example:

```c
--- found word: par with 5 pts ending at 0,2
--- found word: parse with 7 pts ending at 0,4
--- found word: par with 5 pts ending at 2,3
```

Found words should be reported in order of occurrence of the first letter in the search word, when the grid is read row-by-row from left to right, starting with row 0.

After displaying each new word found, one per line, the program should print an empty line, followed by the overall best word found and its total points using this format:

`Best word is parse with 7 points`

The program must also create an output file that reports on each word found that is better than the previous "best". The name of the output file must be the same as that of the input file but with "best_" prepended; e.g. if the first command-line argument supplied to the program is "input_grid.txt", then the output file should be named "best_input_grid.txt". After listing each new "best" word found, one per line, the program should also display the overall best word and its point value, exactly as it appeared in the standard output (see above). Lastly you must write the character grid to the file, but with the best word CAPITALIZED to make it easy to visually locate.

Note that when reporting a new "best" word, it must only print the best word possible from a particular starting cell in the grid, and only if its point total is higher than the previous best total. You will need to strategically initialize variables in order to find this maximum. For the example above, it wouldn't report "par" as a best word because "parse" starts in the same location but is better.

We are providing several sample input files, program runs (which include stdout output), and corresponding output files to help you understand these program requirements. Make sure to study them carefully so that you understand the nuances involved. Ask questions in class or on Piazza!

### Recursion Requirement

You are required to use recursion when searching the grid for a best word. We have provided a method header to help you structure this search, based on a current position. Here is the method header:

```c
/* Find best word in grid based on current position [r,c],
   updating the searched grid to capitalize and the word itself.
   Parameter list holds the valid words and size is how many are in it.
   Return the total point value of the word, or 0 if none found.
*/
int find_best(char crnt_grid[][MAX_GRID], int cols, char word[], int r, int c,
              char list[][MAX_LENGTH], int size);
```

The `crnt_grid` parameter can be updated with capitalized letters for the best word found at this position. The `cols` parameter indicates how many actual columns are used in this character grid. The `word` parameter should be used to (recursively) build the longest found word. Note that you will need to undo updates to `crnt_grid` and `word` when you hit some dead ends during the recursive search. The indices of the current position are indicated by `r` and `c` (row and column, respectively). The `list` contains the list of valid words to use and `size` is how many words it holds.

The function should return the total point value of the word that ends at position [r,c]. This is somewhat counter-intuitive because when it is called from main, the current position [r,c] is the start of the search. In that case, the `word` should be the empty string. However, as the recursion proceeds, the `word` is the longest word found to the left of the current position. In each iteration, the goal is to add the current character to the word if that is still a valid word. Then try to recursively build further by searching one position to the right in the array if you are not at the end of a row.

Here is an algorithm that you can follow. 

```plain
  // try adding current letter to word                                                 

  // if the resulting word is valid, calculate points & print                          

  // if c is not the last column (implicit base case), try to extend:
     // recurse using cell to the right                                                
     // if result is better                                                            
        // capitalize the current letter                                               
        // return these better points
     // otherwise (extend fails) reset extend attempt:
       // remove next character from word                                              
       // uncapitalize next character from grid                                        

  // if valid new word ends at r, c:
    // capitalize current character in grid                                            
    // return points                                                                   
  // otherwise undo word inclusion of current character & return 0   
```

### Examples

Here is a list of provided input files, resulting sample runs (terminal output) and created output files. We will also test your solution with other files to cover situations not included in these examples. **It is really important that you study these to understand program operation and also that you follow the output formats exactly as they appear.**

| Grid File | Word File | Sample Run | Output File |
| ----------- | ----------- | ----------- | ----------- |
| small_grid.txt | small_words.txt | run_small_small.txt | best_small_grid.txt |
| tiny_grid.txt | small_words.txt | run_tiny_small.txt | best_tiny_grid.txt |
| large_grid.txt | clean_large_words.txt | run_large_clean.txt | best_large_grid.txt |

We have also included sample runs for two error conditions. In these cases an output file may or may not be created. Make sure you understand which conditions they test, since you also must create some distinct error condition checks yourself (see Testing section). 

| Grid File | Word File | Sample Run |
| ----------- | ----------- | ----------- |
| small_words.txt | small_grid.txt | run_words_grid.txt | 
| small_grid.txt | large_words.txt | run_small_large.txt |

### Implementation Requirements

* You must use the constants `#define`d in the provided header file.
* You must not use any global (or `extern`) variables.
* Your solution must be split into the three starter files we provide. Specifically: you must implement the functions declared in provided header file `word_funcs.h`, coding their definitions in file `word_funcs.c`. You are strongly encouraged to add other files to these word_funcs files to further modularize your solution. Your main function must reside in a file named `main.c`. Remember to `#include "word_funcs.h"` in your `*.c` files.

* Minimally, you must supply functions with exactly the declarations provided for you in scaffolding file `word_funcs.h`.
* You must also declare and define a function to do a binary seach for a word in a list.

* In addition to the source files mentioned above, you are required to submit additional test situations in a README file, a test program, a working make file, and git log as described below.

### Testing

You are expected to fully test your solution, not only with our provided examples, but also with other examples you create to check its operation in specific cases. For this assignment you must include a README file (plain text, but without any file extension) that describes two error conditions not included in our examples and how you would test to see if your solution handles them correctly.

In addition, you must write and submit a C file named `test_word_funcs.c` that will contain a tester `main` function and `#include word_funcs.h`. This file must have a helper test function to test the declared `points` function and another helper test function for the `find_word` function you must add. The job of each helper function is to call the corresponding function in `word_funcs.c` multiple times to test at least three different situations that each of them will need to handle. Use `assert` statements in each tester function to make sure the functions return expected results. Include comments in your code to describe the situations being tested. The main function in `test_word_funcs.c` should call each helper test function, and if all the tests pass, output "Passed word function tests!!" on `stdout`, advancing to the next line. 

### Makefile
You must submit a working `Makefile` that has a target called **`hw3`** which will be the executable program that is run to test your main program solution. You must also include a target called **`test`** that can be used to execute your test code in `test_word_funcs.c`. Create intermediary targets for necessary object files `*.o`. Also include a `clean` rule to remove `*.o` files and the executables `hw3` and `test`. 

To be considered fully functional, your Makefile should correctly build the executables with the appropriate flags when (and only when) one of the relevant source files has changed. The Makefile must be named `Makefile` (spelling and case are important).

### Git Log
You are expected to use git to backup your progress on this project. Include in your submission a copy of the output of git log showing at least five commits to the repository of code from this assignment, with meaningful commit messages. (You should commit early and often, likely every time you have a version that compiles, so you should probably have many more than five of these). Just before submitting your work, save the output into a file called `gitlog.txt` by executing:

```bash
git log > gitlog.txt
```

### Hints and Tips

Here are some further hints and tips:

<div class='admonition tip'>
<div class='content'>
<ul>
<li>Review the in-class exercise from day 7 for hints on writing a recursive binary search when you create and implement a `find_word` function. 
</li>
<li>Make use of gdb to help debug your program.</li>
<li>Write your function tester functions early, rather than waiting until the last minute. Their purpose is to help you catch bugs in the functions early on, so the bugs don't cause problems when used by main. Using this approach as intended will help you track down bugs more easily.</li>
<li>If in testing your program's output, you want to determine whether two files are identical (e.g. when one file contains your program's actual output and the other contains the expected output) you can use the unix `diff` function: `diff file1 file2` will display symbols, line and character numbers along with the differing characters. Remember you can use the manual pages to get more information on unix commands (`man diff`).  
</li>
<li>In addition to writing tests for individual helper functions that are included in your submission, you should always create and utilize "end-to-end" tests for your complete word search as well. By "end-to-end" testing, we simply mean running the entire program and checking if it behaves as desired on a number of different inputs. Your end-to-end tests do not need to be handed in.</li>
</ul>
</div>
</div>

### Grading

The 60 points for this assignment will be applied as follows (tbd):

* submission, including gitlog [4]
* Makefile [5]
* testing [5]
* error handling [5]
* file input [6]
* function implementations [18]
* output found word results to stdout [5]
* output best results to file [2]
* output grid with capitalized best word to file [5]
* style, including appropriate use of functions (modularization) [5]

### Submission 
Your Gradescope submission should contain at least the following files:

```plain
* main.c
* word_funcs.h
* word_funcs.c
* test_word_funcs.c
* README
* Makefile
* gitlog.txt
* any data files created by you that your tester functions require
```
Create a *.zip* file named *hw3.zip* which contains all the requested files mentioned above. (Do not zip your entire hw3 folder - only the files.) Copy the *hw3.zip* file to your local machine and submit it as Homework 3 on Gradescope. 

<div class='admonition caution'>
<div class='title'>Caution</div>
<div class='content'>
<br/>When you submit, Gradescope conducts a series of automatic tests.  These tests do basic checks like making sure that you submitted the right files and that your `.c` files compile properly.  If you see error messages here (look for red), address them and resubmit. 
</div>
</div>

Two notes regarding automatic checks for programming assignments:
*	Passing an automatic check is not itself worth points. (There might be a nominal, low point value like 0.01 associated with a check, but that will not count in the end.) The checks exist to help you and the graders find obvious errors. This will be true for most of the assignments; the actual grades are given manually by the graders, along with comments.
*	The automatic checks cover some of the requirements set out in the assignment, but not all. There will be hidden tests that test edge cases. In general, it is up to you to test your own work and ensure your programs satisfy all stated requirements. Passing all the automatic checks does not necessarily mean you will earn all the points. Also remember that the course staff can *not* reveal the tests or their outcomes to you. 

<div class='admonition tip'>
<div class='title'>Tips and Hints</div>
<div class='content'>
<ul>
<li>You may re-submit any number of times prior to the deadline; only your latest submission will be graded.</li>
<li>Review the course syllabus and Piazza for late submission policies.</li>
</ul>
</div>
</div>

<div class='admonition caution'>
<div class='title'>No-compile policy</div>
<div class='content'>
<br/>Remember that if your final submitted code does not compile, you will earn a zero score for the assignment.
</div>
</div>


<div class='admonition tip'>
<div class='title'>Code Styling - Style Matters!</div>
<div class='content'>
<br/>
You should always make sure that your code has good style. You can look at the coding style guidelines from a course you will take later that also applies to this course: https://jhucsf.github.io/fall2025/resources/style.html In brief, you should make sure that your submission is well formed:
<ul>
<li>it is not overcommented or undercommented</li>
<li>there are no ambiguous variable names </li>
<li>there is proper/consistent bracket placements and indentation</li>
<li>there are no global variables</li>
<li>lines and functions are a reasonable length</li>
</ul>
</div>
</div>

