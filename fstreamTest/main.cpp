
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int main() {
	std::fstream f("main.cpp", std::fstream::in);
	std::string p;
	f >> p;
	std::cout << p <<  std::endl;

    std::stringstream contentStream;
    contentStream << f.rdbuf();

	std::cout << contentStream.str();

	return 1;
}
