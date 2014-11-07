#pragma once

#include <chf/type_info.hpp>

namespace chf
{
namespace type_info
{

template<typename T>
index_t get_class_index()
{
	return 0;
}

template<typename T>
bool isa_impl(typename const T::root_class*) noexcept
{
	return false;
}

}
}