
#include <chf/type_info/generator.hpp>

#include "a.h"

using namespace fdctest::a;

#define TYPES Root, \
A0, A1, A2, A3, A4, \
B0, B1, B2, B3, B4, \
C0, C1, C2, C3, C4, \
D0, D1, D2, D3

template<typename T>
struct chf::type_info::get_types {
	using types = boost::mpl::vector<TYPES>::type;
};

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

	using types = chf::type_info::get_types<void>::types;
	using b1_base = chf::type_info::base<types, B1>::type;

	b1_base* a1b = nullptr;

	a1b = nullptr;

	static_assert(std::is_same<A0, b1_base>::value, "");
}

}}