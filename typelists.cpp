
#include <tuple>

class A {};

class B : public A {};

class C : public B {};


typedef std::tuple<A, B, C> all_types;

static_assert(std::is_same<std::tuple_element<0, all_types>::type, A>::value, "Error");
static_assert(std::is_same<std::tuple_element<1, all_types>::type, B>::value, "Error");
static_assert(std::is_same<std::tuple_element<2, all_types>::type, C>::value, "Error");



template<typename T, bool>
struct selector {};

template<typename T>
struct selector<T, true> {
	typedef std::tuple<T> type;
};

template<typename T>
struct selector<T, false> {
	typedef std::tuple<> type;
};

template<typename T, typename U>
struct direct_subclasses {};

template<typename T, typename... Types>
struct direct_subclasses<T, std::tuple<Types...>>
{
	typedef typename selector<B, std::is_base_of<T, B>::value>::type type;
};

template<typename T, typename... Types>
struct direct_subclasses_impl
{
	typedef char type;
};

template<typename T, typename First, typename... Types>
struct direct_subclasses_impl
{
	typedef char type;
};

typedef direct_subclasses<A, all_types>::type a_subclasses;
typedef direct_subclasses_impl<A, A, B, C>::type a_subclasses2;

static_assert(std::is_same<std::tuple_element<0, a_subclasses>::type, B>::value, "error");

static_assert(std::is_same<std::tuple_element<0, a_subclasses2>::type, B>::value, "error");
