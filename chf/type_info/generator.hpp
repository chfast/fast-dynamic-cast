#pragma once

#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/max_element.hpp>

#include <chf/type_info.hpp>
#include <chf/type_list.hpp>

namespace chf
{
namespace type_info
{

template<typename> struct typelist2vector {};

template<typename... Ts> struct typelist2vector<chf::typelist<Ts...>>
    : boost::mpl::vector<Ts...> {};

template<typename BaseT, typename DerT>
struct is_strict_base_of
{
	static const bool value = !std::is_same<BaseT, DerT>::value && std::is_base_of<BaseT, DerT>::value;
};

using types = typelist2vector<tlist>::type;

using namespace boost::mpl;

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

template<typename T> struct bases_mpl
    : typelist2vector<typename bases<T>::type> {};

template<typename DerT, typename...> struct base2 { using type = void; };

template<typename DerT, typename T, typename... Ts> struct base2<DerT, typelist<T, Ts...>>
{
    using _tail = typename base2<DerT, typelist<Ts...>>::type;
    static const bool _is_base = is_strict_base_of<T, DerT>::value;
    static const bool _tail_better = !_is_base || is_strict_base_of<T, _tail>::value;
    using type = typename std::conditional<_tail_better, _tail, T>::type;
};

template<typename T> struct base {
    //using _bases = typename bases_mpl<T>::type;
	//using iter = typename max_element<_bases, is_strict_base_of<_1, _2>>::type;
	//using type = typename deref<iter>::type;

    using type = typename base2<T, tlist>::type;

	// TODO: What if already sorted by is_base_of
	//using type = typename back<_bases>::type;
};

template<typename T> struct is_root {
	static const bool value = std::is_same<T, typename T::root_class>::value;
};

template<typename T0, typename T> struct is_bro
{
	using _base0 = typename base<T0>::type;
	using _base = typename base<T>::type;
	static const bool value = std::is_same<_base0, _base>::value;
};

template<typename T> struct bros {
	using type = typename copy_if<types, is_bro<T, _>, back_inserter<vector<>>>::type;
};


template<typename T> struct level
    : tl_size<typename bases<T>::type> {}; // TODO: Use count_if


template<typename T> struct child_index {
	using _bros = typename bros<T>::type;
	using _it = typename find<_bros, T>::type;
	static const index_t value = _it::pos::value;
};

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