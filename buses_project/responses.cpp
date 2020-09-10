/*
 * response.cpp
 *
 *  Created on: 5 мая 2020 г.
 *      Author: yo
 */

#include "responses.h"

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.buses.size() == 0) os << "No stop";
	else {
		for (const string elem: r.buses) os << elem << " ";
	}
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.bus == "") os << "No bus";
	else {
		for (const string stop: r.stops) {
			os << "Stop " << stop << ": ";
			if (r.buses.at(stop).size() == 1) os << "no interchange";
			else {
				for (const string bus: r.buses.at(stop)) {
					if (bus != r.bus) os << bus << " ";
				}
			}
			if (stop != r.stops[r.stops.size()-1]) os << endl;
		}

	}
  return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.buses_to_stops.empty()) {
	    os << "No buses";
	} else {
	    for (const auto& bus_item : r.buses_to_stops) {
	        os << "Bus " << bus_item.first << ": ";
	        for (const string& stop : bus_item.second) {
	            os << stop << " ";
	        }
	        os << endl;
	    }
	}
    return os;
}


