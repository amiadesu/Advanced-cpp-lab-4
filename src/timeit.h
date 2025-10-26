#pragma once

#include <iostream>

#include <chrono>
#include <format>

using namespace std;

template <class F>
auto timeit(F&& f, int repeat = 1)
{
    auto time1 = chrono::system_clock::now();
    while (repeat--)
        f();
    auto time2 = chrono::system_clock::now();
    auto tdiff = time2 - time1;
    if (tdiff > 100000ns)
        cout << format("{:%S}", tdiff) << endl;
    else
        cout << tdiff << endl;
    return tdiff;
}