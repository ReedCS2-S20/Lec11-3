# Lecture 11-3 SMART POINTERS

`Slide 01` [Part 01. Intro to Smart Pointers](https://ensemble.reed.edu/Watch/b2SGr73Z) *02m30s*  
`Slide 03` [Part 02. `mutable` in Lambdas](https://ensemble.reed.edu/Watch/z7K4QdEe) *04m15s*  
`Slide 12` [Part 03. Pointer Bugs](https://ensemble.reed.edu/Watch/Hr35LoJa) *08m15s*  
`Slide 20` [Part 04. Reasoning About Resources](https://ensemble.reed.edu/Watch/n5XLy42A) *11m45s*  
`Slide 30` [Part 05. Automatic Garbage Collection](https://ensemble.reed.edu/Watch/e3Q4Hcq2) *12m00s*  
`Slide 59` [Part 06. `shared_ptr` Preview](https://ensemble.reed.edu/Watch/o6JLs95X) *14m00s*  

There is the usual slide deck here. It illustrates two versions of a
`Box` class, once with bugs, and another with the bugs fixed using
`std::shared_ptr<int>`. It also shows these used in a singly linked
list. These and the other two "smart pointer" types in the C++ STL are
discussed. This can be summarized as follows.

The C++ STL provides three template types (`#include <memory>`):

* std::unique_ptr<T>: used to reference an object owned by one code
component (i.e. one variable). It cannot be copied. It can be moved.

* `std::shared_ptr<T>`: used to reference an object shared by several code
components. It maintains a *reference count*. Copying a shared pointer
increments this count. If a `shared_ptr` variable loses scope or if an
object with a `shared_ptr` component is deleted, it is decremented.

* `std::weak_ptr<T>`: only constructable from a `shared_ptr` without
incrementing its count. Used many ways, including in cyclic
structures.

The `samples` folder contains the singly-linked list code `llist.cc`.
It also contains three versions of a doubly-linked list. One of these,
named `dbllist_bad.cc` is broken. Since all the pointers are
`shared_ptr` references, and since there is a cyclic structure within
doubly-linked lists, the nodes aren't properly deallocated.

The other two fix the `_bad` one in two ways:

* `dbllist_better.cc`: all references are `shared_ptr` here, as well.
But the explicit destructor traverses the list and sets all the 
`prev` links to `nullptr`. This has the effect of breaking any cyclic
structures in the list so that the nodes' `shared_ptr` reference counts 
can go to 0, leading to their reclamation.

* `dbllist_best.cc`: this code instead works with `prev` links of
type `weak_ptr`. These copied references from `shared_ptr` instances
don't increase the reference count. In this way, the `shared_ptr`
structure of the doubly-linked list has no cycles, and so nodes
get reclaimed.

I'm not sure that the latter is actually *best* and that the *better*
one is less good than the *best*.  I just got caught up in naming
things, and the *best* one is a standard illustration of **one** use
of the `weak_ptr` type.

