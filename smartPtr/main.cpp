#include <memory>
#include <utility>
#include <iostream>

class A {

	std::unique_ptr<int> _iPtr;

public:

	void set(const int& i) {
		std::cout << "A.set("<< i << ")" << std::endl;
		_iPtr.release();
		_iPtr = std::make_unique<int>(i);
	}

	const std::unique_ptr<int>& get() const {
		return _iPtr;
	}

	A() : _iPtr(std::make_unique<int>(1337)) {
		std::cout << "A created - i: " <<  *_iPtr << std::endl;
	}

	A(const int& i) : _iPtr(std::make_unique<int>(i)) {
		std::cout << "A created - i: " <<  *_iPtr << std::endl;
	}

	virtual ~A() {
		std::cout << "A destroyed" << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& os, const A& a);
};

std::ostream& operator<<(std::ostream& os, const A& a) {
	os << *a._iPtr;
	return os;
}

int main() {	

	A a;
	A a1(1);
	std::shared_ptr<A> aPtr = std::make_shared<A>(1234);

	{
		std::shared_ptr<A> aSPtr = std::make_shared<A>(1234);
		std::unique_ptr<A> aUPtr = std::make_unique<A>(4321);

		std::shared_ptr<A> aSPtr1{new A(13377)};
		std::unique_ptr<A> aSPtr2{new A(113377)};
		
	}

	std::cout << *(a.get()) << " akk" << std::endl;
	a.set(42);
	std::cout << *(a.get()) << " akk1" << std::endl;

	std::cout << *(a1.get()) << " akk" << std::endl;

	
	std::shared_ptr<A> aPtr1 = std::make_shared<A>(5678);

	std::cout << *(aPtr.get()) << " akk123" << std::endl;
	std::cout << *(aPtr1.get()) << " akk1234" << std::endl;

	std::swap(aPtr1, aPtr);

	std::cout << *(aPtr.get()) << " akk123" << std::endl;
	std::cout << *(aPtr1.get()) << " akk1234" << std::endl;


	return 0;
}