#include <string>
#include <iostream>
#include <algorithm>

int solution(std::string& S) {

	int open = 0;
	int totalClose = 0;
	int actClose = 0;


	for(auto c : S)
		if(c == ')') ++totalClose;

	for(auto i = S.begin(), e = S.end(); i != e; ++i) {
		if(*i == ')') ++actClose;
		else if(*i == '(') ++open;

		if(open == totalClose - actClose) 
			return std::distance(S.begin(), i) + 1;
	}

	return 0;
}

int main() {

	std::string t1{"(())"};
	std::string t2{"(()))"};
	std::string t3{"((())"};
	std::string t4{"(((())())(()))"};
	std::string t5{"))"};
	std::string t6{"(("};

	std::cout << t1 << " pos: " << solution(t1) << std::endl;
	std::cout << t2 << " pos: " << solution(t2) << std::endl;
	std::cout << t3 << " pos: " << solution(t3) << std::endl;
	std::cout << t4 << " pos: " << solution(t4) << std::endl;
	std::cout << t5 << " pos: " << solution(t5) << std::endl;
	std::cout << t6 << " pos: " << solution(t6) << std::endl;
}