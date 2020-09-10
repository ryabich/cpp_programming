#include <set>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <exception>
using namespace std;

class Date {
private:
	int year;
	int month;
	int day;

public:
	Date() {}

	Date (int _year, int _month, int _day) {
		year = _year;
		month = _month;
		day = _day;
	}

	int GetYear() const {
		return year;
	}

	int GetMonth() const {
		return month;
	}

	int GetDay() const {
		return day;
	}
};

bool operator <(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear()) return true;
	else if (lhs.GetYear() > rhs.GetYear()) return false;
	else {
		if (lhs.GetMonth() < rhs.GetMonth()) return true;
		else if (lhs.GetMonth() > rhs.GetMonth()) return false;
		else {
			if (lhs.GetDay() < rhs.GetDay()) return true;
			else if (lhs.GetDay() > rhs.GetDay()) return false;
			else return false;
		}
	}
}

bool operator >(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() > rhs.GetYear()) return true;
	else if (lhs.GetYear() < rhs.GetYear()) return false;
	else {
		if (lhs.GetMonth() > rhs.GetMonth()) return true;
		else if (lhs.GetMonth() < rhs.GetMonth()) return false;
		else {
			if (lhs.GetDay() > rhs.GetDay()) return true;
			else if (lhs.GetDay() < rhs.GetDay()) return false;
			else return false;
		}
	}
}

istream& operator >>(istream& stream, Date& obj) {
	int year, month, day;
	string elem;
	stream >> elem;
	stringstream ss(elem);
	ss >> year;
	if (ss.peek() != '-')
		throw invalid_argument("Wrong date format: " + elem);
	else ss.ignore(1);
	ss >> month;
	if (ss.peek() != '-')
		throw invalid_argument("Wrong date format: " + elem);
	else ss.ignore(1);
	if(!(ss >> day))
		throw invalid_argument("Wrong date format: " + elem);
	string end;
	ss >> end;
	if (end != "")
		throw invalid_argument("Wrong date format: " + elem);
	if (1 > month || 12 < month)
		throw invalid_argument("Month value is invalid: " + to_string(month));
	if (1 > day || 31 < day)
		throw invalid_argument("Day value is invalid: " + to_string(day));
	obj = {year, month, day};
	return stream;
}

bool operator ==(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() &&
			lhs.GetDay() == rhs.GetDay()) return true;
	return false;
}

class Database {
public:
	Database() {}

	void AddEvent(const Date& obj, const string& event) {
		data[obj].insert(event);
	}

	bool DeleteEvent(const Date& obj, const string& event) {
		if (data.find(obj) == data.end()) return false;
		else if (data[obj].find(event) == data[obj].end()) return false;
		else data[obj].erase(event);
		return true;
	}

	int DeleteDate(const Date& obj) {
		int res = data[obj].size();
		data.erase(obj);
		return res;
	}

	void Find(const Date& obj) const {
		if (data.find(obj) != data.end())
			for (const string event: data.at(obj))
				cout << event << endl;
	}

	void Print() const {
		for (const auto date: data) {
			for (const string event: date.second) {
				cout << setfill('0');
				cout << setw(4) << date.first.GetYear() << "-" <<
						setw(2) << date.first.GetMonth() << "-" <<
						setw(2) << date.first.GetDay() << " ";
				cout << event << endl;
			}
		}
	}
private:
	map<Date, set<string>> data;
};

int main() {
	Database db;
	string command;
	while(getline(cin, command)) {
		if (command != "") {
			stringstream stream;
			string request;
			stream << command;
			stream >> request;
			try {
				if (request == "Add") {
					Date date;
					string event;
					stream >> date >> event;
					db.AddEvent(date, event);
				} else if (request == "Del") {
					Date date;
					stream >> date;
					try {
						string event;
						stream >> event;
						if (event == "") throw runtime_error("");
						if (db.DeleteEvent(date, event))
							cout << "Deleted successfully" << endl;
						else cout << "Event not found" << endl;
					} catch (exception& ex) {
						cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
					}
				} else if (request == "Print") {
					db.Print();
				} else if (request == "Find") {
					Date date;
					stream >> date;
					db.Find(date);
				} else {
					cout << "Unknown command: " << request << endl;
				}
			} catch (invalid_argument& ex) {
				cout << ex.what() << endl;
			}
		}
	}
	return 0;
}
