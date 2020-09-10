#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

struct Index {
    _Rb_tree_iterator<pair<const string, Record*>> user_ptr;
    _Rb_tree_iterator<pair<const int, Record*>> karma_ptr;
    _Rb_tree_iterator<pair<const int, Record*>> timestamp_ptr;
};
// Реализуйте этот класс
class Database {
public:
    bool Put(const Record& record) {
        if(data.find(record.id) != data.end()) return false;
        else {
            auto& elem = data[record.id];
            elem = move(record);
            auto& idx = indexes[elem.id];
            idx.user_ptr = users.insert({elem.user, &elem});
            idx.timestamp_ptr = timestamps.insert({elem.timestamp, &elem});
            idx.karma_ptr = karmas.insert({elem.karma, &elem});
            return true;
        }
    };
    const Record* GetById(const string& id) const {
        if (data.find(id) != data.end()) return &data.at(id);
        else return nullptr;
    };
    bool Erase(const string& id) {
        if (data.find(id) != data.end()) {
            auto& idx = indexes[id];
            users.erase(idx.user_ptr);
            karmas.erase(idx.karma_ptr);
            timestamps.erase(idx.timestamp_ptr);
            data.erase(id);
            return true;
        } else return false;
    };

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        auto start = timestamps.lower_bound(low);
        auto end = timestamps.upper_bound(high);
        while (start != end) {
            if (!callback(*start->second)) break;
            start++;
        }
    };

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        auto start = karmas.lower_bound(low);
        auto end = karmas.upper_bound(high);
        while (start != end) {
            if (!callback(*start->second)) break;
            start++;
        }
    }

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const {
        auto it = users.equal_range(user);
        while (it.first != it.second) {
            if (!callback(*it.first->second)) break;
            it.first++;
        }
    }

private:
    unordered_map<string, Record> data;
    multimap<string, Record*> users;
    multimap<int, Record*> timestamps;
    multimap<int, Record*> karmas;
    unordered_map<string, Index> indexes;
};

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestSameUser() {
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}