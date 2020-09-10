#include <iostream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <exception>
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
		if (new_den != 0) {
			pair<int, int> res = sign(new_num, new_den);
			int nod = gcd(abs(res.first), abs(res.second));
			num = res.first/nod;
			den = res.second/nod;
		} else throw invalid_argument("");
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
		if (obj.num != 0) {
			int new_num = this->num * obj.den;
			int new_den = this->den * obj.num;
			return Rational(new_num, new_den);
		} else throw domain_error("");
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
	try {
		int num = 0;
		int den = 1;
		stream >> num;
		if (cin.peek() != '/')
			throw invalid_argument("");
		else cin.ignore(1);
		stream >> den;
		if (den <= 0) throw invalid_argument("");
		obj = {num, den};
	} catch (invalid_argument& er) {
		throw invalid_argument("");
	}
	return stream;
}

int main() {
	Rational first, second;
	char sign;
	try {
		cin >> first >> sign >> second;
		if (sign == '+') cout << first + second;
		else if (sign == '-') cout << first - second;
		else if (sign == '/') cout << first / second;
		else cout << first * second;
	} catch (domain_error& er) {
		cout << "Division by zero";
		return 0;
	} catch (invalid_argument& er) {
		cout << "Invalid argument";
	}
	return 0;
}
