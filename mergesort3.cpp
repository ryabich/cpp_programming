#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin < 2) return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	auto it1 = (end(elements) - begin(elements))/3 + begin(elements);
	auto it2 = (end(elements) - begin(elements))/3 + it1;
	MergeSort(begin(elements), it1);
	MergeSort(it1, it2);
	MergeSort(it2, end(elements));
	vector<typename RandomIt::value_type> time;
	merge(begin(elements), it1, it1, it2, back_inserter(time));
	merge(begin(time), end(time), it2, end(elements), range_begin);
}
