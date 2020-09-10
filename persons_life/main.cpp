#include "professions.h"
using namespace std;

int main() {
	vector<string> destinations = {"Moscow", "London"};
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");
	VisitPlaces(t, destinations);
	p.Check(s);
	VisitPlaces(s, destinations);
    return 0;
}
