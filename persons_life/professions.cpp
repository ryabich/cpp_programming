/*
 * professions.cpp
 *
 *  Created on: 7 мая 2020 г.
 *      Author: yo
 */

#include <iostream>
#include "person.h"
#include "professions.h"

using namespace std;



Teacher::Teacher (const string& name, const string& subject) :
		Person("Teacher", name), Subject(subject) {}

void Teacher::Teach() const {
	cout << Profession << ": " << Name << " teaches: " << Subject << endl;
}

Student::Student (const string& name, const string& song) :
		Person("Student", name), FavouriteSong(song) {}

void Student::Learn() const {
	cout << Profession << ": " << Name << " learns" << endl;
}

void Student::SingSong() const {
	cout << Profession << ": " << Name << " sings a song: " << FavouriteSong << endl;
}

void Student::Walk(const string& destination) const {
	cout << Profession << ": " << Name << " walks to: " << destination << endl;
	SingSong();
}

Policeman::Policeman(const string& name) : Person("Policeman", name) {}

void Policeman::Check(Person& person) const {
	cout << Profession << ": " << Name << " checks " << person.Profession <<
			". " << person.Profession << "'s name is: " << person.Name << endl;
}
