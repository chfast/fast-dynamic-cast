
#pragma once

#include <iostream>

namespace chf
{
namespace test
{
	
template<typename ObjectT, typename ClassT>
void test_isa()
{
	// TODO: Record test statistics, timmings
	std::cout << "Testing " << typeid(ClassT).name() << " - " << typeid(ObjectT).name() << std::endl;
	ObjectT::root_class* ref = new ObjectT;
	auto isa = chf::type_info::isa<ClassT>(*ref);
	auto dyn = dynamic_cast<ClassT*>(ref) != nullptr;
	if (isa != dyn)
	{
		auto msg = std::string() + typeid(ObjectT).name() + " is " + (isa ? "not " : "") + "a " + typeid(ClassT).name();
		throw std::bad_cast(msg.c_str());
	}
}

template<typename... OuterTs>
struct outer_tester
{
	template<typename... InTs>
	static void inner_tester() {}
};

template<typename OuterT, typename... OuterTs>
struct outer_tester<OuterT, OuterTs...>
{
	template<typename... InnerTs>
	static void inner_tester()
	{
		std::initializer_list<int> {(test_isa<OuterT, InnerTs>(), 0)...};
		outer_tester<OuterTs...>::inner_tester<InnerTs...>();
	}
};

template<typename... ClassTs>
void test_classes()
{
	outer_tester<ClassTs...>::inner_tester<ClassTs...>();
}


}
}