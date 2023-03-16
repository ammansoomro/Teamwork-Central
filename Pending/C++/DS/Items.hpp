//
// Name : Your First Name & Last Name
// SSID : Student ID Number
// Assignment #: 2
// Submission Date : DATE_SUBMITTED
//
#ifndef _ITEMS_HPP
#define _ITEMS_HPP
#include <iostream>
#include "BaseItems.hpp"


template <class T>
class Items : public BaseItems<T> {
 public:
  Items<T>() : _number_of_items(0), _items(nullptr) {}
  Items<T>(int n, std::initializer_list<T> il);
  Items<T>(const Items<T>& items);
  ~Items<T>();
  bool update_number_of_items(int n);
	bool empty();
	int number_of_items();
	T* begin();
	T* end();
	T& front();
	T& back();
	T& at(int position);
	T* items();
	const T* items() const;
	T& operator[](int position);
 private:
  int _number_of_items = 0;
  T* _items = nullptr;
};

template <class T>
Items<T>::Items(int n, std::initializer_list<T> il) {
	_number_of_items = n;
	_items = new T[n];
	int i = 0;
	for (auto it = il.begin(); it != il.end(); ++it) {
		_items[i] = *it;
		i++;
	}
}

template <class T>
Items<T>::Items(const Items<T>& items) {
	_number_of_items = items._number_of_items;
	_items = new T[_number_of_items];
	for (int i = 0; i < _number_of_items; i++) {
		_items[i] = items._items[i];
	}
}

template <class T>
Items<T>::~Items() {
	delete[] _items;
}

template <class T>
bool Items<T>::update_number_of_items(int n) {
	if (n < 0) {
		return false;
	}
	T* temp = new T[n];
	for (int i = 0; i < n; i++) {
		temp[i] = _items[i];
	}
	delete[] _items;
	_items = temp;
	_number_of_items = n;
	return true;
}

template <class T>
bool Items<T>::empty() {
	return _number_of_items == 0;
}

template <class T>
int Items<T>::number_of_items() {
	return _number_of_items;
}

template <class T>
T* Items<T>::begin() {
	return _items;
}

template <class T>
T* Items<T>::end() {
	return _items + _number_of_items;
}

template <class T>
T& Items<T>::front() {
	return _items[0];
}

template <class T>
T& Items<T>::back() {
	return _items[_number_of_items - 1];
}

template <class T>
T& Items<T>::at(int position) {
	if (position < 0 || position >= _number_of_items) {
		throw std::out_of_range("Out of range");
	}
	return _items[position];
}

template <class T>
T* Items<T>::items() {
	return _items;
}

template <class T>
const T* Items<T>::items() const {
	return _items;
}

template <class T>
T& Items<T>::operator[](int position) {
	return _items[position];
}

#endif