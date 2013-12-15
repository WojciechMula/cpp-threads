#include <iostream>
#include <thread>

void thread(int count) {
	while (count--) {
		std::cout << std::this_thread::get_id() << "\n";
	}
}

int main() {
	std::thread threads[10];

	for (int i=0; i < 10; i++) {
		threads[i] = std::thread(thread, (i+1)*5000);
	}
	
	for (int i=0; i < 10; i++) {
		threads[i].join();
	}

	return 0;
}
