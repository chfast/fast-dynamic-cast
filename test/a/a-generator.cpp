
#include <boost/mpl/vector.hpp>
#include <chf/type_list.hpp>

#include "a.h"

using namespace fdctest::a;

#define TYPES Root, \
A0, A1, A2, A3, A4, \
B0, B1, B2, B3, B4, \
C0, C1, C2, C3, C4, \
D0, D1, D2, D3

using tlist = chf::typelist<TYPES>;

#include <chf/type_info/generator.hpp>

#include <chf/type_list.hpp>

template<typename T>
void gen(T*)
{
	chf::type_info::get_class_index<T>();
	chf::type_info::isa_impl<T>(nullptr);
}

template<typename... Types>
void gen_all()
{
	std::initializer_list<int> {(gen(static_cast<Types*>(nullptr)), 0)...};
}

void ff()	// TODO: Make this fake functions anonymous
{
	gen_all<TYPES>();
}

namespace fdctest {
namespace a {


void test_gen()
{
    using b1 = chf::type_info::base2<A0, tlist>::type;
    static_assert(std::is_same<b1, Root>::value, "");

    using b2 = chf::type_info::base2<C1, tlist>::type;
    static_assert(std::is_same<b2, B0>::value, "");

    using a = chf::type_info::bases_impl<Root, tlist>::type;
    static_assert(std::is_same<a, chf::typelist<>>::value, "");

    using b = chf::type_info::bases_impl<A0, tlist>::type;
    static_assert(std::is_same<b, chf::typelist<Root>>::value, "");

    using c = chf::type_info::bases_impl<B1, tlist>::type;
    static_assert(std::is_same<c, chf::typelist<Root, A0>>::value, "");
}

}}