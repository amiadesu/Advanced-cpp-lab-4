#include <vector>
#include <fstream>
#include <thread>
#include <future>
#include <string>

#include "timeit.h"
#include "struct.h"

using namespace std;

using duration = chrono::system_clock::duration;

void execute_ops(DataStruct& dataStruct, ifstream& file) {
	string op;
	while (file >> op) {
		if (op == "write") {
			int field, value; file >> field >> value;
			if (field == 0) {
				dataStruct.set0(value);
			}
			else if (field == 1) {
				dataStruct.set1(value);
			}
			else {
				dataStruct.set2(value);
			}
		}
		else if (op == "read") {
			int field; file >> field;
			if (field == 0) {
				dataStruct.get0();
			}
			else if (field == 1) {
				dataStruct.get1();
			}
			else {
				dataStruct.get2();
			}
		}
		else {
			string res = dataStruct;
		}
	}
}

duration execute_timeit(DataStruct& dataStruct, ifstream& file) {
	return timeit(
		[&dataStruct, &file]() {
			execute_ops(dataStruct, file);
		}
	);
}

auto execute_multithreaded(const vector<string>& file_names) {
	DataStruct dataStruct;
	vector<future<duration>> results;

	for (auto& name : file_names) {
		results.push_back(
			async(launch::async, [&, name]() -> duration {
					ifstream file(name);
					if (!file) throw runtime_error("Cannot open file " + name);
					return execute_timeit(dataStruct, file);
				}
			)
		);
	}

	vector<duration> times;
	times.reserve(results.size());
	for (auto& f : results) {
		times.push_back(f.get());
	}
	return times;
}