ITAPK Exercise for Lecture 4 - Exceptions
=========================================

Exercise 1 Safety Guarantees
----------------------------
### Exercise 1.1 Code
Here follows a brief consideration of each of the snippets individually

#### Snippet 1
The class provides a no-throw guarantee, given that it employs
nothing that has any error handling. The class doesn't uphold
the guarantee fully, in the sense that there's no error hand-
ling on the index given (an out of bounds index leads to a
seg-fault or just bad data).

#### Snippet 2
The class in it's current form fails to provide even the basic
guarantee, since the call to copy can throw an exception, in
which case the newData memory will be leaked. If the class had
a try catch clause, calling delete on newData and re-throwing,
the class would provide the strong guarantee since a full
rollback had been provided.
The class has another fault, since if instantiated with 0
capacity, the \*=2 operation fails to expand the capacity and
the subsequent operation goes out of bounds. To fix this, the
class should just add one in the case when capacity == 0.

#### Snippet 3
Both the constructors already provide the strong guarantee since if the new call throws, nothing has been done yet, and thus no rollback is needed.
The assignment operator currently provides the basic guarantee, since no memory gets allocated if the call to new throws. The strong guarantee is not fulfilled since the old data is deleted before the call to new, and thus is lost if it throws. To upgrade this, the function could start out creating the new memory, then using strcpy to copy over the new data, then using swap on the new and the old memory, and calling delete on the new (which now holds the old data). This way if the call to new throws, the old data is intact.
