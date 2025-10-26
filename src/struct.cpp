#include "struct.h"

#include <atomic>
#include <shared_mutex>
#include <string>
#include <sstream>

DataStruct::value_type DataStruct::get0() const {
    std::lock_guard<std::mutex> lck(mtx0);
    return field0;
}
void DataStruct::set0(DataStruct::value_type value) {
    std::lock_guard<std::mutex> lck(mtx0);
    field0 = value;
}

DataStruct::value_type DataStruct::get1() const {
    std::shared_lock<std::shared_mutex> lck(mtx1);
    return field1;
}
void DataStruct::set1(DataStruct::value_type value) {
    std::unique_lock<std::shared_mutex> lck(mtx1);
    field1 = value;
}

DataStruct::value_type DataStruct::get2() const {
    std::lock_guard<std::mutex> lck(mtx2);
    return field2;
}
void DataStruct::set2(DataStruct::value_type value) {
    std::lock_guard<std::mutex> lck(mtx2);
    field2 = value;
}

DataStruct::operator std::string() const {
    std::lock_guard<std::mutex> lck0(mtx0);
    std::shared_lock<std::shared_mutex> lck1(mtx1);
    std::lock_guard<std::mutex> lck2(mtx2);

    std::ostringstream ss;
    ss << "field0=" << field0
        << ", field1=" << field1
        << ", field2=" << field2;
    return ss.str();
}
