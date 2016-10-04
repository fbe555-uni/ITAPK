Exercise 10 - C++11 select
==========================

## Ex1 Moving and Rule of 5:

### part 1: Why is move usefull?
Obviously moving something is more efficient, since one does not have to
call constructors for all members of the new object, and destructors for
all members of the old object, but rather one just have to move the
objects which for all dynamic content only involves a pointer creation.
Many times an object might be instantiated in the righthandside of an
expression. without the move concept, this would lead to a fully uneces-
sarry copy. A very constructed, yet also clear example is the following:
```c++
class Foo{};
void main(){
    Foo f = Foo();
}
```
Obviously this could be done by omitting the assignment and just calling
the constructor on f, but for explanation purposes, this shows how
having a move assignment operation is a significantly more efficient 
approach.

### part 2: The signature
move constructors and assignment constructors use non const && rather
than const &. The && is a referance capable of dealing with rvalues, and
obviously the const modifyer is not appropriate for move, since the 
source object is left empty.

### part 3: How and when
Whenever the source will be discarded after (is an rvalue) or to gene-
ralize, it isn't needed to have to copies.

### part : Forcing usage
To force usage of move operations, std::move() has to be employed.


##Ex3 variadic templates
To implement a typelist using variadic templates, 