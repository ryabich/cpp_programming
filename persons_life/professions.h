/*
 * professions.h
 *
 *  Created on: 7 мая 2020 г.
 *      Author: yo
 */

#pragma once
#include "person.h"

using namespace std;

class Teacher : public Person {
private:
	const string Subject;

public:
	Teacher (const string& name, const string& subject);

	void Teach() const;
};


class Student : public Person {
private:
	const string FavouriteSong;

public:
	Student (const string& name, const string& song);

	void Learn() const;

	void SingSong() const;

	void Walk(const string& destination) const override;
};


class Policeman : public Person {
public:
	Policeman(const string& name);

	void Check(Person& person) const;
};
