
#include "fdc.h"




class A { using a = A; };

class B: public A { using b = B; };

class B2: public A {};

class C: public B { using c = C;  };

class C2: public B {};

namespace fdc {
template<typename T>
struct get_types {
	using types = boost::mpl::list<A, B, C, C2, B2>::type;
};
}

using namespace fdc;

using types = get_types<int>::types;
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

static_assert(id<types, A>::value == 0, "");
static_assert(id<types, B>::value == 0x01, "");
static_assert(id<types, B2>::value == 0x02, "");
static_assert(id<types, C>::value == 0x0101, "");
static_assert(id<types, C2>::value == 0x0201, "");
