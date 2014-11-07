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

template<typename DstT, typename SrcT, bool always_true>
bool isa_select(SrcT const& obj) noexcept
{
	static_assert(!always_true, "Specialization error");
	return isa_impl<dst_type>(&obj);
}

template<typename DstT, typename SrcT>
bool isa_select<true>(SrcT const& obj) noexcept
{
	return true;
}

template<typename DstT, typename SrcT>
bool isa(SrcT const& obj) noexcept
{
	static const auto always_true = std::is_base_of<DstT, SrcT>::value;
	return isa_select<DstT, SrcT, always_true>(obj);
}

template<typename DstT, typename SrcT>
DstT* dyn_cast(SrcT* obj) noexcept
{
	return isa_impl<DstT>(obj) ? static_cast<DstT*>(obj) : nullptr;
}

}
}