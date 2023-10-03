# cpp-iterator-boilerplates

A simple file containing boilerplate code to create custom iterators of any kind

**VERSION: 0.1.0**

# Introduction

Programming is not my main activity but I use it mainly to develop tools and/or libraries heling my main activities, like automation of information security related tasks.  Here I currently mainly develop in C++20 (boilerplates can be used on earlier versions, see below).  

The idea for these boilerplates issued from the development of my general library to support other projects and standardize things, like for example status message reporting etc...

From time to time I come across the need to write a custom iterator.  Before C++20 concepts you did this by developing according to  the named requirements for Legacy*Iterator (where * is the type of iterator). This is quite straightforward but error-prone as details or complete features are easily overseen. In this process you often develop until the iterator works as expected in your context which does not assure that it is compatible as expected to all its possible use cases. 

With the introduction of concepts in C++20 we got some help via the *_iterator concepts which verify that the iterator fulfills the expected requirements. On the other hand, if it does not it often (depending on the compiler) results in very cryptic or just useless ("concept X was not satisfied") error messages making it difficult to solve the issue(s).

Now again for my messaging part of the library I have to write a custom iterator for a custom map type. It is actually a weird iterator as the item types in the map is variable (tuples of different types). While I cannot make the iterator compatible to std:map::iterator I still want it to fulfill the std::bidirectional_iterator concept.

Trying to do so ad hoc resulted in useless errors in the used compiler and detecting the problems by going through the concept documentation is very time-consuming and difficult. Especially since all iterators are linked together in a tree, the deeper iterators requiring all the requirements of its "parents" and the bidirectional iterator is already quite deep.  

So I took the decision to create a boilerplate once for all, and by doing so starting at the root of the iterator tree the task is split int smaller requirement changes and easier to handle. Also I decided to use another compiler for this, in order to get better error messages. 

The result is the file provided here which should just compile in any C++20 compiler. But the compilation is only useful to verify that the iterators declarations are valid and pass the concepts. While the iterators themself should be fine for earlier versions of the C++ specifications it is quite useless to compile without the concepts.

# Use cases

Use cases for these boilerplates are:
- Development: Starting point for writing a custom C++ iterator
- Learning: The boiler plate may help new users of C++ to have a quick overview of what functionality each iterator type provides
# What you don't get

## Tutorial for writing iterators

While it still may help for the matter, this project is not meant to be a tutorial for iterators. You are expected to know what iterators are how they are used and at some extension how they work.

It is not excluded that in the future the project will go a little further providing more detailed boilerplates for some generic cases.

## Working iterator and code

The provided classes are boilerplates only with most of the code only provided to avoid error messages during test compilations (for example return statements). In far most cases the provided code is meaningless and will have to be replaced by your iterator code. 
## Any warranty (You don't get any warranty)

The code in this project is provided as-is as boilerplate example only without any warranty nor explicit nor implicit. The author and/or any contributor to this project assure no responsibility for any bug, damage or other objective or subjective negative effects caused either directly or indirectly by the provided code or any related file or information. The user of the here provided code and information is solely responsible of any effect caused by its use.

NOTE: This is only the README file and meant as informal information source without any legal value, please refer to the LICENSE file for all legal information. 

# What you get

## Boilerplates

If you want to develop any custom iterator just pick out the associated class from the boilerplate file and use it as a development base for your iterator. 

# How to use

## Read the boilerplates

### The order of the iterators

All iterators except the input iterator are based on the previous one (in the file).  The input iterator (just like the output iterator) is based on the virtual input_or_output_iterator which starts the file.

Thus the order of the iterators in the file corresponds to their dependency.  Dependency here means that a given iterator must match all requirements of the iterator it depends on. Thus the forward_iterator does fulfill all requirements of the input_iterator, etc...

### Special comments

There are two types of special line-comments. One linked to the C++20 concepts, the other linked to the "Legacy*Iterators"

#### "NEW" comments

New comments are linked to C++20 concepts and document a change in the iterator against its previous depency, i.e. something which was not allowed or not necessary in the previous iterator type. This type of comment will only be shown once but the change will apply to all subsequent 
iterators as well

#### "Legacy*Iterator" comments

The iterators have ben developed firstly against the C++20 iterator concepts. Once the iterators did pass all concepts I did cross check the Legacy*Iterator named requirements and implemented each missing one from there. These "extensions" have then been labeled with the iterator
category that introduced the change.

These requirements are thus not currently enforced by the C++20 concepts.
## Pick appropriate template

Decide on the type of iterator you want to implement and pick the appropriate class from the boilerplate file. For the first test it is preferrable not to change any code as far is possible and  also take the dummy_value_type class.

If you have to change the iterators name due to name collisions (which is not expected),, don't forget to also change the constructor names as well as the "using iterator_t =" in the class.

## Assertion

In your main function (or any other non-template related function) create a variable of given type using the default constructor and insert the appropriate static_assert from the boilerplate into the same function.

## First test compilation

Assuming that your code did compile without error prior to the change, run a test compilation and correct any error. Do not hesitate to report any error you value to have been caused by the original code. 

## Rename

Rename the iterator to its final name, including its constructors and iterator_t
## Cleanup

Once the compilation succeeds cleanup the code:
- Remove the temporary test variable
- Move the static assert into the most used constructor of the iterator and edit its message to reflect its new name
- Remove any useless code (most of it) from all methods and optionally replace it by some implementation guards (like throw std::logic_error("NOT YET IMPLEMENTED"); )
- Change the value_type (and potentially other using statements) to your own used types
- Get rid of the dummy_value_type class
## Develop

Now the fun time starts :-) Start writing your own code for your custom iterator to come to life.

# How you can contribute ?

Please keep in mind that this is work in progress just starting, so that I would suggest not to submit and general discussions like typos etc. as I will review this later.

But...
## Concepts

While the standard gives guidelines for the concepts, they still are implementation specific. So reports of any failure are highly welcome.

Required Information:

- Boilerplate (this project) version
- Full compiler version
- Full error message

## Legacy*Iterator

Feel free to point out if you think I did omit or misinterpret a requirement of the Legacy*Iteraator named requirements

Note: Not all  of the Legacy*Iterator requirements are documented. Only the ones that are not enforced by the C++20 concepts, are.

## Declaration errors

While this is one of the next reviews I will conduct myself, you may also report any sensed declaration (as most definitions are dummy's anyway) mistakes. For example a missing const, etc...

Not to make you loose any time, you may also just wait until version 0.2.x+ which would be the version where I concluded my own review.

## Suggestions

While currently not prioritized, suggestions for future directions may be discussed as well. Potential futures are currently more specialized boilerplates and  iterator templates.

## Miscellaneous

The previous points are of course not meant to be suggestions rather than limits. I.e. other contributions are also welcome ;-)

# Tests

The boilerplate file compiled successfully with the following compilers:

- Gnu C++ V11.3.0
- MSVC++ V19.37.32024