#ifndef COLLECTION_H_
#define COLLECTION_H_
typedef int E;

class Collection {
public:
  virtual void add(E e) = 0;
  virtual void clear() = 0;
  virtual bool contain(E a) = 0;
  virtual bool isEmpty() = 0;
  virtual void remove(E a) = 0;
  virtual int size() = 0;
};

#endif