
#include <boost/mpl/list.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/order.hpp>

using namespace boost;
using namespace mpl;
using namespace mpl::placeholders;

template<typename Types, typename T> struct bases { using type = typename mpl::copy_if<Types, and_<not_<is_same<_1, T>>, is_base_of<_1, T>>, mpl::back_inserter<mpl::vector<>>>::type; };


template<typename Types, typename T> struct is_root {
	using _bases = typename bases<Types, T>::type;
	using _size = typename size <_bases >::type;
	using type = typename equal_to<_size, int_<0>>::type;
	static const auto value = type::value;
};

template<typename Types> struct roots {
	using type = typename
		mpl::copy_if<Types, is_root<Types, _1>, back_inserter<vector<>>>::type;
};

template<typename Types, typename T> struct subs {
	using type = typename
		copy_if<Types, and_<not_<is_same<T, _1>>, is_base_of<T, _1>>, back_inserter<vector<>>>::type;
};

template<typename Types, typename T> struct dsubs {
	using _subs = typename subs<Types, T>::type;
	using type = typename roots<_subs>::type;
};

template<typename Types, typename T> struct dsubs_set {
	using _dsubs = typename dsubs<Types, T>::type;
	using type = typename fold<_dsubs, set<>, insert<_1, begin<_1>, _2>>::type;
};

template<typename Types, typename T> struct base {
	using _bases = typename  bases<Types, T>::type;
	using iter = typename find_if <_bases, contains<dsubs_set<Types, _1>, T> >::type;
	using type = typename deref<iter>::type;
};

template<typename Types, typename T> struct level;

template<typename Types, typename T, bool is_root> struct level_from_base {
	using _base = typename ::base<Types, T>::type;
	static const auto _base_level = typename level<Types, _base>::value;
	static const auto value = _base_level + 1;
};

template<typename Types, typename T> struct level_from_base<Types, T, true> {
	static const auto value = 0;
};

template<typename Types, typename T> struct level {
	static const auto _is_root = is_root<Types, T>::value;
	static const auto value = level_from_base<Types, T, _is_root>::value;
};

template<typename Types, typename T> struct child_order {
	using _base = typename ::base<Types, T>::type;
	using _bros = typename dsubs_set<Types, _base>::type;
	static const auto value = order<_bros, T>::value;
};

template<typename Types, typename T> struct child_index {
	using _base = typename ::base<Types, T>::type;
	using _bros = typename dsubs<Types, _base>::type;
	using _it = typename find<_bros, T>::type;
	static const auto value = _it::pos::value;
};




class A { using a = A; };

class B: public A { using b = B; };

class B2: public A {};

class C: public B { using c = C;  };

class C2: public B {};

using types = mpl::list<A, B, C, B2, C2>;

using a_bases = bases<types, A>::type;

//static_assert(is_same<mpl::front<a_bases>::type, A>::value, "");

static_assert(mpl::size<a_bases>::value == 0, "E");

using Roots = roots<types>::type;

static_assert(size<Roots>::value == 1, "");
static_assert(is_same<front<Roots>::type, A>::value, "");

using a_subs = subs<types, A>::type;
static_assert(size<a_subs>::value == 4, "");

using b_subs = subs<types, B>::type;
static_assert(size<b_subs>::value == 2, "");

using c_subs = subs<types, C>::type;
static_assert(size<c_subs>::value == 0, "");

using a_dsubs = dsubs<types, A>::type;
static_assert(size<a_dsubs>::value == 2, "");

using b_dsubs = dsubs<types, B>::type;
static_assert(size<b_dsubs>::value == 2, "");

using b_dsubs_set = dsubs_set<types, B>::type;
static_assert(size<b_dsubs_set>::value == 2, "");

using c_base = ::base<types, C>::type;

c_base ccc;
static_assert(is_same<::base<types, C>::type, B>::value, "");

static_assert(is_root<types, A>::value, "");

static_assert(level<types, A>::value == 0, "");

static_assert(level<types, B>::value == 1, "");

static_assert(level<types, C>::value == 2, "");

static_assert(child_order<types, B>::value == 2, "");
static_assert(child_index<types, B>::value == 0, "");
static_assert(child_index<types, B2>::value == 1, "");
static_assert(child_order<types, C>::value == 2, "");
static_assert(child_order<types, C2>::value == 3, "");
