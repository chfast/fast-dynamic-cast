#include <chf/type_info.hpp>

namespace chf
{
namespace test
{
namespace gen40
{

template<typename T> using ci = type_info::with<T>;
template<typename T> using ci_root = type_info::root<T>;

class Root : public ci_root<Root> { public: virtual ~Root() {} };
class A1 : public Root, ci<A1> {};
class A1_B1 : public A1, ci<A1_B1> {};
class A1_B1_C1 : public A1_B1, ci<A1_B1_C1> {};
class A1_B1_C2 : public A1_B1, ci<A1_B1_C2> {};
class A1_B1_C3 : public A1_B1, ci<A1_B1_C3> {};
class A1_B1_C4 : public A1_B1, ci<A1_B1_C4> {};
class A1_B1_C5 : public A1_B1, ci<A1_B1_C5> {};
class A1_B1_C6 : public A1_B1, ci<A1_B1_C6> {};
class A1_B1_C6_D1 : public A1_B1_C6, ci<A1_B1_C6_D1> {};
class A1_B1_C6_D2 : public A1_B1_C6, ci<A1_B1_C6_D2> {};
class A1_B1_C6_D3 : public A1_B1_C6, ci<A1_B1_C6_D3> {};
class A1_B1_C6_D4 : public A1_B1_C6, ci<A1_B1_C6_D4> {};
class A2 : public Root, ci<A2> {};
class A3 : public Root, ci<A3> {};
class A4 : public Root, ci<A4> {};
class A5 : public Root, ci<A5> {};
class A6 : public Root, ci<A6> {};
class A7 : public Root, ci<A7> {};
class A8 : public Root, ci<A8> {};
class A9 : public Root, ci<A9> {};
class A9_B1 : public A9, ci<A9_B1> {};
class A9_B2 : public A9, ci<A9_B2> {};
class A9_B3 : public A9, ci<A9_B3> {};
class A9_B4 : public A9, ci<A9_B4> {};
class A9_B5 : public A9, ci<A9_B5> {};
class A9_B5_C1 : public A9_B5, ci<A9_B5_C1> {};
class A9_B5_C1_D1 : public A9_B5_C1, ci<A9_B5_C1_D1> {};
class A9_B5_C1_D2 : public A9_B5_C1, ci<A9_B5_C1_D2> {};
class A9_B5_C1_D3 : public A9_B5_C1, ci<A9_B5_C1_D3> {};
class A9_B5_C1_D4 : public A9_B5_C1, ci<A9_B5_C1_D4> {};
class A9_B5_C1_D5 : public A9_B5_C1, ci<A9_B5_C1_D5> {};
class A9_B5_C1_D6 : public A9_B5_C1, ci<A9_B5_C1_D6> {};
class A9_B5_C1_D7 : public A9_B5_C1, ci<A9_B5_C1_D7> {};
class A10 : public Root, ci<A10> {};

#define CLASSES Root, A1, A1_B1, A1_B1_C1, A1_B1_C2, A1_B1_C3, A1_B1_C4, A1_B1_C5, A1_B1_C6, A1_B1_C6_D1, A1_B1_C6_D2, A1_B1_C6_D3, A1_B1_C6_D4, A2, A3, A4, A5, A6, A7, A8, A9, A9_B1, A9_B2, A9_B3, A9_B4, A9_B5, A9_B5_C1, A9_B5_C1_D1, A9_B5_C1_D2, A9_B5_C1_D3, A9_B5_C1_D4, A9_B5_C1_D5, A9_B5_C1_D6, A9_B5_C1_D7, A10
}
}
}