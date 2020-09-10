#pragma once

#include <set>
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>

#include "date.h"

using namespace std;

class Database {
public:
	Database() {}

	void Add(const Date& obj, const string& event);

	void Print(ostream& os) const;

	template <typename predicate>
	int RemoveIf(predicate p) {
		vector<Date> del_dates;
		int counter = 0;
		for (auto& elem : data) {
			vector<string> del_events;
			for (auto& event : elem.second) {
				if (p(elem.first, event)) {
					del_events.push_back(event);
					counter++;
				}
			}
			Date _date = elem.first;
			auto it = remove_if(sequence[elem.first].begin(), sequence[elem.first].end(),
					[p, _date](const string& _event) {
				return p(_date, _event);
			});
			sequence[elem.first].erase(it, sequence[elem.first].end());
			for (auto event : del_events) elem.second.erase(event);
			if (elem.second.empty()) del_dates.push_back(elem.first);
		}
		for (auto date : del_dates) {
			data.erase(date);
			sequence.erase(date);
		}
		return counter;
	}


	template<typename predicate>
	vector<string> FindIf(predicate p) const {
		vector<string> ans;
		for (const auto& elem: sequence) {
			for (const string& event : elem.second) {
				if (p(elem.first, event)) {
					stringstream os;
					os << setfill('0');
					os << setw(4) << elem.first.GetYear() << "-" <<
							setw(2) << elem.first.GetMonth() << "-" <<
							setw(2) << elem.first.GetDay() << " ";
					os << event;
					ans.push_back(os.str());
				}
			}
		}
		return ans;
	}

	string Last(const Date& date) const;
private:
	map<Date, set<string>> data;
	map<Date, vector<string>> sequence;

	void PrintDate(ostream& os, const Date& date) const;
};
