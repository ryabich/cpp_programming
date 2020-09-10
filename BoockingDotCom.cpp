#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <queue>
#include <map>

using namespace std;

struct Reserve {
	int user_id;
	int room_count;
	long long time;
};

class BookingDotCom {
public:
	BookingDotCom() {}

	void Add(long long time, const string& hotel_name,
			int user_id, int room_count) {
		Delete(time, hotel_name);
		_current_time = time;
		data[hotel_name].push_back({user_id, room_count, time});
		rooms_reserved[hotel_name] += room_count;
		clients[hotel_name][user_id] += room_count;

	}

	int Clients(const string& hotel_name) {
		Delete(_current_time, hotel_name);
		return clients[hotel_name].size();
	}

	int Rooms(const string& hotel_name) {
		Delete(_current_time, hotel_name);
		return rooms_reserved[hotel_name];
	}

private:
	map<string, deque<Reserve>> data;
	map<string, long long> rooms_reserved;
	map<string, map<int, int>> clients;
	long long _current_time = 0;

	void Delete(const long long curr_time, const string& hotel_name) {
		deque<Reserve>& hotel = data[hotel_name];
		long long& rooms = rooms_reserved[hotel_name];
		map<int, int>& client = clients[hotel_name];
		while (!hotel.empty() &&
				hotel.front().time <= curr_time - 86400) {
			rooms -= hotel.front().room_count;
			if (client[hotel.front().user_id] == hotel.front().room_count)
				client.erase(hotel.front().user_id);
			else client[hotel.front().user_id] -= hotel.front().room_count;
			hotel.pop_front();
		}
	}
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  BookingDotCom manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      int page_count, user_id;
      long long _time;
      string hotel_name;
      cin >> _time >> hotel_name >> user_id >> page_count;
      manager.Add(_time, hotel_name, user_id, page_count);
    } else if (query_type == "CLIENTS") {
    	string hotel_name;
    	cin >> hotel_name;
    	cout << manager.Clients(hotel_name) << '\n';
    } else {
    	string hotel_name;
    	cin >> hotel_name;
    	cout << manager.Rooms(hotel_name) << '\n';
    }
  }

  return 0;
}
