#pragma once

#include "synhronized.h"
#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <future>
#include <mutex>
#include <unordered_map>

using namespace std;

class InvertedIndex {
public:

    InvertedIndex() = default;
    InvertedIndex (InvertedIndex&& other) : index(other.index), docid(other.docid) {}
    void operator = (InvertedIndex&& other) {
        index = other.index;
        docid = other.docid;
    }
    void Add(string&& document);
    const vector<pair<size_t, size_t>>& Lookup(const string& word) const;

    size_t Size() const {
        return docid;
    }

private:
    unordered_map<string, vector<pair<size_t, size_t>>> index;
    size_t docid = 0;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);
    Synchronized<InvertedIndex>& Item() {
        return index;
    }
    vector<future<void>>& Futures() {
        return futures;
    }

private:
    Synchronized<InvertedIndex> index;
    vector<future<void>> futures;
};