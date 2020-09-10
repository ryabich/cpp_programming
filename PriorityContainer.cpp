#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <queue>
#include <map>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = int;

  PriorityCollection() = default;
  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
	  identifiers[counter] = make_pair(move(object), 0);
	  priorities[0].insert(counter++);
	  return counter-1;
  }
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
	  while (range_begin != range_end) {
		  identifiers[counter] = make_pair(move(*range_begin), 0);
		  range_begin++;
		  priorities[0].insert(counter);
		  *ids_begin = counter;
		  counter++;
		  ids_begin++;
	  }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
	  if (identifiers.find(id) != identifiers.end()) return true;
	  return false;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
	  return identifiers.at(id).first;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
	  int priority = identifiers[id].second;
	  priorities[priority].erase(id);
	  if (priorities[priority].empty()) priorities.erase(priority);
	  priorities[++priority].insert(id);
	  identifiers[id].second++;
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
	  auto max_map_it = prev(priorities.end());
	  auto max_set_it = prev((max_map_it->second).end());
	  int value = max_map_it->first;
	  const T& elem = identifiers.at(*max_set_it).first;
	  return {elem, value};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
	  auto max_map_it = prev(priorities.end());
	  auto max_set_it = prev((max_map_it->second).end());
	  int id = *max_set_it;
	  int value = (*max_map_it).first;
	  priorities[value].erase(max_set_it);
	  if (priorities[value].empty()) priorities.erase(value);
	  T elem = move(identifiers[id].first);
	  identifiers.erase(id);
	  return make_pair(move(elem), value);
  }

private:
  int counter = 0;
  map<int, pair<T, int>> identifiers;
  map<int, set<int>> priorities;
};


class StringNonCopyable : public string {
public:
  using string::string;  // РџРѕР·РІРѕР»СЏРµС‚ РёСЃРїРѕР»СЊР·РѕРІР°С‚СЊ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂС‹ СЃС‚СЂРѕРєРё
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);

  auto elem = strings.GetMax();
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }

}


int main() {
  TestRunner tr;
  TestNoCopy();
  RUN_TEST(tr, TestNoCopy);
  return 0;
}

