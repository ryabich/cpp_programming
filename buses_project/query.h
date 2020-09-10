/*
 * query.h
 *
 *  Created on: 5 мая 2020 г.
 *      Author: yo
 */

#pragma once

#include <vector>
#include <string>
#include <istream>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q);
