#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class FunctionPart {
public:
	FunctionPart (char c, double new_value) {
		sign = c;
		value = new_value;
	}
	double Apply (double request) const {
		if (sign == '+') {
			request += value;
		} else if (sign == '-') {
			request -= value;
		} else if (sign == '*') {
			request *= value;
		} else {
			request /= value;
		}
		return request;
	}
	void Invert() {
		if (sign == '+') sign = '-';
		else if (sign == '*' ) sign = '/';
		else if (sign == '/') sign = '*';
		else sign = '+';
	}
private:
	char sign;
	double value;
};

class Function {
public:
	void AddPart(char c, double value) {
		data.push_back({c, value});
	}
	double Apply(double value) const {
		for (const FunctionPart elem : data) {
			value = elem.Apply(value);
		}
		return value;
	}
	void Invert() {
		for (FunctionPart& elem : data) {
			elem.Invert();
		}
		reverse(data.begin(), data.end());
	}
private:
	vector<FunctionPart> data;
};
