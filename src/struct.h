#pragma once

#include <shared_mutex>

class DataStruct {
public:
    using value_type = int;
private:
    mutable std::mutex mtx0;
    mutable std::shared_mutex mtx1;
    mutable std::mutex mtx2;
    value_type field0 = 0;
    value_type field1 = 0;
    value_type field2 = 0;

public:
    // 10% read, 10% write
    value_type get0() const;
    void set0(value_type value);

    // 50% read, 10% write
    value_type get1() const;
    void set1(value_type value);

    // 5% read, 5% write
    value_type get2() const;
    void set2(value_type value);

    // 10%
    operator std::string() const;
};
