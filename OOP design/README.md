# OOP Design
#### Ecr23
---

## What is OOP?
>Object-oriented programming (OOP) is a programming paradigm based on the concept of "objects", which may contain data, in the form of fields, often known as attributes; and code, in the form of procedures, often known as methods.  
--from Wikipedia  

As we all know, there are 3 main features in OOP: [Encapsulation](https://en.wikipedia.org/wiki/Object-oriented_programming#Encapsulation), [Polymorphism]( https://en.wikipedia.org/wiki/Object-oriented_programming#Polymorphism), [Inheritance](https://en.wikipedia.org/wiki/Object-oriented_programming#Composition.2C_inheritance.2C_and_delegation). In a nutshell, OOP programming tries to seperate the programming process into different indepedent parts. And these parts can be used by others for every part (or boject) was defined in an indepedent class.      

---

## OOP Design Principles  

### 1. Single Responsibility Principle or SRP
（单一职责原则）

>The single responsibility principle states that every module or class should have responsibility over a single part of the functionality provided by the software, and that responsibility should be entirely encapsulated by the class. All its services should be narrowly aligned with that responsibility.

Let me take an example to explain why we need SRP. Suppose there is a class named `App`(just like an app in you smart phone), which contains many methods like `play_2048()`, `surf_the_Internet()`, `send_message()`...And imagine when we wanna play 2048, we run the `App` class, then it loads many functions like `surf_the_Internet()`, `send_message()`. However, I just want to play 2048, so it causes a huge waste of memory. What's more, when we want to update our 2048 in this class, we have to view all  codes, including methods we do not need to change like `send_message()`. It's obviously against "Encapsulation".  
Fortunately, in our daily life, functions are seperated into different apps rather than only one app in our smart phone.

> A class should have only one reason to change.by Robert C. Martin

![1](http://images.cnitblog.com/i/175043/201406/101805479994772.jpg)

### 2. Open/closed principle  
( 开放/封闭原则 )

>In OOP, the open/closed principle states "software entities (classes, modules, functions, etc.) should be open for extension, but closed for modification"; that is, such an entity can allow its behaviour to be extended without modifying its source code.

When we want to update a system, we don't want to change parts that are already exists. We only want to add more parts to strengten our system. Therefore, a good modules satisfy two properties:  
1. Open For Extension  
It's easy to understand~ All systems change during their life cycles. This must be borne in mind when developing systems expected to last longer than the first version.
2. Closed For Modification  
No one is allowed to change the codes of modules that are already exists.

It may be a a little abstract. Suppose a base class `app`, and some derived classes like `2048`, `message`...If class `app` is not an abstract class, we have to decide in based class methods when we execute some functions like `print()`. We have to decide it is a game information(like how many scores you get) or just message to print. And when we add a new app, we have to change the decide part to contain this new app.

>Abstraction is the Key.

Abstraction is the key, but it's not the key to every system. "Strategic Closure" is needed when we desgin a system, and desginers should decide which parts should be closed and which parts should be opened. In our human body, heart, kidney are closed but hands, penis are opened.

![2](http://images.cnitblog.com/i/175043/201406/140217336555168.jpg)

### 3. Liskov Substitution Principle or LSP  
( 里氏替换原则 )

>Substitutability is a principle in object-oriented programming. It states that, in a computer program, if S is a subtype of T, then objects of type T may be replaced with objects of type S (i.e., objects of type S may substitute objects of type T) without altering any of the desirable properties of that program (correctness, task performed, etc.).  
More formally, the Liskov substitution principle (LSP) is a particular definition of a subtyping relation, called (strong) behavioral subtyping ( 强关系子类 ).  

In short, LSP requiers us to use more [Virtual inheritance](https://en.wikipedia.org/wiki/Virtual_inheritance) instead of normal inheritance.  
Example again, we've already had a class named `rectange`, methods of which includes `set_width()`, `set_height()` and we need to write a class called `square`. Of course it is a derived class from `rectange`, but problems came out: we don't need two methods because width is equal to height in square. If we add codes below, the property of project would decrease a lot especially we construct many squares.
```cpp
if set_width()
  set_height();
if set_height()
  set_width();
```
It's apparently that inheritance from `rectange` to `square` is not a perfect inheritance, because not all the behaviors of `square` and `rectange` are same. When we define a "is-a" relation, we have to notice the behaviors between base class and derived class and in this example, a square is not a rectange! (what we focus on on programming is behaviors rather than the properties) In other words, `square` doesn't completely inherited from `rectange`.  
LSP is a

> Functions that use pointers or references to base classes must be able to use objects of derived classes without knowing it.

![3](http://images.cnitblog.com/i/175043/201406/142301060927025.jpg)
