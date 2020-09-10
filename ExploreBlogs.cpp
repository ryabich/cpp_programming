#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <vector>
#include <future>
#include <functional>
#include <sstream>

using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for (const auto& elem: other.word_frequences) {
            word_frequences[elem.first] += elem.second;
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    stringstream str(line);
    string word;
    Stats res;
    while (getline(str, word, ' ')) {
        if (key_words.find(word) != key_words.end())
            res.word_frequences[word] += 1;
    }
    return res;
}

Stats ExploreKeyWordsSingleThread(
        const set<string>& key_words, istream& input
) {
    Stats result;
    for (string line; getline(input, line); ) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    vector<future<Stats>> futures;
    Stats result;
    vector<stringstream> peeks(8);
    string line;
    int index = 0;
    while (getline(input, line)) {
        peeks[index] << line << "\n";
        index = (index+1)%8;
    }
    for (size_t i = 0; i < 8; ++i) {
        futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(peeks[i])));
    }
    for (size_t i = 0; i < 8; ++i) {
        result += futures[i].get();
    }
    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when  yangle isn't available\n";
    ss << "10 reasons why  yangle is the best IT company\n";
    ss << "yangle rocks   others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
    ss << "yangle rocks   others suck\n";
    ss << "yangle rocks   others suck\n";
    ss << "yangle rocks   others suck\n";
    ss << "yangle rocks   others suck\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 10},
            {"rocks", 6},
            {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}