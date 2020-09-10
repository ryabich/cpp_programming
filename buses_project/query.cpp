#include "query.h"

istream& operator >> (istream& is, Query& q) {
	string request_str;
	int request;
	is >> request_str;
	if (request_str == "NEW_BUS") request = 0;
	if (request_str == "BUSES_FOR_STOP") request = 1;
	if (request_str == "STOPS_FOR_BUS") request = 2;
	if (request_str == "ALL_BUSES") request = 3;
	switch(request) {
	case 0:
		q.type = QueryType::NewBus;
		is >> q.bus;
		int stop_count;
		is >> stop_count;
		q.stops.clear();
		for (size_t i = 0; i < stop_count; ++i) {
			string stop;
			is >> stop;
			q.stops.push_back(stop);
		}
		break;
	case 1:
		q.type = QueryType::BusesForStop;
		is >> q.stop;
		break;
	case 2:
		q.type = QueryType::StopsForBus;
		is >> q.bus;
		break;
	default:
		q.type = QueryType::AllBuses;
	}
  return is;
}



