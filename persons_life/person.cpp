/*
 * person.cpp
 *
 *  Created on: 7 мая 2020 г.
 *      Author: yo
 */
#include <iostream>
#include "person.h"

using namespace std;

Person::Person (const string& profession, const string& name) :
				Profession(profession), Name(name) {}

void Person::Walk(const string& destination) const {
	cout << Profession << ": " << Name << " walks to: " << destination << endl;
}

void VisitPlaces(Person& person, const vector<string>& places) {
	for (const string place : places) person.Walk(place);
}
