#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
bool operator ==(const set<Char<String>>& lhs,
		const set<Char<String>>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	auto it2 = rhs.begin();
	for (auto it1 = lhs.begin(); it1 != lhs.end(); ++it1) {
		if (*it1 != *it2++) return false;
	}
	return true;
}

template <typename String>
bool operator !=(const set<Char<String>>& lhs,
		const set<Char<String>>& rhs) {
	return !(lhs == rhs);
}

template <typename String>
bool operator <(const set<Char<String>>& lhs,
		const set<Char<String>>& rhs) {
	if (lhs.size() < rhs.size()) return true;
	else if (lhs.size() > rhs.size()) return false;
	else {
		auto it2 = rhs.begin();
		for (auto it1 = lhs.begin(); it1 != lhs.end(); ++it1) {
			if (*it1 < *it2) return true;
			else if (*it1 > *it2) return false;
			it2++;
		}
	}
	return true;
}

template <typename String>
bool operator >(const set<Char<String>>& lhs,
		const set<Char<String>>& rhs) {
	if (lhs.size() < rhs.size()) return false;
	else if (lhs.size() > rhs.size()) return true;
	else {
		auto it2 = rhs.begin();
		for (auto it1 = lhs.begin(); it1 != lhs.end(); ++it1) {
			if (*it1 < *it2) return false;
			else if (*it1 > *it2) return true;
			it2++;
		}
	}
	return false;
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
	map<set<Char<String>>, vector<String>> data;
	for (auto it = strings.begin(); it != strings.end();) {
		set<Char<String>> word;
		for (auto& elem : *it) {
			word.insert(elem);
		}
		auto find_word = data.find(word);
		if (find_word != data.end()) {
			auto prev = it++;
			(*find_word).second.push_back(move(*prev));
		} else {
			auto prev = it++;
			data[move(word)].push_back(move(*prev));
		}
	}
	vector<Group<String>> res(data.size());
	size_t counter = 0;
	for (auto it = data.begin(); it != data.end(); ++it) {
		for (auto& elem : it->second) {
			res[counter].push_back(move(elem));
		}
		counter++;
	}
	return res;
}


void TestGroupingABC() {
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), static_cast<size_t>(2));
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), static_cast<size_t>(4));
  sort(begin(groups), end(groups));  // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);
  return 0;
};

