#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;


class Person {
public:
	Person (const string& first, const string& second, int year) {
		start_name = first;
		start_surname = second;
		start_year = year;
	}

  void ChangeFirstName(int year, const string& first_name) {
	  if (start_year <= year) names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
	  if (start_year <= year) surnames[year] = last_name;
  }
  string GetFullName(int year) const {
	  if (!start_name.size() || year < start_year)
		  return "No person";
	  auto it_name = names.find(year);
	  auto it_surname = surnames.find(year);
	  if (it_name != names.end()) {
	  	  if (it_surname != surnames.end())
	  		  return (*it_name).second + " " + (*it_surname).second;
	  	  else {
	  		  it_surname = surnames.upper_bound(year);
	  		  if (it_surname == surnames.begin())
	  			  return (*it_name).second + " " + start_surname;
	  		  else return (*it_name).second + " " + (*(--it_surname)).second;
	   	  }
	  } else {
	  	  if (it_surname != surnames.end()) {
	  		  it_name = names.upper_bound(year);
	  		  if (it_name == names.begin())
	  			  return start_name + " " + (*it_surname).second;
	 		  else return (*(--it_name)).second + " " + (*it_surname).second;
	  	  }
	  	  else {
	  		  it_name = names.upper_bound(year);
	  		  it_surname = surnames.upper_bound(year);
	  		  if (it_name == names.begin()) {
	  		   	  if (it_surname == surnames.begin())
	  			   	  return start_name + " " + start_surname;
	  			  else return start_name + " " + (*(--it_surname)).second;
	  		  } else {
	  			  if (it_surname == surnames.begin())
	  			   	  return (*(--it_name)).second + " " + start_surname;
	  			  else return (*(--it_name)).second + " " + (*(--it_surname)).second;
	  		  }
	  	  }
	  }
  }
  string GetFullNameWithHistory(int year) const {
	  if (!start_surname.size() || year < start_year)
		  return "No person";
	  vector<string> pass_names;
	  vector<string> pass_surnames;
	  pass_names.push_back(start_name);
	  pass_surnames.push_back(start_surname);
	  for (const auto& elem : names) {
		  if (elem.first <= year)
			  pass_names.push_back(elem.second);
		  else break;
	  }
	  for (const auto& elem : surnames) {
	  	  if (elem.first <= year)
	  		  pass_surnames.push_back(elem.second);
	  	  else break;
	  }
	  string answer = pass_names[pass_names.size()-1] + " ";
	  if (pass_names.size() > 1) {
		  answer += "(";
		  for (int i = pass_names.size()-2; i > 0; --i) {
			  if (pass_names[i] != pass_names[i+1])
				  answer += pass_names[i] + ", ";
		  }
		  answer += pass_names[0] + ") ";
	  }
	  answer += pass_surnames[pass_surnames.size()-1];
	  if (pass_surnames.size() > 1) {
		  answer += " (";
		  for (int i = pass_surnames.size()-2; i > 0; --i) {
			  if (pass_surnames[i] != pass_surnames[i+1])
			  	  answer += pass_surnames[i] + ", ";
		  }
		  answer += pass_surnames[0] + ")";
	  }
	  return answer;
  }

private:
  map<int, string> surnames;
  map<int, string> names;
  string start_name;
  string start_surname;
  int start_year;
};

