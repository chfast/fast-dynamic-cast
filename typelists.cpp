
#include <boost/mpl/list.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/comparison.hpp>

using namespace boost;
using namespace mpl;
using namespace mpl::placeholders;

template<typename Types, typename T> struct bases { using type = typename mpl::copy_if<Types, and_<not_<is_same<_1, T>>, is_base_of<_1, T>>, mpl::back_inserter<mpl::vector<>>>::type; };

template<typename Types> struct roots {
	using type = typename
		mpl::copy_if<Types, equal_to<size<bases<Types, _1>>, int_<0>>, back_inserter<vector<>>>::type;
};

template<typename Types, typename T> struct subs {
	using type = typename
		copy_if<Types, and_<not_<is_same<T, _1>>, is_base_of<T, _1>>, back_inserter<vector<>>>::type;
};

template<typename Types, typename T> struct dsubs {
	using _subs = typename subs<Types, T>::type;
	using type = typename roots<_subs>::type;
};




class A {};

class B: public A {};

class C: public B {};

using types = mpl::list<A, B, C>;

using a_bases = bases<types, A>::type;

//static_assert(is_same<mpl::front<a_bases>::type, A>::value, "");

static_assert(mpl::size<a_bases>::value == 0, "E");

using Roots = roots<types>::type;

static_assert(size<Roots>::value == 1, "");
static_assert(is_same<front<Roots>::type, A>::value, "");

using a_subs = subs<types, A>::type;
static_assert(size<a_subs>::value == 2, "");

using b_subs = subs<types, B>::type;
static_assert(size<b_subs>::value == 1, "");

using c_subs = subs<types, C>::type;
static_assert(size<c_subs>::value == 0, "");

using a_dsubs = dsubs<types, A>::type;
static_assert(size<a_dsubs>::value == 1, "");

using b_dsubs = dsubs<types, B>::type;
static_assert(size<b_dsubs>::value == 1, "");
