
#include "a.h"

#include <chf/type_info.hpp>
#include <test/helper.hpp>

#include <stdexcept>
#include <string>

namespace fdctest {
namespace a {

void test_gen();

void test()
{
	test_gen();

	chf::test::test_classes<TYPES>();
}


}}