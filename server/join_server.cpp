#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include "server.h"

struct Timer 
{
	using time_point = std::chrono::time_point<std::chrono::steady_clock>;

	Timer(): start_p(std::chrono::steady_clock::now()) {}

	// elapsed time in ms
	auto getElapsed() {
		auto end = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - start_p).count();
	}
	
private:
	time_point start_p;
};


void big_compute() {
	std::cout << "Hi\n";
	for (volatile size_t i = 0; i < 100000000; i++) {
	}
}

int main() {
	int a = 5;

	boost::asio::io_context io;
	//server s(io, 5656);

	boost::asio::post(io, [&]() { big_compute(); });
	boost::asio::post(io, [&]() { big_compute(); });
	boost::asio::post(io, [&]() { big_compute(); });
	boost::asio::post(io, [&]() { big_compute(); });
	boost::asio::post(io, [&]() { big_compute(); });
	boost::asio::post(io, [&]() { big_compute(); });
	boost::asio::post(io, [&]() { big_compute(); });
	boost::asio::post(io, [&]() { big_compute(); });
	boost::asio::post(io, [&]() { big_compute(); });
	boost::asio::post(io, [&]() { big_compute(); });


	Timer timer;

	std::thread t1(
		[&]() {
			io.run();
		}
	);
	std::thread t2(
		[&]() {
			io.run();
		}
	);

	t1.join();
	t2.join();

	//io.run();


	std::cout << timer.getElapsed() << "\n";

	

	//io.run();

	//std::cout << a << "\n";
}