#include <iostream>
#include <atomic>

const char* value_description(int x) {
	switch (x) {
		case 0:
			return "never";

		case 1:
			return "sometimes";

		case 2:
			return "always";

		default:
			return "unknown";
	}
}


void print(const char* name, int value) {
	std::cout << name << ": lock-free " << value_description(value) << "\n";
}


int main() {

	print("ATOMIC_BOOL_LOCK_FREE", ATOMIC_BOOL_LOCK_FREE);
	print("ATOMIC_CHAR_LOCK_FREE", ATOMIC_CHAR_LOCK_FREE);
	print("ATOMIC_SHORT_LOCK_FREE", ATOMIC_SHORT_LOCK_FREE);
	print("ATOMIC_INT_LOCK_FREE", ATOMIC_INT_LOCK_FREE);
	print("ATOMIC_LONG_LOCK_FREE", ATOMIC_LONG_LOCK_FREE);
	print("ATOMIC_LLONG_LOCK_FREE", ATOMIC_LLONG_LOCK_FREE);
	print("ATOMIC_WCHAR_T_LOCK_FREE", ATOMIC_WCHAR_T_LOCK_FREE);
	print("ATOMIC_CHAR16_T_LOCK_FREE", ATOMIC_CHAR16_T_LOCK_FREE);
	print("ATOMIC_CHAR32_T_LOCK_FREE", ATOMIC_CHAR32_T_LOCK_FREE);
	print("ATOMIC_POINTER_LOCK_FREE", ATOMIC_POINTER_LOCK_FREE);

	return 0;
}
