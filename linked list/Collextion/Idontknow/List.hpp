#ifndef LIST_H_
#define LIST_H_
#include "Collection.hpp"

class List: virtual public Collection {
public:
  virtual E& operator[](int index) = 0;
  virtual E& get(int index) = 0;
  virtual int indexOf(E x) = 0;
  virtual void sort() = 0;
}; 


#endif