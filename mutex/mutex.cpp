#include <string>
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex;

void thread(int id) {
	mutex.lock();
	for (int i=0; i < 10000; i++)
		std::cout << id << ' ';
	mutex.unlock();
}

int main() {
	const int count = 100;
	std::thread threads[count];

	for (int i=0; i < count; i++) {
		threads[i] = std::thread(thread, i);
	}
	
	for (int i=0; i < count; i++) {
		threads[i].join();
	}

	return 0;
}

