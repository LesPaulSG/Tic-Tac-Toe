#include <iostream>
#include "IO_Thread.h"
#include <thread>

int main() {
	std::thread IO(input);
	IO.join();
}