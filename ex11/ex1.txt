Lecture 1: C vs. C++
====================

##Agenda
 * Encapsulation
 * Polymorphism
 * Namespaces
 * Generic programming
 * Meta programming

##Encapsulation
Using C++ one has access to real classes with data encapsulation.
No overhead for non polymorphic classes on almost any compiler/platform
Helps programmers avoid mistakes

##Polymorphism
Allows better code reuse and a better match between code and concept.
Some overhead. Compiler dependent

##Namespaces
C++ allows the programmer to use several seperate namespaces.
both explicitly, and implicitly through class encapsulation
Improves code readability significantly
Avoid name clashes when integrating several parts of code

##Generic programming
Templetization allows for even more code reuse, and improves utility of imple-
mented libraries.
No runtime overhead, but can lead to surprisingly large code size due to similar
code being instantiated seperately for every type.

##Meta programming
Allows moving some of the workload to the compiler, making complicated code
compile to simpler executable code.
Also allows catching more errors at compile time, which is good for embedded
systems with their high reprogramming penalty and limited posibility for post
deployment updates

Lecture 2: Embedded C++ pitfalls
================================

##Agenda
 * Overhead
 * Exceptions
 * Platform specific compiler maturity

##Overhead
While there's not necessarily any significant overhead caused by using C++, one
can easily cause a lot of overhead, not thinking about how the C++ features are
utilized.
Firstly templates can lead to significant code size overhead, since the code is
instantiated seperately for every used type.
Polymorphic classes have some runtime overhead, calling virtual functions, and
RTTI must cause some memory overhead as well.

##Exceptions
While exception are not necessarily a bad choice for embedded systems, they do
have some issues worth considering.
Firstly, the execution of exception handling is not currently predictable enough
for timing critical systems.
Secondly, Exceptions cause overhead even when not used, which might be more than
whats justifiable for a given system.
Thirdly, an exceptional condition justifying exception use, might need a full
reboot for safety reasons in many embedded applications involving real-world
hardware interaction, nullifying all exception benefits.

##Platform specific compiler maturity
While almost all embedded platforms have a well matured C compiler, the C++ com-
pilers available for embedded platforms vary in their ability to do implicit in-
lining, quality of memory optimizations, and support for advanced features such
as meta programming. Generally one has to test on the specific platform compiler
combination being used to get a good idea of the actual overheads involved.
