/*
 * bus_manager.cpp
 *
 *  Created on: 5 мая 2020 г.
 *      Author: yo
 */

#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
	  for (const string elem : stops) {
		  buses_to_stops[bus].push_back(elem);
		  stops_to_buses[elem].push_back(bus);
	  }
  }

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
	vector<string> buses;
	if (stops_to_buses.count(stop) == 1) buses = stops_to_buses.at(stop);
	return {buses};
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
	vector<string> stops;
	if (buses_to_stops.count(bus) == 0) return {"", stops, stops_to_buses};
	if (buses_to_stops.count(bus) == 1) stops = buses_to_stops.at(bus);
	return {bus, stops, stops_to_buses};
}

AllBusesResponse BusManager::GetAllBuses() const {
	return {buses_to_stops};
}


