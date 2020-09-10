#include <deque>
#include <string>
#include <iostream>

using namespace std;

void Function(deque<string>& obj, const char& operation,
		const int num, bool is_need) {
	if (!is_need) {
		obj.push_back(" ");
		string s = "";
		s += operation;
		obj.push_back(s);
		obj.push_back(" " + to_string(num));
		return;
	}
	obj.push_front("(");
	obj.push_back(") ");
	string s = "";
	s += operation;
	obj.push_back(s);
	obj.push_back(" " + to_string(num));
}

int main() {
	int first, count;
	cin >> first >> count;
	deque<string> data;
	data.push_back(to_string(first));
	bool is_need = false;;
	for (size_t i = 0; i < count; ++i) {
		char operation;
		int num;
		cin >> operation >> num;
		if (operation == '+' || operation == '-') {
			Function(data, operation, num, false);
			is_need = true;
		} else {
			Function(data, operation, num, is_need);
			is_need = false;
		}
	}
	for (const string elem : data) {
		cout << elem;
	}
	return 0;
}
