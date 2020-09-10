/*
 * person.h
 *
 *  Created on: 7 мая 2020 г.
 *      Author: yo
 */

#pragma once
#include <string>
#include <vector>

using namespace std;


class Person {
public:
	Person (const string& profession, const string& name);

	virtual void Walk(const string& destination) const;

	const string Profession;
	const string Name;
};

void VisitPlaces(Person& person, const vector<string>& places);
