#pragma once

#include <cstdlib>
#include <algorithm>

using namespace std;
// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() {}

  explicit SimpleVector(size_t size) {
	  Vector = new T[size];
	  _size = size;
	  _capacity = size;
  }

  SimpleVector(const SimpleVector& other) :
	  Vector(new T[other.Capacity()]),
	  _size(other.Size()),
	  _capacity(other.Capacity()) {
	  copy(other.begin(), other.end(), begin());
  }

  void operator =(const SimpleVector& other) {
	  if (_size == 1) delete Vector;
	  else delete[] Vector;
	  Vector = new T[other.Capacity()];
	  _size = other.Size();
	  _capacity = other.Capacity();
	  copy(other.begin(), other.end(), (*this).begin());
  }

  ~SimpleVector() {
	  if (_size == 1) delete Vector;
	  else delete[] Vector;
  }

  T& operator[](size_t index) {
	  return *(Vector+index);
  }

  T* begin() {
	  return Vector;
  }

  T* end() {
	return Vector+_size;
  }

  const T* begin() const {
  	  return Vector;
    }

  const T* end() const {
  	  return Vector+_size;
  }

  size_t Size() const {
	  return _size;
  }
  size_t Capacity() const {
	  return _capacity;
  }
  void PushBack(const T& value) {
	  if (_size == 0) {
		  Vector = new T(value);
		  _size = 1;
		  _capacity = 1;
		  return;
	  }

	  if (_size == _capacity) {
		  T* dublicate = new T[_size * 2];
		  for (size_t i = 0; i < _size; ++i) {
			  *(dublicate+i) = *(Vector+i);
		  }
		  *(dublicate+_size) = value;
		  _capacity = _size*2;
		  if (_size == 1) delete Vector;
		  else delete[] Vector;
		  Vector = dublicate;
		  _size++;
		  return;
	  }

	  *(Vector+_size) = value;
	  _size++;
  }

private:
  T* Vector = nullptr;
  size_t _size = 0;
  size_t _capacity = 0;
};
