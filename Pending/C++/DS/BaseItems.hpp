#ifndef _BASE_ITEMS_HPP
#define _BASE_ITEMS_HPP
#include <iostream >
#include <string >
template <class T>
class BaseItems {
 public:
  // destructor
  virtual ~BaseItems(){};
  // set the value of number of items n, return false if n is invalid size
  virtual bool update_number_of_items(int n) = 0;
  // return true if number of items is zero
  virtual bool empty() = 0;
  // returns the number of items
  virtual int number_of_items() = 0;
  virtual T* begin() = 0;
  virtual T* end() = 0;
  // For a BaseItems object b, the expression
  // b. front () is equivalent to *b. begin () , undefined if empty ()
  virtual T& front() = 0;
  // For a non - empty BaseItems object b, the expression
  // b. back () is equivalent to *std :: prev (b.end ()) , undefined if empty
  virtual T& back() = 0;
  // std :: out_of_range exception thrown if !( position < number_of_items ()).
  virtual T& at(int position) = 0;
  // If number_of_items () is 0 , items () may or may not return a null pointer
  // .
  virtual T* items() = 0;
  virtual const T* items() const = 0;
  // return Reference to the requested element .
  virtual T& operator[](int position) = 0;
};
#endif