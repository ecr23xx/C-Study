#Tips for linked list
For most beginner in C, linked list can be annoying. Memory errors are easily caused if you don't pay 100 percent attention. Today I'd like to share with you about some tips for linked list.

## Drawing graphs
![Insert a node](https://raw.githubusercontent.com/ECer23/Pictures/master/linkedlist/assert.png)
![Erase a node](https://raw.githubusercontent.com/ECer23/Pictures/master/linkedlist/erase.png)
With the help of graphs, we can easily figure out 3 steps to insert a node or erase one. What could be noticd is the order: we should delete a node after finishing pointing the previous node-pointer, and we should point the new-allocated node-pointer before adding it to the linked list.

## Initializing
```c
node* temp = new node;
temp->data = data;
temp->prev = NULL;
temp->next = NULL;
```
It's a good habit to initialize every variable after defining them, especially for the pointer. Unless memory error might be caused because the pointer may point at some illegal memory.

## Header file
### cassert
A function called ```assert(condition)``` in the header file```<cassert>``` is a very useful tool to check if your program has memory problem. Sometimes we are attempting to free memory already freed, which will cause memory leak. Your program will be quited if the condition does not satisfy. For example:
```
assert(p != NULL);  // Your program will shut down if p is a NULL pointer.
delete p;
```
### vld.h
Before using it, you should download and install [vld](https://vld.codeplex.com/)(short for Visual Leak Detector for Visual C++). After that, what you need is only to add one line of code:```#include <vld.h>```. Then we'll see the memory leak warning in the output frame.
Ps vld cannot find memory error and it can only run foe Visual C++. If you're using *nix, you can turn to valgrind for help.
![vld warning](https://github.com/ECer23/Pictures/blob/master/linkedlist/memoryleak.PNG?raw=true)

## Valgrind
it's definetly the best memory check app I've ever used. You only need to type-in
```
sudo valgrind -q ./yourfile  // valgrind runs quietly if there's no memory errors in your programs
sudo valgrind -che
```
