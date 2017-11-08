// you can use includes, for example:
#include <algorithm>
#include <bitset>
#include <utility>
#include <memory>
#include <iostream>

const std::shared_ptr<std::string> toBinaryString(const int& n) {
    std::shared_ptr<std::string> res = std::make_shared<std::string>(std::bitset<32>(n).to_string());    
    return res;
}

int solution(int N) {
    auto bits = toBinaryString(N);
    std::cout << *bits << std::endl;
    auto firstOne = std::find(bits->begin(), bits->end(), '1');
    std::cout << *firstOne << std::endl;
    auto nextOne = std::find(firstOne+1, bits->end(), '1');
    std::cout << *nextOne << std::endl;
    auto gapSize = std::distance(firstOne, nextOne);
    return gapSize - 1;
}

int main() {
	
	std::cout << solution(1041);
}