#include <iostream>
#include <format>

#include "thread_execution.h"

using namespace std;

int main() {
	try {
		int threads_amount = 1;
		cout << "Enter threads amount: "; cin >> threads_amount;
		if (threads_amount < 1) {
			cout << "Cannot execute less than 1 thread" << endl;
		}
		else if (threads_amount > 3) {
			cout << "Cannot execute more than 3 threads" << endl;
		}
		else {
			vector<string> file_names;
			for (int i = 0; i < threads_amount; i++) {
				string file_name = format("demo_code_{}.txt", i);
				file_names.push_back(file_name);
			}

			auto results = execute_multithreaded(file_names);

			for (int i = 0; i < threads_amount; i++) {
				cout << "Thread " << i + 1 << ": " << (results[i] / 10000000.0).count() << "s" << endl;
			}
		}
	}
	catch (exception e) {
		cout << "Error while executing: " << e.what() << endl;
	}
}