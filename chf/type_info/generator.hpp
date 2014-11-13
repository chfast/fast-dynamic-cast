#pragma once

#include <chf/type_info.hpp>
#include <chf/type_list.hpp>

namespace chf
{
namespace type_info
{

template<typename BaseT, typename DerT> struct is_strict_base_of
    : std::integral_constant<bool, !std::is_same<BaseT, DerT>::value && std::is_base_of<BaseT, DerT>::value> {};


template<typename DerT, typename...> struct bases_impl
{
    using type = typelist<>;
};

template<typename DerT, typename T, typename... Ts> struct bases_impl<DerT, typelist<T, Ts...>>
{
    static const bool _is = is_strict_base_of<T, DerT>::value;
    using _tail = typename bases_impl<DerT, typelist<Ts...>>::type;
    using _cat = typename cat<T, _tail>::type;
    using type = typename std::conditional<_is, _cat, _tail>::type;
};

template<typename T> struct bases
    : bases_impl<T, tlist> {};


template<typename DerT, typename...> struct base2 { using type = void; };

template<typename DerT, typename T, typename... Ts> struct base2<DerT, typelist<T, Ts...>>
{
    using _tail = typename base2<DerT, typelist<Ts...>>::type;
    static const bool _is_base = is_strict_base_of<T, DerT>::value;
    static const bool _tail_better = !_is_base || is_strict_base_of<T, _tail>::value;
    using type = typename std::conditional<_tail_better, _tail, T>::type;
};

template<typename T> struct base
    : base2<T, tlist> {}; // TODO: What if already sorted by is_base_of


template<typename T> struct is_root {
	static const bool value = std::is_same<T, typename T::root_class>::value;
};

template<typename T0, typename T> struct is_bro
{
	using _base0 = typename base<T0>::type;
	using _base = typename base<T>::type;
	static const bool value = std::is_same<_base0, _base>::value;
};

template<typename T> struct level
    : size<typename bases<T>::type> {}; // TODO: Use count_if


template<index_t idx, typename ChildT, typename...> struct child_idx
{
    static const index_t value = -1;
};

template<index_t idx, typename ChildT, typename T, typename... Ts> struct child_idx<idx, ChildT, typelist<T, Ts...>>
{
    static const bool _its_me = std::is_same<ChildT, T>::value;
    using _base = typename base<ChildT>::type;
    using _bro_base = typename base<T>::type;
    static const bool _is_bro = std::is_same<_base, _bro_base>::value;
    static const index_t curr_idx = idx + _is_bro;
    static const index_t value = _its_me ? idx : child_idx<curr_idx, ChildT, typelist<Ts...>>::value;   // TODO: Use integra_constant here
};

template<typename T> struct child_index
    : child_idx<0, T, tlist> {};


template<typename T> struct id;

template<typename T, bool is_root> struct id_impl {
	static const index_t _level = level<T>::value;
	static_assert(_level != 0, "not specialization for root");
	static const index_t _index = child_index<T>::value + 1;
	using _base = typename base<T>::type;
	static const index_t value = id<_base>::value + (_index << (8 * (_level - 1)));
};

template<typename T> struct id_impl<T, true> {
	static const index_t value = 0;
};

template<typename T> struct id {
	static const bool _is_root = is_root<T>::value;
	static const index_t value = id_impl<T, _is_root>::value;
};


template<typename T>
struct class_info
{
	static const index_t id = id<T>::value;
	static const index_t depth = level<T>::value;
};

template<typename T>
index_t get_class_index()
{
	return class_info<T>::id;
}


template<typename T>
bool isa_impl(typename const T::root_class* obj) noexcept
{
	static const auto dst_index = class_info<T>::id;
	static const auto depth = class_info<T>::depth;
	static const index_t FULL_MASK = -1;
	static const auto mask = FULL_MASK << (8 * depth);

	auto obj_index = obj->class_index;

	// TODO: Optimization
	//if (did == bid)
	//	return true;

	auto masked_index = obj_index & ~mask;
	auto r = masked_index == dst_index;
	return r;
}

}
}