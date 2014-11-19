
#pragma once

#include <iostream>

namespace chf
{
namespace test
{
	
template<typename ObjectT, typename ClassT>
void test_isa()
{
	ObjectT::root_class* ref = new ObjectT;
	auto isa = chf::type_info::isa<ClassT>(*ref);
	auto dyn = dynamic_cast<ClassT*>(ref) != nullptr;
	if (isa != dyn)
	{
		auto msg = std::string() + typeid(ObjectT).name() + " is " + (isa ? "not " : "") + "a " + typeid(ClassT).name();
		throw std::bad_cast(msg.c_str());
	}
}

template<typename T, typename U>
void fake_test()
{
	std::cout << "Testing " << typeid(T).name() << " - " << typeid(T).name() << std::endl;
}

template<typename...>
struct outter
{
};

template<template<typename> class Tpl, typename ClassT>
struct outter<Tpl<ClassT>>
{
	static void go() {}
};

template<typename... ClassTs>
void test_classes()
{
	//using tpl = outter<void>;
	//outter<tpl>::go();
	std::initializer_list<int> {(fake_test<ClassTs, ClassTs>(), 0)...};
}


}
}