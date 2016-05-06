# C++的异常抛出和匹配机制

1. 当一个错误信息被throw出之后，程序会一直和这个错误进行匹配（catch），如果没有匹配成功（类型恰好匹配或者父类捕获子类），则终止当前函数的运行。C++特别加入了try块表（特殊的数据结构）来记录错误抛出的位置。
  并且父类捕获应当写在子类之后。
  `catch(...) {}`表示可以匹配任何类型的异常，避免强制退出的出现。必须加在最后。
2. 函数后可以添加异常类型列表
```cpp
void fun1();             
// catch all types of throw
void fun2() throw();     
// catch no types of throw
void fun3() throw(int)   
// only catch int throw
```  
3. 当cacth的是一个引用时，多态技术可以自动匹配对象的类型
```cpp
catch(Myexception &e) {  
// use '&' change e itself instead of its copy
e.setMessage("new");
throw;
// throw the preview error
}
catch(Myexception e) {
e.setMessage("new");
throw;
// throw the preview error, which hasn't been changed
}
```
4. 栈展开：沿着函数链向上搜索异常的过程。  
但是如果构造函数进行到一半，或者在析构函数调用之前，出现故障抛出后栈展开，就会产生内存垃圾。解决方案是`智能指针`和`auto_ptr`，但后者只能解决指针问题。

5. 标准库异常类`<stdexcept>`
```cpp
class exception {
public:
  exception () throw();
  exception (const exception&) throw();
  exception& operator= (const exception&) throw();
  virtual ~exception() throw();
  // Returns a null terminated character sequence that may be used to identify the exception.The particular representation pointed by the returned value is implementation-defined.As a virtual function, derived classes may redefine this function so that specific values are returned.
  virtual const char* what() const throw();
}
```
![类图](http://eden.sysu.edu.cn/media/[2014]%20SE-123%20by%20Dr.%20Wan/img/2014%20Lecture%20Notes%20on%20C++%20-%209%20-%20Exceptiong%20Handling%20/page-34.jpg)
