#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        pages(MAX_PAGE_COUNT_ + 1) {} // O(n)

  void Read(int user_id, int page_count) {
    if (user_page_counts_[user_id] == 0) {
      _size++;
    } else {
    	pages[user_page_counts_[user_id]].erase(user_id);
    }
    user_page_counts_[user_id] = page_count;
    pages[page_count].insert(user_id);
    // O(n)
  }

  double Cheer(int user_id) const {
    if (user_page_counts_[user_id] == 0) {
      return 0;
    }
    if (_size == 1) {
      return 1;
    }
    int sum = 0;
    for (int i = 0; i < user_page_counts_[user_id]; ++i)
    	sum += pages[i].size();
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return (sum) * 1.0 / (_size - 1);
    // O(n)
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_PAGE_COUNT_ = 1'000;
  static const int MAX_USER_COUNT_ = 100'000;

  vector<set<int>> pages;
  vector<int> user_page_counts_;
  int _size = 0;// позиции в векторе sorted_users_
  // O(1)
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
