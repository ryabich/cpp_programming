#include "date.h"

#include <exception>
#include <tuple>
#include <iomanip>

using namespace std;

Date::Date (int _year, int _month, int _day) {
	year = _year;
	month = _month;
	day = _day;
}

int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}

bool operator <=(const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <=
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator >=(const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >=
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator <(const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator >(const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator ==(const Date& lhs, const Date& rhs) {
	return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator !=(const Date& lhs, const Date& rhs) {
	return !(make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) ==
			make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()));
}

Date ParseDate(istream& stream) {
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
	Date obj(year, month, day);
	return obj;
}

ostream& operator <<(ostream& os, const Date& obj) {
	os << setfill('0');
	os << setw(4) << obj.GetYear() << "-" <<
			setw(2) << obj.GetMonth() << "-" <<
			setw(2) << obj.GetDay();
	return os;
}
