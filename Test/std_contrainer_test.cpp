#include <vector>
#include <iostream>

class A {
public:
	int num;
	int num2;
	A(int num):num(num), num2(num*num) {}

};


void basic_test() {
	A a = A(5);
	std::cout << a.num << " " << a.num2 << std::endl;
}
void vector_test() {
	std::vector<int> c{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (auto &i : c) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	c.erase(c.begin());

	for (auto i : c) {

		std::cout << i << " ";
		i++;
	}
	std::cout << "\n";

	for (auto &i : c) {
		std::cout << i << " ";
		i++;
	}
	std::cout << '\n';

	for (auto &i : c) {
		std::cout << i << " ";

	}
	std::cout << '\n';


	c.erase(c.begin() + 2, c.begin() + 5);

	for (auto &i : c) {
		std::cout << i << " ";
	}
	std::cout << '\n';

	// Erase all even numbers (C++11 and later)
	for (auto it = c.begin(); it != c.end(); ) {
		if (*it % 2 == 0) {
			it = c.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto &i : c) {
		std::cout << i << " ";
	}
	std::cout << '\n';
}

int main()
{
	//vector_test();
	basic_test();

	getchar();
}