#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <memory>
#include <vector>
#include <iomanip>

using namespace std;

class Figure {
public:
	Figure(const string& _name) : name(_name) {}

	string Name() {
		return name;
	}

	virtual double Perimeter() const = 0;

	virtual double Area() const = 0;

private:
	const string name;
};


class Rect : public Figure {
public:
	Rect (double _width, double _height)
			   : Figure("RECT"), width(_width), height(_height) {}

	double Perimeter() const override {
		return width*2 + height*2;
	}

	double Area() const override {
		return width * height;
	}

private:
	const double width;
	const double height;
};


class Circle : public Figure {
public:
	Circle (double _radius) : Figure("CIRCLE"), radius(_radius) {}

	double Perimeter() const override {
		return 2 * 3.14 * radius;
	}

	double Area() const override {
		return 3.14 * radius * radius;
	}
private:
	const double radius;
};


class Triangle : public Figure {
public:
	Triangle (double _a, double _b, double _c) :
			  Figure("TRIANGLE"), a(_a), b(_b), c(_c) {}

	double Perimeter() const override {
		return a + b + c;
	}

	double Area() const override {
		double p = (a + b + c)/2;
		return sqrt(p * (p-a) * (p-b) * (p-c));
	}

private:
	const double a, b, c;
};

shared_ptr<Figure> CreateFigure(istream& stream) {
	string name;
	stream >> name;
	if (name == "RECT") {
		double width, height;
		stream >> width >> height;
		return make_shared<Rect>(width, height);
	} else if (name == "TRIANGLE") {
		double a, b, c;
		stream >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	} else {
		double r;
		stream >> r;
		return make_shared<Circle>(r);
	}
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
