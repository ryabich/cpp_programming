#pragma once

#include <sstream>

using namespace std;

class Date {
private:
	int year;
	int month;
	int day;

public:
	Date();

	Date (int _year, int _month, int _day);

	int GetYear() const;

	int GetMonth() const;

	int GetDay() const;
};

bool operator <=(const Date& lhs, const Date& rhs);

bool operator >=(const Date& lhs, const Date& rhs);

bool operator !=(const Date& lhs, const Date& rhs);

bool operator <(const Date& lhs, const Date& rhs);

bool operator >(const Date& lhs, const Date& rhs);

bool operator ==(const Date& lhs, const Date& rhs);

ostream& operator <<(ostream& os, const Date& obj);

Date ParseDate(istream& stream);
