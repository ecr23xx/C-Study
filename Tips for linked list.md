#Tips for linked list
For many beginners in C, linked list can be annoying. Memory errors are easily caused if you don't pay 100 percent attention. Today I'd like to share with you about some tips for linked list. I'll also recommend some efficient tools and their usage.  

## 1. Drawing graphs
![Insert a node](https://raw.githubusercontent.com/ECer23/Pictures/master/linkedlist/assert.png)
![Erase a node](https://raw.githubusercontent.com/ECer23/Pictures/master/linkedlist/erase.png)  
With the help of graphs, we can easily figure out 3 steps to insert a node or erase one. What could be noticed is the order: we should delete a node after finishing pointing the previous node pointer, and we should point the newly allocated node-pointer before adding it to the linked list.  
## 2. Initializing
```c
node* temp = new node;
temp->data = data;
temp->prev = NULL;
temp->next = NULL;
```  
It's a good habit to initialize every variable after defining them, especially for the pointer. Unless memory error might be caused because the pointer may point at some illegal memory.  

## 3. Header file
### - cassert
A function called ```assert(condition)``` in the header file```<cassert>``` is a very useful tool to check if your program has any memory leak problems. Sometimes we are attempting to free memory already freed, which will cause memory leaks. Your program will be quit if the condition does not satisfy. For example:
```
assert(p != NULL);  // Your program will shut down if p is a NULL pointer.
delete p;
```
### - vld.h
Before using it, you should download and install [vld](https://vld.codeplex.com/)(short for Visual Leak Detector for Visual C++). After that, what you need is only to add one line of code:```#include <vld.h>```. Then we'll see the memory leak warning in the output Let me take this one an example. It points out in list.cpp, the operator new() on line 147, line 241 has some memory leak problem. Apperatantly, the reason is we do not delete the memory we allocated. In this example, vld didn't point out where we should add the delete function. It only found the source of the memory leak is the operator new().
![vld warning](https://github.com/ECer23/Pictures/blob/master/linkedlist/memoryleak.PNG?raw=true)  
Ps. vld cannot find memory error and it can only run foe Visual C++. If you're using *nix, you can turn to valgrind for help.

## 4. Valgrind
Valgrind is definitely the best memory check app I've ever used. You only need to type some instructions on Linux(just the way you compile your program). The format is ```valgrind [valgrind-options] your-prog [your-prog options]``` And here are some examples. Detailed information is on its official website.[Valgrind Home](http://valgrind.org/)
```
$ gcc -Wall -o list list.c 
$ valgrind --tool=memcheck ./list
$ valgrind -q ./list  // valgrind runs quietly if there's no memory errors in your programs
```
![valgrind warning](https://github.com/ECer23/Pictures/blob/master/linkedlist/lost.PNG?raw=true)
There're some types of output format.  
### - Invalid read or write of memory  
Maybe you are trying to access an element of an array of which the index is out of range. And it's also possible that your pointer points to some unallocated memory. To solve such kind of problem, you can enlarge your array. If it didn't work, maybe you should check your looping statements.

### - Use of uninitialised value  
REMEMBER TO INITIALIZE!!! Because you don't know whether you have initialised it when you use it, and we often take it for granted that every variable we use has been initialised.

### - Memory leak.  
Mostly, the reason is that some memory becomes unreachable.
Sometimes it occurred when you're using pointers.
```p = p->next;```  
If you did nothing to remain p, then the block stored p was lost because no pointer pointed to it. It became unreachable.
When you overload the operator"=" or write a function like "assign()", you'd better care for memory leak for when you are assigning some variables or array, you must guarantee the values stored in them have been cleared! And if you're unfortunate to cause such problem, Valgrind won't point out the exact line where you miss it. It only tells you there's something wrong with your "operator new()".

### - Mismatched free() / delete / delete []  
It means  
1. you're trying to delete/free some memory which has been deleted/free.  
2. you're trying to delete memory allocated by ```malloc()```, or to free memory allocated by ```new[]```.  
It's easy to handle such kind of problem.  

###Please trust vld/valgrind and mostly it's your fault!!  
