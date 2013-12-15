#include <iostream>
#include <thread>

void thread1(int arg1) {
	std::cout << "argument of thread " << arg1 << "\n";
}

int main() {
	
	std::thread t(thread1, 42);

	std::cout << "waiting for thread #" << t.get_id() << "\n";
	t.join();
	std::cout << "... done\n";

	return 0;
}
