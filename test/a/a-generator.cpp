#include "a.h"

using namespace fdctest::a;


#include <chf/type_info/generator.hpp>

void ff()	// TODO: Use template instance
{
	chf::type_info::register_classes<TYPES>();
}

namespace fdctest {
namespace a {


void test_gen()
{
	using b1 = chf::type_info::base2<A0, TYPES>::type;
    static_assert(std::is_same<b1, void>::value, "");

    using b2 = chf::type_info::base2<C1, TYPES>::type;
    static_assert(std::is_same<b2, B0>::value, "");
}

}}