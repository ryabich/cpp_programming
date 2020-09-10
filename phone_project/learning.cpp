#include "phone_number.h"
#include <sstream>
#include <exception>
#include <iostream>

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number) {
	int index = 1;
	if (international_number.size() < 5 || international_number[0] != '+')
		throw invalid_argument("");
	try {
		while (index < international_number.size() &&
				international_number[index] != '-') {
			country_code_ += international_number[index];
			index++;
		}
		index++;
		while (index < international_number.size() &&
				international_number[index] != '-') {
			city_code_ += international_number[index];
			index++;
		}
		index++;
		while (index < international_number.size()) {
			local_number_ += international_number[index];
			index++;
		}
		if (local_number_.size() == 0 || country_code_.size() == 0 ||
				city_code_.size() == 0)
			throw invalid_argument("");
	} catch (...) {
		throw invalid_argument("");
	}
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
