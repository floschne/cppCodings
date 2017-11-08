#include <iostream>
#include <string>

class A
{
	std::string _s;
public:
	 A(const std::string& s) : _s(s) {}
	~ A();

	void setS(const std::string& ss) {
		_s = ss;
	}

	std::string& getS() { return _s; }
};

void f(A* a) {
	std::string abc("abc");
	a->setS(abc);
}

int main() {


	A* b = new A("akk");

	f(b);

	std::cout << b->getS(); 

	return 0;
}