#include <iostream>

class A {
public:
	virtual int getA() = 0;
	virtual int getB() = 0;
	int sum() {
		return getA() + getB();
	}
};

int main() {
	class B : public A {
		int getA() override {
			return 1;
		}
		int getB() override {
			return 2;
		}
	};
	A* object = new B;
	std::cout << object->sum();
}