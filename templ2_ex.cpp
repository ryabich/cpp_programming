#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>

using namespace std;

template <typename T> vector<T> operator *(const vector<T>& a,const vector<T>& b);
template <typename Key, typename Value> map<Key, Value> operator *(const map<Key, Value>& a, const map<Key, Value>& b);
template <typename First, typename Second> pair<First, Second> operator *(const pair<First, Second>& a, const pair<First, Second>& b);
template <typename T> T Sqr(const T& obj);

template <typename T>
vector<T> operator *(const vector<T>& a,const vector<T>& b) {
	vector<T> res;
	for (const auto& elem: a) {
		res.push_back(elem * elem);
	}
	return res;
}

template <typename Key, typename Value>
map<Key, Value> operator *(const map<Key, Value>& a, const map<Key, Value>& b) {
	map<Key, Value> res;
	for (const auto& elem : a) {
		res[elem.first] = elem.second * b.at(elem.first);
	}
	return res;
}

template <typename First, typename Second>
pair<First, Second> operator *(const pair<First, Second>& a, const pair<First, Second>& b) {
	return {a.first * b.first, a.second * b.second};
}

template <typename T>
T Sqr(const T& obj) {
	return obj * obj;
}

