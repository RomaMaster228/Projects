#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void var() {
	cout << this_thread::get_id() << " " << "Hello" << '\n';
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "world!" << '\n';
}

int main() {
	thread th1(var);

	for (int i = 0; i < 10; i++) {
		cout << this_thread::get_id() << " " << i + 1 << '\n';
		this_thread::sleep_for(chrono::milliseconds(500));
	}

	th1.join();
	return 0;
}
