# OOP Design Principles  
#### Ecr23
---
## 1. Single Responsibility Principle or SRP
（单一职责原则）

>The single responsibility principle states that every module or class should have responsibility over a single part of the functionality provided by the software, and that responsibility should be entirely encapsulated by the class. All its services should be narrowly aligned with that responsibility.
---from Wikipedia

Let me take an example to explain why we need SRP. Suppose there is a class named `App`(just like an app in you smart phone), which contains many methods like `play_2048()`, `surf_the_Internet()`, `send_message()`...And imagine when we wanna play 2048, we run the `App` class, then it loads many functions like `surf_the_Internet()`, `send_message()`. However, I just want to play 2048, so it causes a huge waste of memory. What's more, when we want to update our 2048 in this class, we have to view all  codes, including methods we do not need to change like `send_message()`. It's obviously against "Encapsulation".  
Fortunately, in our daily life, functions are seperated into different apps rather than only one app in our smart phone.

> A class should have only one reason to change.
---by Robert C. Martin

![1](http://images.cnitblog.com/i/175043/201406/101805479994772.jpg)

## 2. Open/closed principle  or OCP
( 开放/封闭原则 )

>In OOP, the open/closed principle states "software entities (classes, modules, functions, etc.) should be open for extension, but closed for modification"; that is, such an entity can allow its behaviour to be extended without modifying its source code.
---from Wikipedia

When we want to update a system, we don't want to change parts that are already exists. We only want to add more parts to strengthen our system. Therefore, a good modules satisfy two properties:  
1. Open For Extension  
It's easy to understand~ All systems change during their life cycles. This must be borne in mind when developing systems expected to last longer than the first version.
2. Closed For Modification  
No one is allowed to change the codes of modules that are already exists.

It may be a a little abstract. Suppose a base class `app`, and some derived classes like `2048`, `message`...If class `app` is not an abstract class, we have to decide in based class methods when we execute some functions like `print()`. We have to decide it is a game information(like how many scores you get) or just message to print. And when we add a new app, we have to change the decide part in base to include this new app.

>Abstraction is the Key.

Abstraction is the key, but it's not the key to every system. "Strategic Closure" is needed when we design a system, and designers should decide which parts should be closed and which parts should be opened. In our human body, heart, kidney are closed but hands, penis are opened.

![2](http://images.cnitblog.com/i/175043/201406/140217336555168.jpg)

## 3. Liskov Substitution Principle or LSP  
( 里氏替换原则 )

>Substitutability is a principle in object-oriented programming. It states that, in a computer program, if S is a subtype of T, then objects of type T may be replaced with objects of type S (i.e., objects of type S may substitute objects of type T) without altering any of the desirable properties of that program (correctness, task performed, etc.).  
More formally, the Liskov substitution principle (LSP) is a particular definition of a subtyping relation, called (strong) behavioral subtyping ( 强关系子类 ).  
---from Wikipedia

In short, LSP requires us to use more [Virtual inheritance](https://en.wikipedia.org/wiki/Virtual_inheritance) instead of normal inheritance.  
Example again, we've already had a class named `rectange`, methods of which including `set_width()`, `set_height()` and we need to write a class called `square`. Of course it is a derived class from `rectange`, but problems came out: we don't need two methods because width is equal to height in square. If we add codes below, the property of project would decrease a lot especially we construct many squares.
```cpp
set_width(double x) {
  width = x;
  set_height(x);  // or height = x
}

set_height(double x) {
  height = x;
  set_width(x);  // or width = x;
}
```
It's apparently that inheritance from `rectange` to `square` is not a perfect inheritance, because not all the behaviors of `square` and `rectange` are same. When we define a "is-a" relation, we have to notice the behaviors between base class and derived class and in this example, a square is not a rectange! (what we focus on on programming is behaviors rather than the properties) In other words, `square` doesn't completely inherited from `rectange`.  

> Functions that use pointers or references to base classes must be able to use objects of derived classes without knowing it.

![3](http://images.cnitblog.com/i/175043/201406/142301060927025.jpg)  

## 4. Interface segregation principle or ISP  
( 接口分离原则 )
>The interface-segregation principle (ISP) states that no client should be forced to depend on methods it does not use.[1] ISP splits interfaces which are very large into smaller and more specific ones so that clients will only have to know about the methods that are of interest to them.
---from Wikipedia

I think the example of Xerox explains well on this principle, and it's Xerox that arose this principle after they met with problems as follows.  
>Xerox had created a new printer system that could perform a variety of tasks such as stapling and faxing. As the software grew, making modifications became more and more difficult so that even the smallest change would take a redeployment cycle of an hour.  
The design problem was that a single Job class was used by almost all of the tasks. Whenever a print job or a stapling job needed to be performed, a call was made to the Job class. This resulted in a 'fat' class with multitudes of methods specific to a variety of different clients. Because of this design, a staple job would know about all the methods of the print job, even though there was no use for them.
The solution suggested by Martin utilized what is called the Interface Segregation Principle today. Applied to the Xerox software, an interface layer between the Job class and its clients was added using the Dependency Inversion Principle. Instead of having one large Job class, a Staple Job interface or a Print Job interface was created that would be used by the Staple or Print classes, respectively, calling methods of the Job class. Therefore, one interface was created for each job type, which were all implemented by the Job class.

And I thought ISP is similar to SRP. They both require us seperate different interfaces and function. In Xerox's example, the problem was when client call some of the methods, other independent ones are also called. So we only give what clients want, others that they don't need should be hidden. The point of ISP is to specify our methods and avoid unnecessary interconnection in client class.  

![4](http://images.cnitblog.com/i/175043/201406/200019556768861.jpg)

## 5. Dependency inversion principle or DIP
( 依赖倒置原则 )
>The dependency inversion principle(DIP) refers to a specific form of decoupling software modules.  
The principle states:  
1. High-level modules should not depend on low-level modules. Both should depend on abstractions.  
2. Abstractions should not depend on details. Details should depend on abstractions.
---from Wikipedia

Maybe many people (include me) think, in OOP, high-level objects should depend on low-level objects so that our quantity of work could be reduced. In traditional layers pattern, designers thought the same as us, and as the development of OOP design, software designers found it difficult to reuse codes because they must reuse the whole system, instead of high-level layers only.  
The principle dictates that both high- and low-level objects must depend on **the same abstraction.** And it do increase the re-usability.  
So what is **Dependency inversion**? Suppose you've designed a automatic Teaching Evaluation System for SYSU and PKU. The old system includes `teaching_quality()`, `amount_of_homework()` two parts and your system could evaluate automatically.
Then we design this system as follow:
```cpp
class SYSU_TES {
public:
  teaching_quality();
};

class PKU_TES {
public:
  teaching_quality();
};

class auto_TES {
private:
  PKU_TES a = new PKU_TES();
  SYSU_TES b = new SYSU_TES();
public:
  enum school {PKU, SYSU};
  teaching_quality() {
    if (type == PKU) { a.teaching_quality(); }
    else { b.teaching_quality(); }
  }
};
```
Luckily, your system gets a good response in students and SCUT want add this system to their system. So you have to change all the system.  
This is definitely a bad design because your system (high-level) depends on low-level system. To reduce this problem, we design this system in another way
```cpp

class school {
  virtual teaching_quality() = 0;
};

class PKU_TES: school {
public:
  teaching_quality();
};

class SYSU_TES: school {
public:
  teaching_quality();
};

class auto_TES {
 private:
  school s;
  auto_TES(school s_) { s = s_; }

 public:
  teaching_quality() { s.teaching_quality(); }
};
```
In our auto_system version 2.0, high-level class depends on an abstract class, and low-level ones inherited abstract ones. It explains the superiority in Figure2 below.


![5](https://upload.wikimedia.org/wikipedia/commons/9/96/Dependency_inversion.png)

## 6. Law of Demeter or LoD
( 底米特法则 )
>
- Each unit should have only limited knowledge about other units: only units "closely" related to the current unit.
- Each unit should only talk to its friends; don't talk to strangers.
- Only talk to your immediate friends.
---from Wikipedia

This principle is easy to understand, the ppoint of which is that objects' relation do not allow transition. It means one object `A` can't get methods in `C` through `B`. Because if `A` has no direct relation with `C`, C is unnecessary for `A`. In OOP, we don't need anything that is unnecessary.

---

## Conclusion
### What is a "Bad Design"?
1. Hard to modify, for every modification influences many parts in system. **Rigidity**
2. Hard to predict, for you don't know which part could be influenced. **Fragility**
3. Hard to reuse in other systems, for it depends on many other parts in this system, or hard to decouple. **Immobility**

### Some points I learn from these principles.
1. Do not add to many function(responsibility) to one object. Remove some unnecessary interface. (SRP, ISP)
2. Do not inherit directly from low-level class. Take abstract class instead. (LoD)
3. In inheritance, the framework for judging whether it should inherit others is if they have the same behaviors. And use virtual inheritance when faced with some unsuitable inheritance. (LSP, OCP)

### Encapsulation, Polymorphism, Inheritance, Abstraction
