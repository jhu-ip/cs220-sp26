---
id: notes-OOdesign
layout: default
title: Object Oriented Design & Teamwork
---

<h3>Object Oriented Design</h3>

A <em>design</em> is a blueprint for the
software structure, including  
<ul>
  <li>technologies (platforms, programming languages, frameworks/libraries) used;
</li>  <li>overall deployment architecture if more than one computer is involved;
</li>  <li>class names and structure (this is <em>object-oriented design</em> after all)
</li></ul>

We are focusing only on the last one in this class, you are being given the first two.

<h4>Starting a Design</h4>

How to start?
<ul>
  <li>Get the developers together (i.e. your project group), find a whiteboard and get going!
</li>  <li>Focus on the <em>key features</em> (the most important ones, not special or corner cases) in the initial design.
</li>  <li>A good way to get off the ground is <em>textual analysis</em>.
</li></ul>


<h4>Begin with textual analysis</h4>

Look at all the English text describing your requirements.
<ul>
  <li>Potential classes are  <em>nouns</em> (the <em>things)</em>
</li>  <li>Potential member functions in the classes are <em>verbs</em>.  
</li>  <li>Any text can be mined, e.g. for chess find a webpage with the rules on it.
</li>  <li>This simple approach can work surprisingly well.
</li></ul>

<h4>UML Class diagrams in brief</h4>

UML class diagrams let you sketch your initial design ideas and how classes relate on paper or whiteboard.

Classes 
<ul>
  <li>Each class is a rectangle
</li>  <li>put class name; line; data members (UML calls them "attributes"); line; member functions (UML calls them "methods")
</li>  <li><a href="http://upload.wikimedia.org/wikipedia/commons/4/41/BankAccount1.svg">example</a> where <code>Dollars</code> is assumed to be a class type 
</li>  <li>The standard is to use <code><em>variable</em> : <em>type</em></code> notation as in the above, but we can just use the C/C++ form of <code><em>type</em> <em>variable</em></code> in our diagrams
</li></ul>

Class relationships

<ul>
<li>See <a href="https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-class-diagram-tutorial/">this site</a> for UML symbols and examples of different relationships between classes
  <li>Inheritance: use an open arrow from derived to base class to show inheritance ("is-a")
</li>
  <li>Associations are shown simply as a line from one class to another
</li><ul>  <li>At the conceptual level they mean two classes are closely interacting with each other
</li>   <li>At a high level, an association implies one may access or change the another;
</li>  <li>At the implementation level they might imply one having the other as a data member
</li></ul>
</li><li>Singular has-a relationships are associations (ie, a field is a member of another class). 
</li><li>Aggregation is when a collection of items from one class is a member of another class and represented with a diamond symbol on the containing class
</li>
</ul>

Attributes (aka data members / fields)

<ul>
  <li>In a UML class diagram, the <em>attributes</em> represent what the C++ data members might be
</li>  <li>Generally for simplicity if there is an association between two classes or a getter member function you don't also need to show the attribute in the class 
</li></ul>

The above only covers the most basic features; if you want more information, <a href="http://www.ibm.com/developerworks/rational/library/content/RationalEdge/sep04/bell/">here is a tutorial from IBM</a>

<h4>Design refinement tips</h4>
<ul>
	<li>Think about an individual class'
	    <em>responsibilities</em>; make any responsibility or
	    action a class needs a member function 
	    of the class (with an evocative name so you will remember
	    what its  supposed to do)
</li>	<li>  Play out different use-cases over the class diagram and make sure there is a class and member function responsible for implementing each action in the use-case
</li>	<li>If a class has no member functions that probably means its not doing anything;
	    throw it out
</li>	<li>If two or more classes are
      similar but not quite the same, make an abstract 
   superclass of them containing the shared functionality - let inheritance emerge; don't force it
</li>     </ul>

<h4>Design Pitfalls in a nutshell</h4>

<ol>
       <li>The <em>Data-centric design</em> trap
<ul>
  <li>A data-centric design has classes with no meaningful member functions - they are just passive data <em>holders</em>
</li>  <li>Data-centric designs tend to have a couple really fat classes
      doing all the operations and a bunch
      of tiny classes that just passively hold data
</li>  <li>Data-centric designs should be refactored to push methods from the big class out to the data classes
</li>  <li>Example of a <strong>bad</strong> data-centric design for chess: pieces that are basically <code>struct</code>s with no meaningful member functions and all the member functions are in the <code>Board</code> or <code>Game</code> class
</li></ul>
</li><li>The <em>Over-eager inheritance</em> trap
    <ul>
      <li>In many cases there may be is-a relationships where all there is no real code difference between the base and derived classes
</li>      <li>In this case simply <em>don't inherit</em>
</li>      <li>Example: making a class <code>Suit</code> with subclasses <code>SpadeSuit</code>, <code>HeartSuit</code>, <code>DiamondsSuit</code>, <code>ClubsSuit</code> has nice is-a properties but the code is pretty much the same so in nearly all card games there is no meaningful inheritance there
</li>      <li>If you have derived classes with no new or overriden methods other than constructors/getters/setters than you likely have unnecessary inheritance
</li>    </ul>
</li><li>The <code><em>switch</em></code> smell
    <ul>
      <li>If your code has lots of <code>switch</code> or <code>if</code> statements, it often means the decision being made could instead be based on which subclass you have at run-time and so you don't need to <code>switch</code>.  
</li>      <li>An example in chess is if the <code>move()</code> function was all in the main <code>Game</code> and just did a big <code>switch</code> on which type of piece was being moved.  <em>Don't</em> do that, put the <code>move()</code> action on the <code>Piece</code> and override as needed.
</li>    </ul>
</li></ol>


<h4>Evolution of Initial Designs to Code</h4>

The first step is to take the proposed classes and member functions
and map them on to class templates
<ul>
  <li>Create a C++ header file for each proposed class.  At the top write a  brief comment describing the purpose of the class.
</li>  <li>For classes closely associated with each other, consider making a data member in one to give access to the other.
</li>  <li>Proposed member functions become C++ member functions in your <code>.h</code> file.
</li>  <li>Put types in your <code>.h</code> file if they are clear, and use <code>()</code> and <code>void</code> if not.
</li></ul>


<h3>Teamwork</h3>

Pair Programming utilizes driver/navigator roles and implements the "two heads are better than one" approach:
<ul>
	<li>Driver is the only person with hands on the keyboard
</li>	<li>Navigator is looking out for the bigger picture and for errors made by driver
</li>  <li> Take turns in roles
</li>  <li> Highly recommended that you try out pair programming
</li></ul>

Teamwork: the Good ..
<ul>
  <li> Open and frequent communication
</li>  <li> Multiple perspectives & ideas
</li>  <li> Sharing of work according to abilities
</li>  <li> Planning
</li>  <li> Asking for help
</li>  <li> Sharing code/work (commit early, commit often)
</li>  <li> Compromise approaches:
   <ul> <li> Try several, pick best
</li>    <li> Take turns
</li>    <li> Find middle ground
</li>  </ul>
</li></ul>

... the Bad ...
<ul>
  <li> Can't agree on things
</li>  <li> Scheduling work with partners
</li>  <li> People don't pull their weight
</li>  <li> Time management & expectations
</li>  <li> People not properly integrating their code
</li></ul>

... and the Ugly
<ul>
  <li> One person does all the work
</li>  <li> Procrastinating, not getting things done
</li></ul>

