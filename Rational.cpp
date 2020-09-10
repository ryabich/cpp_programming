#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
using namespace std;

class Rational {
private:
	int num;
	int den;

	pair<int, int> sign(int num, int den) {
		if (den < 0) {
			den = abs(den);
			num = -num;
		}
		return {num, den};
	}

	int gcd(int num, int den) {
		while (den != 0) {
			num %= den;
			swap(num, den);
		}
		return num;
	}

public:
	Rational(int new_num = 0, int new_den = 1) {
		pair<int, int> res = sign(new_num, new_den);
		int nod = gcd(abs(res.first), abs(res.second));
		num = res.first/nod;
		den = res.second/nod;
	}

	int Numerator() const {
		return num;
	}

	int Denominator() const {
		return den;
	}

	Rational operator+(const Rational obj) const {
		int new_num = this->num * obj.den + obj.num * this->den;
		int new_den = this->den * obj.den;
		return Rational(new_num, new_den);
	}

	Rational operator-(const Rational obj) const {
		int new_num = this->num * obj.den - obj.num * this->den;
		int new_den = this->den * obj.den;
		return Rational(new_num, new_den);
	}

	Rational operator/(const Rational obj) const {
		int new_num = this->num * obj.den;
		int new_den = this->den * obj.num;
		return Rational(new_num, new_den);
	}

	Rational operator*(const Rational obj) const {
		int new_num = this->num * obj.num;
		int new_den = this->den * obj.den;
		return Rational(new_num, new_den);
	}

	bool operator==(const Rational obj) const {
		if (this->num == obj.num && this->den == obj.den) return true;
		else return false;
	}

	bool operator>(const Rational& obj) const {
		int left = this->num * obj.den;
		int right = this->den * obj.num;
		return left > right;
	}

	bool operator<(const Rational& obj) const {
		int left = this->num * obj.den;
		int right = this->den * obj.num;
		return left < right;
	}
};

ostream& operator<<(ostream& stream, const Rational& obj) {
	stream << obj.Numerator() << "/" << obj.Denominator();
	return stream;
}

istream& operator>>(istream& stream, Rational& obj) {
	int num, den;
	if(stream >> num) {
		stream.ignore(1);
		if(stream >> den) {
			obj = {num, den};
		} else {
			obj = {num, 1};
		}
	}
	return stream;
}

