
#include "random.hpp"

#include <exception>
#include <iostream>
#include <fstream>

namespace chf
{
namespace test
{
	void test_a();
	void test_gen40();
}
}

int main()
{
    //std::ofstream out("../test/gen/gen40.hpp");
    //chf::random_test(out, 40, 4, 10);

	using namespace chf::test;

	try {
		test_a();
		test_gen40();
	}
	catch (std::exception& ex) {
		auto what = ex.what();
		std::cerr << what << std::endl;
		return -1;
	}

	return 0;
}