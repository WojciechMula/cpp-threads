/*

	There is no way to catch an unhandled exceptions in raised in a thread.

*/
#include <exception>
#include <iostream>
#include <thread>

void thread1(int arg1) {
	throw int(arg1);
}

void terminate () {
  std::cerr << "unhandled exception in thread #" << std::this_thread::get_id()  << "\n";
}

int main() {
	std::set_terminate (terminate);	

	std::thread t(thread1, 42);

	std::cout << "waiting for thread #" << t.get_id() << "...\n";
	t.join();

	return 0;
}
