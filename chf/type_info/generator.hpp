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
// TODO Opt: no abstract classes

using index0_type = std::integral_constant<index_t, 0>;

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


template<typename T> struct depth
	: std::integral_constant<index_t, depth<typename base<T>::type>::value + 1> {};

template<> struct depth<void> : index0_type {};


template<index_t idx, typename ChildT, typename...> struct child_idx : index0_type {}; // TODO: Can be undefined?

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


template<typename T> struct index {
	static const index_t _index = child_idx<1, T, TYPES>::value;
	using _base = typename base<T>::type;
	static const index_t value = index<_base>::value + (_index << (8 * depth<_base>::value));
};

template<> struct index<void> : index0_type {};

template<typename T>
index_t get_class_index() // TODO: constexpr?
{
	return index<T>::value;
}


template<typename T>
bool isa_impl(typename const T::root_class* obj) noexcept
{
	// TODO: Optimization equal indexes

	static const index_t mask = (index_t(1) << (8 * depth<T>::value)) - 1;
	auto obj_index = obj->class_index;
	auto masked_index = obj_index & mask;
	return masked_index == index<T>::value;
}


template<typename T>
void gen(T*) // TODO: Remove fake param - not needed, use explicit template param type
{
	chf::type_info::get_class_index<T>();
	chf::type_info::isa_impl<T>(nullptr);
}

template<typename... Types>
void register_classes()
{
	std::initializer_list<int> {(gen(static_cast<Types*>(nullptr)), 0)...};
}

}
}