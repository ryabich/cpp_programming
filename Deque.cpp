#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
public:
	Deque() {}

	bool Empty() const {
		if (_size == 0) return true;
		return false;
	}

	size_t Size() const {
		return _size;
	}

	T& operator [](size_t i) {
		if (i < front.size()) return front[front.size()-1-i];
		return back[i-front.size()];
	}

	const T& operator [](size_t i) const {
		if (i < front.size()) return front[front.size()-1-i];
		return back[i-front.size()];
	}

	T& At(size_t i) {
		if (i >= _size) throw out_of_range("invalid index");
		else if (i < front.size()) return front[front.size()-1-i];
		return back[i-front.size()];
	}

	const T& At(size_t i) const {
		if (i >= _size) throw out_of_range("invalid index");
		else if (i < front.size()) return front[front.size()-1-i];
		return back[i-front.size()];
	}

	T& Front() {
		if (front.size() == 0) return back[0];
		return front[front.size() - 1];
	}

	const T& Front() const {
		if (front.size() == 0) return back[0];
		return front[front.size()-1];
	}

	T& Back() {
		if (back.size() == 0) return front[0];
		return back[back.size()-1];
	}

	const T& Back() const {
		if (back.size() == 0) return front[0];
		return back[back.size()-1];
	}

	void PushBack(T i) {
		_size++;
		back.push_back(i);
	}

	void PushFront(T i) {
		_size++;
		front.push_back(i);
	}

private:
	size_t _size = 0;
	vector<T> back;
	vector<T> front;
};
