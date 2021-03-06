#pragma once

#include <mutex>
using namespace std;

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T())
            : value(move(initial))
    {
    }

    struct Access {
        T& ref_to_value;
        lock_guard<mutex> guard;
    };

    Access GetAccess() {
        return {value, lock_guard(m)};
    }

    void Unlock() {
        m.unlock();
    }

private:
    T value;
    mutex m;
};