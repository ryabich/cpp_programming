#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>
#include <functional>
#include <thread>

using namespace std;
using namespace chrono;

const vector<pair<size_t, size_t>> EMPTY;

vector<string> SplitIntoWords(string&& line) {

    istringstream words_input(move(line));
    return {make_move_iterator(istream_iterator<string>(words_input)),
            make_move_iterator(istream_iterator<string>())};
}

void UpdateDocs(istream& document_input, Synchronized<InvertedIndex>& index) {
    InvertedIndex new_index;
    //auto& f = index.GetAccess().ref_to_value;
    string current_document;
    while (getline(document_input, current_document)) {
        new_index.Add(move(current_document));
    }

    {
        index.GetAccess().ref_to_value = move(new_index);
    }
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    //this_thread::sleep_for(milliseconds(150));
    futures.push_back(async(UpdateDocs, ref(document_input), ref(index)));
    //UpdateDocs(document_input, index);
    //return futures.back().get();
}

SearchServer::SearchServer(istream& document_input) {
    //UpdateDocumentBase(document_input);
    UpdateDocs(document_input, index);
}

void AddQueries (istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex>& index) {
    size_t size = index.GetAccess().ref_to_value.Size();
    vector<pair<size_t, size_t>> search_results(size);
    string current_query;
    //auto& f = index.GetAccess().ref_to_value;
    while (getline(query_input, current_query)) {
        {
            search_results.assign(size, {0, 0});
        }
        search_results_output << current_query << ':';

        for (const auto &word : SplitIntoWords(move(current_query))) {
            const auto &index_ = index.GetAccess().ref_to_value;
            for (const auto &docid : index_.Lookup(word)) {
                search_results[docid.second].second += docid.first;
                search_results[docid.second].first = docid.second;
            }
        }

        partial_sort(
                begin(search_results),
                begin(search_results) + min<size_t>(search_results.size(), 5),
                end(search_results),
                [](const pair<size_t, size_t> &lhs, const pair<size_t, size_t> &rhs) {
                    return pair(lhs.second, -static_cast<int>(lhs.first)) >
                           pair(rhs.second, -static_cast<int>(rhs.first));
                }
        );

        for (const auto&[docid, hitcount] : Head(search_results, 5)) {
            if (hitcount != 0)
                search_results_output << " {"
                                      << "docid: " << docid << ", "
                                      << "hitcount: " << hitcount << '}';
            else break;
        }
        search_results_output << '\n';
    }
}

void SearchServer::AddQueriesStream(
        istream& query_input, ostream& search_results_output
) {
    //this_thread::sleep_for(milliseconds(150));
    futures.push_back(async(AddQueries, ref(query_input), ref(search_results_output), ref(index)));
    //AddQueries(query_input, search_results_output, index);
    //return futures.back().get();
}

void InvertedIndex::Add(string&& document) {

    for (auto& word : SplitIntoWords(move(document))) {
        auto& elem = index[word];
        if (elem.empty() || elem.back().second != docid)
            elem.push_back(make_pair(0, docid));
        elem.back().first++;
    }
    docid++;
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(const string& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return EMPTY;
    }
}

