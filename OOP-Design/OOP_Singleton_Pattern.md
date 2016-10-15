# OOP Singleton pattern
#### Ecr23

---

## Singleton (单例模式)
>the singleton pattern is a design pattern that restricts the instantiation of a class to one object. This is useful when exactly one object is needed to coordinate actions across the system.
--- from Wikipedia

In some situations, a certain type of data needs to be available to all other objects in the application. In most cases, this type of data is also unique in the system. For example, a user interface can have only one mouse pointer that all applications must access. Likewise, an enterprise solution may interface with a single-gateway object that manages the connection to a specific legacy system.  

### Solution
1. Making the class create a single instance of itself.  
2. Allowing other objects to access this instance through a class method that returns a reference to the instance. A class method is globally accessible.  
3. Declaring the class constructor as private so that no other object can create a new instance.  

### Benefits
1. Instance control. Singleton prevents other objects from instantiating their own copies of the Singleton object, ensuring that all objects access the single instance.  
2. Flexibility. Because the class controls the instantiation process, the class has the flexibility to change the instantiation process.  

### Liabilities
1. Overhead. Although the amount is minuscule, there is some overhead involved in checking whether an instance of the class already exists every time an object requests a reference. This problem can be overcome by using static initialization as described in Implementing Singleton in C#.
2. Possible development confusion. When using a singleton object (especially one defined in a class library), developers must remember that they cannot use the new keyword to instantiate the object. Because application developers may not have access to the library source code, they may be surprised to find that they cannot instantiate this class directly.
3. Object lifetime. Singleton does not address the issue of deleting the single object. In languages that provide memory management (for example, languages based on the .NET Framework), only the Singleton class could cause the instance to be deallocated because it holds a private reference to the instance. In languages, such as C++, other classes could delete the object instance, but doing so would lead to a dangling reference inside the Singleton class.
---from MSDN

### Lazy initialization
Because we only need to construct only one object, so the constructor must be private, or client could construct many objects.
But if the constructor is private, how do we reach it? the answer is to use a static pointer. We can only reach the constructor for once (when the pointer is NULL).
```cpp
class CSingleton {
 private:  
    // private constructor
    CSingleton() {}
    // avoid being copying
    CSingleton(const CSingleton&);
  	CSingleton& operator=(const CSingleton&);
    static CSingleton* m_pInstance;
 public:
    static CSingleton* getInstance() {  
        if (m_pInstance == NULL)
            m_pInstance = new CSingleton();  // only construct for once
        return m_pInstance;
    }
};
```
Version 1.0 will cause memory leak because we didn't deallocate the object. To deallocate it, we can choose not to use `new` to avoid memory destroy.
```cpp
static CSingleton* getInstance() {  
    if (m_pInstance == NULL) {
      static CSingleton static_instance.
      m_pInstance = &static_instance;  // only construct for once
    }
    return m_pInstance;
}
```
Or we can creat a class to destroy instance.
```cpp
// its only work is to free the memory
class CGarbo {
 public:
  ~CGarbo() {
    if (CSingleton::m_pInstance) delete CSingleton::m_pInstance;
  }
};
static CGarbo Garbo;  // when the program end, system will call Garbo's deallocator automatically.
```

This version is simple and clean, but it's at the expense of potentially lower concurrency in a multithreaded environment. And this may be a safer version:

```cpp
Singleton* getInstance() {
  if (instance == NULL) {
    lock();
    if (instance == NULL) {
      instance = new Singleton();
    }
    unlock();
  }
  return instance;
};

```
### Eager initialization
If the program will always need an instance, or if the cost of creating the instance is not too large in terms of time/resources, the programmer can switch to eager initialization, which always creates an instance:
```cpp
class CSingleton {
private:
  static CSingleton* m_pInstance = new CSingleton();
  CSingleton () {}
  // avoid being copying
  CSingleton(const CSingleton&);
	CSingleton& operator=(const CSingleton&);

public:
  CSingleton* getInstance() { return m_pInstance; }
};
```

### External links
[Singleton pattern --  Wikipedia](https://en.wikipedia.org/wiki/Singleton_pattern)  
[Singleton -- MSDN](https://msdn.microsoft.com/zh-cn/library/ff650849.aspx)  
[How should singleton be used -- stackoverflow](http://stackoverflow.com/questions/86582/singleton-how-should-it-be-used)  
[C++ Singleton pattern -- stackoverflow](http://stackoverflow.com/questions/1008019/c-singleton-design-pattern)  
