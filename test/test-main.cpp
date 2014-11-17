
#include "a/test.h"
#include "random.hpp"

#include <exception>
#include <iostream>

int main()
{

    chf::random_test(std::cout, 2000, 8, 200);

	using namespace fdctest;

	try {
		a::test();
	}
	catch (std::exception& ex) {
		auto what = ex.what();
		std::cerr << what << std::endl;
		return -1;
	}

	return 0;
}