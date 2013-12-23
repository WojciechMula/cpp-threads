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
	while (true) {
		const int c = fgetc(f);

		if (c == EOF)
			break;

		sum += c;
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
			switch (jobs[i].wait_for(tiny)) {
				case std::future_status::ready:
					std::cout << '.';
					break;

				case std::future_status::deferred:
					break;

				case std::future_status::timeout:
					std::cout << progress[ticks[i] % 4];

					ticks[i] += 1;
					any_waiting = true;
					break;
			}
		}

		std::cout << '\r';
		std::cout.flush();
	}

	std::cout << "\n";
	for (size_t i=0; i < jobs.size(); i++) {
		std::cout << "* " << argv[i+1] << ": " << jobs[i].get() << "\n";
	}
}
