#include <mutex>
#include <iostream>

class A {
protected:
	std::mutex mA;
public:
	A() {
		std::cout << "A" << std::endl;
		mA.lock();
	}
};


class B : public A {
public:
	B() : A() {
		std::cout << "B" << std::endl;
		mA.lock();
	}

};

int main() {

	A a;
	B b;
	
}
