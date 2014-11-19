
#include "a/test.h"
#include "random.hpp"

#include <exception>
#include <iostream>
#include <fstream>

int main()
{
    //std::ofstream out("../test/gen/gen40.hpp");
    //chf::random_test(out, 40, 4, 10);

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