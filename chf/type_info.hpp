#pragma once

#include <type_traits>

#define noexcept throw()

namespace chf
{
namespace type_info
{

using index_t = unsigned long long;

template<typename T>
index_t get_class_index();

template<typename T>
struct root
{
	using root_class = T;

	index_t class_index = 0;
};

template<typename T>
struct with
{
	with()
	{
		auto t = static_cast<T*>(this);
		t->class_index = get_class_index<T>();
	}
};

template<typename T>
bool isa_impl(typename const T::root_class*) noexcept;

template<typename DstT, typename SrcT>
auto isa(SrcT const& obj) noexcept -> typename std::enable_if<!std::is_base_of<DstT, SrcT>::value, bool>::type
{
	return isa_impl<DstT>(&obj);
}

template<typename DstT, typename SrcT>
auto isa(SrcT const& obj) noexcept -> typename std::enable_if<std::is_base_of<DstT, SrcT>::value, bool>::type
{
	return true;
}

template<typename DstT, typename SrcT>
DstT* dyn_cast(SrcT* obj) noexcept
{
	return isa_impl<DstT>(obj) ? static_cast<DstT*>(obj) : nullptr;
}

}
}