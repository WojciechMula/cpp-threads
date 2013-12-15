#include <cstdio>
#include <iostream>
#include <vector>

#include <future>
#include <chrono>

int file_sum(const char* name) {
	FILE* f;

	f = fopen(name, "rb");
	if (!f) {
		return -1;
	}

	int sum = 0;
	while (!feof(f)) {
		sum += fgetc(f);
	}

	fclose(f);

	return sum;
}


int main(int argc, char* argv[]) {
	const char progress[] = "|/-\\";

	typedef std::future<int> sum_result_future;

	std::vector<sum_result_future> jobs;
	std::vector<int> ticks;

	for (int i = 1; i < argc; i++) {
		jobs.push_back(
			std::async(std::launch::async, file_sum, argv[i])
		);

		ticks.push_back(0);
	}

	bool any_waiting = true;
	while (any_waiting) {
		any_waiting = false;
		std::chrono::milliseconds tiny(5);
		for (size_t i=0; i < jobs.size(); i++) {
			if (jobs[i].wait_for(tiny) == std::future_status::ready)
				std::cout << '.';
			else {
				std::cout << progress[ticks[i] % 4];

				ticks[i] += 1;
				any_waiting = true;
			}
		}

		std::cout << '\r';
		std::cout.flush();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << "\n";
	for (size_t i=0; i < jobs.size(); i++) {
		std::cout << "* " << argv[i+1] << ": " << jobs[i].get() << "\n";
	}
}
