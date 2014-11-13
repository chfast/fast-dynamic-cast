#pragma once

#include <chf/type_info.hpp>

namespace chf
{
namespace type_info
{

// TODO Diagnostics: Root class cannot be on the list
// TODO Diagnostics: Only classes can be on list
// TODO Diagnostics: Unique types
// TODO Opt: Finding children once can be benefitial

template<typename BaseT, typename DerT> struct is_strict_base_of
    : std::integral_constant<bool, !std::is_same<BaseT, DerT>::value && std::is_base_of<BaseT, DerT>::value> {};

template<typename DerT, typename...> struct base2 { using type = void; };

template<typename DerT, typename T, typename... Ts> struct base2<DerT, T, Ts...>
{
    using _tail = typename base2<DerT, Ts...>::type;
    static const bool _is_base = is_strict_base_of<T, DerT>::value;
    static const bool _tail_better = !_is_base || is_strict_base_of<T, _tail>::value;
    using type = typename std::conditional<_tail_better, _tail, T>::type;
};

template<typename T> struct base
    : base2<T, TYPES> {}; // TODO: What if already sorted by is_base_of

template<typename T0, typename T> struct is_bro
{
	using _base0 = typename base<T0>::type;
	using _base = typename base<T>::type;
	static const bool value = std::is_same<_base0, _base>::value;
};


template<typename T> struct depth
	: std::integral_constant<index_t, depth<typename base<T>::type>::value + 1> {};

template<> struct depth<void>
	: std::integral_constant<index_t, 0> {};


template<index_t idx, typename ChildT, typename...> struct child_idx
{
    static const index_t value = -1;
};

template<index_t idx, typename ChildT, typename T, typename... Ts> struct child_idx<idx, ChildT, T, Ts...>
{
    static const bool _its_me = std::is_same<ChildT, T>::value;
    using _base = typename base<ChildT>::type;
    using _bro_base = typename base<T>::type;
    static const bool _is_bro = std::is_same<_base, _bro_base>::value;
    static const index_t curr_idx = idx + _is_bro;
    static const index_t value = _its_me ? idx : child_idx<curr_idx, ChildT, Ts...>::value;   // TODO: Use integra_constant here
	//static const index_t value = std::conditional<_its_me, std::integral_constant<index_t, idx>, std::integral_constant<index_t, child_idx<curr_idx, ChildT, typelist<Ts...>>::value>>::type::value;
};

template<typename T> struct child_index
    : child_idx<0, T, TYPES> {};


template<typename T> struct index {
	static const index_t depth = type_info::depth<T>::value;
	static const index_t _index = child_index<T>::value + 1;
	using _base = typename base<T>::type;
	static const index_t value = index<_base>::value + (_index << (8 * (depth - 1)));
};

template<> struct index<void> {
	static const index_t value = 0;
};

template<typename T>
index_t get_class_index()
{
	return index<T>::value;
}


template<typename T>
bool isa_impl(typename const T::root_class* obj) noexcept
{
	using dst_index = index<T>;
	static const index_t FULL_MASK = -1;
	static const auto mask = FULL_MASK << (8 * dst_index::depth);

	auto obj_index = obj->class_index;

	// TODO: Optimization
	//if (did == bid)
	//	return true;

	auto masked_index = obj_index & ~mask;
	auto r = masked_index == dst_index::value;
	return r;
}

}
}