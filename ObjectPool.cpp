#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
	  if (!deleted.empty()) {
		  T* object = deleted.front();
		  deleted.pop();
		  current.insert(object);
		  return object;
	  }
	  T* object = new T;
	  current.insert(object);
	  return object;
  }

  T* TryAllocate() {
	  if (!deleted.empty()) {
		  T* object = deleted.front();
		  deleted.pop();
		  current.insert(object);
		  return object;
	  } else return nullptr;
  }

  void Deallocate(T* object) {
	  auto it = current.find(object);
	  if (it == current.end())
		  throw invalid_argument("");
	  deleted.push(*it);
	  current.erase(object);
  }

  ~ObjectPool() {
	  while (!current.empty()) {
		  delete *(current.begin());
		  current.erase(current.begin());
	  }
	  while (!deleted.empty()) {
		  delete deleted.front();
		  deleted.pop();
	  }
  }

private:
  set<T*> current;
  queue<T*> deleted;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
