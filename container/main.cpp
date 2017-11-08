#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <cstdint>
#include <chrono>
#include <ratio>

const std::uint32_t NUM_ELEMENTS = 10000000;

auto gen = []{static int i{0}; return ++i;};

class TimeMeasurement {
	std::chrono::time_point<std::chrono::high_resolution_clock> _begin;
public:
	TimeMeasurement() : _begin(std::chrono::high_resolution_clock::now()) {}
	
	~TimeMeasurement() { 
		auto duration{std::chrono::high_resolution_clock::now() - _begin};
		std::cout << "Time Measurement: " << std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() << " ns" << std::endl;
		std::cout << "Time Measurement: " << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() << " µs" << std::endl;
		std::cout << "Time Measurement: " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " ms" << std::endl;
		std::cout << "Time Measurement: " << std::chrono::duration_cast<std::chrono::seconds>(duration).count() << " s" << std::endl;
	}
};

void vector() {
	{
		TimeMeasurement tM;
		std::vector<int> iVec(NUM_ELEMENTS);
		std::generate(iVec.begin(), iVec.end(), gen);
		std::random_shuffle(iVec.begin(), iVec.end());
		for(auto i : iVec)
			i;
	}
}

void deque() {
	{
		TimeMeasurement tM;
		std::deque<int> iLis(NUM_ELEMENTS);
		std::generate(iLis.begin(), iLis.end(), gen);
		std::random_shuffle(iLis.begin(), iLis.end());
		for(auto i : iLis)
			i;
	}
}

int main() {

	vector();
	deque();

	return 0;
}