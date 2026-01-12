---
id: hw1
layout: default
title: Homework 1
---

<div class='admonition caution'>
<div class='title'>Caution</div>
<div class='content'>
<ul>
<li>You are expected to work individually.</li>
<li><strong>Due: Friday, September 12th at 11pm Baltimore time.</strong></li>
<li><em>This assignment is worth 60 points.</em></li>
</ul>
</div>
</div>

## Learning Objectives
<div class='admonition success'>
<div class='title'>Objectives</div>
<div class='content'>
<ul>
<li>arithmetic operators</li>
<li>arrays</li>
<li>control structures</li>
<li>input collection and validation</li>
<li>version control using <code>git</code></li>
</ul>
</div>
</div>

### Overview

In this homework, you will write a program to keep track of geographic locations. Each location will be labeled with a single capital letter (in range 'A' to 'Z') and have associated with it a [latitude and longitude pair](https://en.wikipedia.org/wiki/Geographic_coordinate_system#Latitude_and_longitude). The program will allow the user to add and remove locations, list the locations currently stored along with their latitude and longitude, as well as compute the [geographical distance](https://en.wikipedia.org/wiki/Geographical_distance) between two locations.



### Program Requirements

We will use 8 as the maximum number of stored locations that the program must handle. When the program starts, it displays a welcome message and then enters a command loop. The program presents a menu of options, which the user is then prompted to choose from by entering the number corresponding to the option. It must do error handling to make sure the option entered is an integer and a valid option value. Depending on the command, the program will then then prompt the user for the required input, which will also be validated. If the inputs are valid, the program then carries out the command and then continues the command loop by presenting the menu again. The program terminates when there are problematic inputs or the user chooses to quit. (See below for prompts and error handling details.) 


There are five options the user may choose from:

* **Option 1: Add a location:** This option allows the user to enter a new location into the set of stored locations. When selected, the user will be prompted to enter a label for the new location, which must be a (unique) single capital letter (between 'A' and 'Z'), followed by a latitude, longitude pair. The program must validate this input insuring it can be read, falls within the appropriate ranges, and is not already in use. The latitudes and longitudes should be stored as type `double`. Use the `%lf` format specifier to read values of type `double`.

* **Option 2: Remove a location:** This option allows the user to remove a location from the set of stored locations. When selected, the user will be prompted to enter a label which must match one of the stored ones. After removal the remaining locations should be in the same relative order they were previously.

* **Option 3: List locations:** This option allows the user to display the entire set of stored locations, including their labels, latitudes, and longitudes. The labels and their corresponding locations should be displayed one per line using the following format. For example, if the label 'B' is stored representing Baltimore with latitude 39.290400 and longitude -76.612200, the line should be displayed as `B: (39.290400, -76.612200)`.

* **Option 4: Compute distance:** This option allows the user to compute the geodesic distance between two stored locations. When selected, the user will be prompted to enter a first and second label, each separately prompted for and validated. The program will then compute the distance between the two locations using the following formula:

	```text
	acos(sin(lat1)*sin(lat2) + cos(lat1)*cos(lat2)*cos(lon1 - lon2))*EARTH_RADIUS_MILES;
	```
	
	where `lat1`, `lon1` and `lat2`, `lon2` correspond to the stored latitude and longitude coordinates of the given locations **converted from degrees to radians** (you must implement this conversion.) The constant `EARTH_RADIUS_MILES` is declared in the starter code for this homework. Your program should `#include <math.h>` to use the trigonometric functions found there. **All calculations should be done using double precision** (i.e. using type `double` instead of `float`.) When displaying the distance result, use the format specifier `%.2lf` to display only two decimal places of the result. Remember to also compile with the `-lm` option to use the math library.

* **Option 0: Quit:** This option terminates the command loop and exits the program with exit code 0.

### Error Handling

In the following, the error code constants refer to those declared in the starter code provided. The program should handle errors as follows.

* If the program fails to parse an option (e.g. because the user enters a letter instead of a number) the program should print "Error: Unable to read option." and return with error code `ERROR_BAD_OPTION`. If the program succesfully reads a number but it does not correspond to a valid option, the program should simply print "Invalid option." and re-display the menu prompt. 

* If the user attempts to enter more than the `MAX_LOCATIONS` number of locations, the program should print "Error: Max location count exceeded." and return with error code `ERROR_LOCATION_COUNT_EXCEEDED`.

* If at a label prompt the user enters a character that is not a capital letter (between 'A' and 'Z'), the program should print "Error: Invalid label." and return with error code `ERROR_BAD_LABEL`.

* When attempting to add a location, if the label entered is already in use, the program should print "Error: Duplicate label." and return with error code `ERROR_BAD_LABEL`.

* If, when attempting to remove a location or compute a distance between locations, an user-entered label is not found among those stored, the program should print "Error: Label not found." and return with code `ERROR_BAD_LABEL`.

* When reading a latitude and longitude if either coordinate is not a valid `double`, the program should print "Error: unable to read coordinates." If the coordinates are read but they are not in the valid range of -90 to 90 for latitude and -180 to 180 for longitude, then the program should print "Error: coordinate out of range.". In either case the program should return with error code `ERROR_BAD_COORDINATES`.

All error messages must end with a line break. You do **not** need to consider any other errors in your implementation.

### Specifications, Development Requirements, and Hints

In the homework folder of your private repository (the one having the name in the form `YEAR-TERM-student-JHED` or `my220repo`), you should create a new subfolder named `homework/hw1`. Copy into that `homework/hw1` subfolder the starter code file `distance.c` provided in the public repository, from folder `homework/hw1`. At the top of the file, add a comment with your six character alphanumeric **Hopkins ID**. (Please do not include your name or JHED so as to allow for blind grading.)

Use three parallel arrays to keep track of labels, latitudes, and longitudes. You'll also need a variable to count how many different locations have been entered so that you know which elements of these arrays are used.

Make sure that your program consistently checks the return value of `scanf`
so that it knows whether or not input was read successfully.

The starter code provided defines the constant `M_PI`. Use this value when converting latitudes and longitudes from degrees to radians before applying the distance formula provided above.

Throughout your work on this assignment, be sure to frequently add, commit
(supplying meaningful messages) and push your changes to your personal repository. After you complete your work on the assignment, you will be asked to submit a *gitlog.txt* file, just as in [Homework 0](hw0.html). However,
we expect your log for this homework to show more activity.

**Your code is always expected to compile without errors
or warnings on the ugrad servers.** Submissions which do not compile
properly may earn zero points, so be sure to submit to Gradescope early
and often! And once you get a good start on the assignment, always have
some earlier compiling version of your work pushed to Github. Use the following line to compile your code: `gcc -lm -std=c99 -pedantic -Wall -Wextra distance.c -o distance` (the `-lm` option indicates that the compiler should link with the `math.h` library, since you should be using it for your trigonometric functions.) You can then run your program with the command `./distance`. 

### Sample Runs

<div class="admonition caution">
<div class='title'>Caution</div>
<div class='content'>
<p>
When you test your program in a terminal using the example inputs
shown below, the result should be <em>exactly</em> what is shown below,
including spacing. Note that
<ul>
  <li>Each prompt should end with a space, but should <em>not</em> have a newline at the end, with the exemption of the prompt to enter type identifiers and durations.</li>
  <li>Each output line indicating an error <em>should</em> end with a newline.</li>
</ul>
</p>
</div>
</div>

Here are several samples runs of the program on ugrad, where `$` denotes the command prompt, and user input is shown in **bold**. Note that the first line shown below is the command you are expected to use as you compile your program (and the one that will be used by the graders). The compilation line should report zero errors and warnings, as demonstrated in these examples.

**Example 1** (no input errors)

This example demostrates adding locations for Baltimore (B) and Washington (W), listing the locations, computing the distances between them, removing a location and re-listing. 

<div class="highlighter-rouge"><pre>
$ <b>gcc -lm -std=c99 -pedantic -Wall -Wextra distance.c -o distance</b>
$ <b>./distance</b> 
Welcome to the distance calculation program.
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>1</b>
Enter a label: <b>B</b>
Enter a latitude and longitude pair: <b>39.2904 -76.6122</b>
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>1</b>
Enter a label: <b>W</b>
Enter a latitude and longitude pair: <b>38.9072 -77.0369</b>
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>3</b>
B: (39.290400, -76.612200)
W: (38.907200, -77.036900)
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>4</b>
Enter a label: <b>B</b>
Enter a second label: <b>W</b>
Approximate distance in miles: 34.92
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>2</b>
Enter a label: <b>B</b>
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>3</b>
W: (38.907200, -77.036900)
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>0</b>
$
</pre></div>

**Example 2** (bad option)

<div class="highlighter-rouge"><pre>
$ <b>gcc -lm -std=c99 -pedantic -Wall -Wextra distance.c -o distance</b>
$ <b>./distance</b> 
Welcome to the distance calculation program.
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>A</b>
Error: Unable to read option.
$
</pre></div>

**Example 3** (bad label)

<div class="highlighter-rouge"><pre>
$ <b>gcc -lm -std=c99 -pedantic -Wall -Wextra distance.c -o distance</b>
$ <b>./distance</b> 
Welcome to the distance calculation program.
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>1</b>
Enter a label: <b>x</b>
Error: Invalid label.
$
</pre></div>

**Example 4** (duplicate label)

<div class="highlighter-rouge"><pre>
$ <b>gcc -lm -std=c99 -pedantic -Wall -Wextra distance.c -o distance</b>
$ <b>./distance</b> 
Welcome to the distance calculation program.
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>1</b>
Enter a label: <b>B</b>
Enter a latitude and longitude pair: <b>39.2904 -76.6122</b>
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>1</b>
Enter a label: <b>B</b>
Error: Duplicate label.
$ 
</pre></div>

**Example 5** (label not found)

<div class="highlighter-rouge"><pre>
$ <b>gcc -lm -std=c99 -pedantic -Wall -Wextra distance.c -o distance</b>
$ <b>./distance</b> 
Welcome to the distance calculation program.
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>1</b>
Enter a label: <b>B</b>
Enter a latitude and longitude pair: <b>39.2904 -76.6122</b>
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>1</b>
Enter a label: <b>W</b>
Enter a latitude and longitude pair: <b>38.9072 -77.0369</b>
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>4</b>
Enter a label: <b>T</b>
Error: Label not found.
$ 
</pre></div>

**Example 6** (unable to read coordinates)

<div class="highlighter-rouge"><pre>
$ <b>gcc -lm -std=c99 -pedantic -Wall -Wextra distance.c -o distance</b>
$ <b>./distance</b> 
Welcome to the distance calculation program.
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>1</b>
Enter a label: <b>L</b>
Enter a latitude and longitude pair: <b>x y</b>
Error: unable to read coordinates.
$ 
</pre></div>

**Example 7** (coordinate out of range)

<div class="highlighter-rouge"><pre>
$ <b>gcc -lm -std=c99 -pedantic -Wall -Wextra distance.c -o distance</b>
$ <b>./distance</b> 
Welcome to the distance calculation program.
Please select an option:
[1] Add a location
[2] Remove a location
[3] List locations
[4] Compute distance
[0] Quit
Option: <b>1</b>
Enter a label: <b>L</b>
Enter a latitude and longitude pair: <b>90.01 0.0</b>
Error: coordinate out of range.
$ 
</pre></div>

<div class='admonition tip'>
<div class='title'>Tip</div>
<div class='content'>
<p>There may be other ways for the input to be malformed,
besides the ways shown above. You must be careful to check for all the
various ways it might be malformed.</p>
</div>
</div>

### Starter File and Testing

It is your responsibility to test a variety of valid input situations as well as invalid inputs. Make sure to test that every possible error condition detailed in the specifications is handled as specified. Think critically as an adversary for other problems or edge cases that your program might encounter, and test that they are handled appropriately.

For this first real assignment, we are providing a starter file `distance.c` and sample input files with matching output files that you can use to check whether your prompts and outputs are programmed exactly as expected. This is the type of testing that our autograder will usually perform in public and hidden tests. In order to access the samples you will need to download them from our public course repo using commands similar to those in exercise 3b, assuming you have successfully cloned that repository. If not, complete exercises 3a and 3b and ask for help in office hours or class if needed.

First, log into the ugrad system and navigate into your clone of the `cs220-xxx-public` repo (where `xxx` represents the current semester.) Do a `git pull` to get the latest files we have provided. Then, using the unix command `cp` (copy) along with customized file paths based on your file directory set-up, you'll want to copy from `cs220-xxx-public/homework/hw1/` to the directory where you are coding your solution to this assignment. 

When you're ready to test your output locally, compile and run on the input file using input redirection, saving the `stdout` output to file `my_output_xx.txt` (where `xx` refers to the particular number of file you're testing.) For example, to check with the first sample input, run the command:

```
$ ./distance < sample_input_01.txt > my_output_01.txt
```

Now use the unix `diff` command to compare our output file to yours. This does an exact character comparison. The output should be nothing if the files match exactly as shown below.

```
$ diff sample_output_01.txt my_output_01.txt
$
```

If the output files don't match, then you will be shown which lines differ. Sometimes the difference may only be a space that is invisible to us, but that could cause an autograder test to fail. What is shown is the output in the first file (`sample_output_01.txt`) indicated by lines that start with `<` and the output in the second file (`my_output_01.txt`) indicated by `>`. Each pair of lines that differ start with the line number(s) in the first file and the line number(s) of the mismatches in the second file. It is generally recommend that you use the reference file as the first argument to `diff` for consistent interpretation of these results.

You can use this style of testing to make your assignment process smoother throughout the semester. We recommend writing multiple small input files so you can easily re-run them on your evolving solution with input redirection to see if you get the right output. However, we won't usually provide either the input or the reference output for you. You'll need to figure out what that should be.

### Style

You should also make sure that your code has good style. You can look
at the [coding style guidelines
here](https://jhucsf.github.io/fall2024/resources/style.html) from a
course you may take later that also applies to this course. In brief,
you should make sure that your submission is well formed, readable,
consistently styled, and documented as follows:

- it is well commented
- there are no ambiguous or meaningless variable names
- it has proper/consistent bracket placements and indentation
- there are no global variables
- lines are at most 80 characters long

For this homework, since declaring functions has not yet been covered in class,  you are not required to write your own helper functions; i.e. you can have your entire program under the main function. However, if you would like to declare your own functions you are permitted (and encouraged) to do so.

### Submission

Create a *.zip* file named *hw1.zip* which contains only **distance.c**
and **gitlog.txt**. (Do not zip your entire hw1 folder - only these two
files.) Copy the *hw1.zip* file to your local machine and submit it as
Homework 1 on Gradescope.

Recall you can create your `gitlog.txt` file by running `git log > gitlog.txt`.

When you submit, Gradescope conducts a series of automatic tests.
These tests do basic checks like making sure that you submitted the
right files and that your `.c` file compiles properly. If you see
error messages here (look for red), address them and resubmit until
you pass them. Some of the error messages will show results similar to
the `diff` in Testing example above.

<div class='admonition tip'>
<div class='title'>Tip</div>
<div class='content'>
<p>You may re-submit any number of times prior to the deadline; only
your latest submission will be graded.</p>
</div>
</div>

<div class='admonition info'>
<div class='title'>Info</div>
<div class='content'>
<p>Review the course syllabus for late submission policies. Remember that you can use at most 2 late days from your remaining budget for any one
assignment and any portion of a day counts as one whole day.</p>
</div>
</div>


### Grading

Two notes regarding automatic checks for programming assignments:

* Passing an automatic check is not itself worth points. (There
  might be a nominal, low point value like 0.01 associated with a check,
  but that will not count in the end.) The checks exist to help you and
  the graders find obvious errors. This will be true for most of the
  assignments; the actual grades are given manually by the graders, along
  with comments.
* The automatic checks cover some of the requirements set out in the
  assignment, but not all. There will be hidden tests that test edge
  cases. In general, it is up to you to test your own work and ensure
  your programs satisfy all stated requirements. Passing all the
  automatic checks does not necessarily mean you will earn all the
  points. It is an ethics violation for the course staff to tell you
  what is in the hidden tests or whether you pass them, so please
  don't ask!

<div class='admonition danger'>
<div class='title'>No-compile Policy</div>
<div class='content'>
<p>Remember that if your final code submission does not compile, you will
receive a zero score for the assignment.</p>
</div>
</div>

The 60 points for this assignment will be distributed roughly as follows when we grade:

* [9] Submission (including gitlog and deductions for compiler warnings)
* [18] Basic functionality (including prompts and control flow)
* [16] Correctness of results (summary output)
* [12] Input validation and error handling
* [5] Style

Please plan accordingly, and practice incremental coding and testing for best results!
