#include "database.h"


void Database::Add(const Date& obj, const string& event) {
	if (data[obj].count(event) == 0) {
		data[obj].insert(event);
		sequence[obj].push_back(event);
	}
}

void Database::Print(ostream& os) const {
	for (const auto date: sequence) {
		for (const string event: date.second) {
			os << setfill('0');
			os << setw(4) << date.first.GetYear() << "-" <<
					setw(2) << date.first.GetMonth() << "-" <<
					setw(2) << date.first.GetDay() << " ";
			os << event << endl;
		}
	}
}

string Database::Last(const Date& date) const {
	auto it = sequence.upper_bound(date);
	if (it == sequence.begin()) {
		throw invalid_argument("");
		return "";
	} else {
		it--;
		Date new_date = (*it).first;
		string event = (*it).second.back();

		stringstream os;
		os << setfill('0');
		os << setw(4) << new_date.GetYear() << "-" <<
				setw(2) << new_date.GetMonth() << "-" <<
				setw(2) << new_date.GetDay() << " ";
		os << event;
		return os.str();
	}
}
