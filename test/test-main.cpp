
#include "a/test.h"

#include <exception>
#include <iostream>

int main()
{
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