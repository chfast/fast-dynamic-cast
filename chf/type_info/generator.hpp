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

namespace chf
{
namespace type_info
{

template<typename BaseT, typename DerT>
struct is_strict_base_of
{
	static const bool value = !std::is_same<BaseT, DerT>::value && std::is_base_of<BaseT, DerT>::value;
};


using namespace boost;
using namespace mpl;
using namespace mpl::placeholders;

template<typename Types, typename T> struct bases
{
	using type = typename mpl::copy_if<Types, is_strict_base_of<_1, T>, mpl::back_inserter<mpl::vector<>>>::type;
};

template<typename Types, typename T> struct base {
	using _bases = typename  bases<Types, T>::type;
	using iter = typename max_element<_bases, std::is_base_of<_1, _2>>::type;
	using type = typename deref<iter>::type;

	// TODO: What if already sorted by is_base_of
	//using type = typename back<_bases>::type;
};

template<typename Types, typename T> struct is_root {
	static const bool value = std::is_same<void_, typename base<Types, T>::type>::value;
};

template<typename Types> struct roots {
	using type = typename
		mpl::copy_if<Types, is_root<Types, _1>, back_inserter<vector<>>>::type;
};

template<typename Types, typename T> struct subs {
	using type = typename
		copy_if<Types, is_strict_base_of<T, _1>, back_inserter<vector<>>>::type;
};

template<typename Types, typename T> struct dsubs {
	using _subs = typename subs<Types, T>::type;
	using type = typename roots<_subs>::type;
};


template<typename Types, typename T> struct level {
	using _base = typename base<Types, T>::type;
	static const index_t value = level<Types, _base>::value + 1;
};

template<typename Types> struct level<Types, void_> {
	static const auto value = -1;
};


template<typename Types, typename T> struct child_index {
	using _base = typename type_info::base<Types, T>::type;
	using _bros = typename dsubs<Types, _base>::type;
	using _it = typename find<_bros, T>::type;
	static const index_t value = _it::pos::value;
};

template<typename Types, typename T> struct id;

template<typename Types, typename T, bool is_root> struct id_impl {
	static const index_t _level = level<Types, T>::value;
	static_assert(_level != 0, "not specialization for root");
	static const index_t _index = child_index<Types, T>::value + 1;
	using _base = typename type_info::base<Types, T>::type;
	static const index_t value = id<Types, _base>::value + (_index << (8 * (_level - 1)));
};

template<typename Types, typename T> struct id_impl<Types, T, true> {
	static const index_t value = 0;
};

template<typename Types, typename T> struct id {
	static const bool _is_root = is_root<Types, T>::value;
	static const index_t value = id_impl<Types, T, _is_root>::value;
};

template<typename T>
struct get_types;

template<typename T>
struct class_info
{
	using types = typename get_types<T>::types;
	static const index_t id = id<types, T>::value;
	static const index_t depth = level<types, T>::value;
};

template<typename T>
index_t get_class_index()
{
	return class_info<T>::id;
}


template<typename T>
bool isa_impl(typename const T::root_class* obj) noexcept
{
	static const auto bid = class_info<T>::id;
	static const auto depth = class_info<T>::depth;

	auto did = obj->class_index;

	// TODO: Optimization
	//if (did == bid)
	//	return true;

	static const index_t FULL_MASK = -1;
	auto mask = FULL_MASK << (8 * depth);	// static const
	auto mdid = did & ~mask;
	auto r = mdid == bid;
	return r;
}

}
}