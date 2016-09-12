# Polymorphism(多态) and Binding(绑定)

---

### Compile-time polymorphism(编译时多态)
```cpp
int abs(int x);
float abs(float x;)
```
上面两个函数在C++中是可以编译通过的，C++编译时会帮我们把两个重名但是返回值和参数列表不同的函数换一个名字，进行函数重载。（我只是方便理解这样换，其实换出来是人看不懂的一坨），变成`abs_int(int)` 和 `abs_float(float)`两个函数。然后在程序运行时根据参数列表、返回值类型来决定调用哪一个函数。这个叫做编译时多态。
```cpp
float x = 0.1;
int y = 1;
std::cout << x << std::endl;
std::cout << y << std::endl;
```
不要以为上面的两个cout名字不一样，其实他们是一样的。实现方式就是用模板（泛型编程）。而这种方式是当程序编译到时将模板实例化成不同的函数。这种也是编译时多态。
编译时多态的核心是函数在编译时已经绑定(binding)了那一种重载，而运行时多态是指程序运行到此时系统自动判断应该调用哪个函数。

### Run-time polymorphism(运行时多态)
```cpp
class A {
 public:
  virtual void print() { std::cout << "I'm A" << std::endl; }
};
class B : public A {
 public:
  void print() { std::cout << "I'm B" << std::endl; }
};
class C : public A {
 public:
  void print() { std::cout << "I'm C" << std::endl; }
};
void Print(A a) { a.print(); }
int main() {
  B b;
  C c;
  Print(b);
  Print(c);
}
```
上面一段程序输出的结果是两段`I'm A`，原因是`Print()`函数中参数列表是`A`， 所以子类都“回退”到了父类。可是我们主函数的意图是想要输出`I'm B`和`I'm C`，这个时候，我们就要用到运行时多态。我们把`Print(A a)`改写一下，变成`Print(A& a)`，其余不变，这个时候再运行就成了我们想要的`I'm B`和`I'm C`。
为什么用了指针或引用之后就不一样了呢？C++中，对于一个对象来说无论有多少个指针指向它，这些个指针所指的都是同一个对象。(即使你用一个void的指针指向一个对象也是这样的)同理对于引用也一样。
这里的深层的意义在于：子类型的信息本来就在它本身中存在，所以我们用一个基类的指针来指出它，这个子类型的信息也会被找到，同理引用也是一样的。C++正是利用了指针的这一特性。来做到动态多态的。而这个特性，又被称为动态绑定。

### Static biding & Dynamic binding
静态类型：对象在声明时采用的类型，在编译期既已确定；  
动态类型：通常是指一个指针或引用目前所指对象的类型，是在运行期决定的；  
静态绑定：绑定的是静态类型，所对应的函数或属性依赖于对象的静态类型，发生在编译期；  
动态绑定：绑定的是动态类型，所对应的函数或属性依赖于对象的动态类型，发生在运行期；  
来看一段代码
```cpp
A* pb = new B();
A* pc = new C();
A* pa = pc;
pb->print();
pa->print();
```

假设上面的基类`A`中的print函数不是一个虚函数，那么这段程序的输出会是两个`I'm A`。原因在于C++的 **继承体系中只有虚函数使用的是动态绑定，其他的全部是静态绑定** 。所以虽然基类指针可以指向派生类对象，但是他的静态类型是A，动态类型虽然可以变成B，但是`pa->print()`已经和类型A在编译时绑定，所以无法实现运行时多态。如果要实现运行时多态，必须使用虚函数。
>如果基类A中的`print()`不是virtual函数，那么无论pa、pb、pc指向哪个子类对象，对`print()`的调用都是在定义pa、pb、pc时的静态类型决定，早已在编译期确定了。同样的空指针也能够直接调用no-virtual函数而不报错(这也说明一定要做空指针检查啊！)，因此静态绑定不能实现多态；如果`print()`是虚函数，那所有的调用都要等到运行时根据其指向对象的类型才能确定，比起静态绑定自然是要有性能损失的，但是却能实现多态特性；
---from [lizhenghn](http://www.cnblogs.com/lizhenghn/p/3657717.html)

总结一下：  
对象的动态类型可以更改，但是静态类型无法更改；  
要想实现动态，必须使用动态绑定；  
在继承体系中只有虚函数使用的是动态绑定，其他的全部是静态绑定；  