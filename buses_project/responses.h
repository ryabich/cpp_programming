/*
 * responses.h
 *
 *  Created on: 5 мая 2020 г.
 *      Author: yo
 */

#pragma once

#include <ostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct BusesForStopResponse {
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
	string bus;
	vector<string> stops;
	map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
	map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);
