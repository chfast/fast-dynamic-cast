
#pragma once

#include <chf/type_info.hpp>

namespace fdctest {
namespace a {

	class Root : public chf::type_info::root<Root> {
	public:
        virtual ~Root() = default;
	};

	class A0 : public Root, chf::type_info::with<A0> {};
	class A1 : public Root, chf::type_info::with<A1> {};
	class A2 : public Root, chf::type_info::with<A2> {};
	class A3 : public Root, chf::type_info::with<A3> {};
	class A4 : public Root, chf::type_info::with<A4> {};

	class B0 : public A0, chf::type_info::with<B0> {};
	class B1 : public A0, chf::type_info::with<B1> {};
	class B2 : public A0, chf::type_info::with<B2> {};
	class B3 : public A0, chf::type_info::with<B3> {};
	class B4 : public A0, chf::type_info::with<B4> {};

	class C0 : public B0, chf::type_info::with<C0> {};
	class C1 : public B0, chf::type_info::with<C1> {};
	class C2 : public B0, chf::type_info::with<C2> {};
	class C3 : public B0, chf::type_info::with<C3> {};
    class C4 : public B0, chf::type_info::with<C4> {};

    class D0 : public C0, chf::type_info::with<D0> {};
    class D1 : public C0, chf::type_info::with<D1> {};
    class D2 : public C0, chf::type_info::with<D2> {};
    class D3 : public C0, chf::type_info::with<D3> {};
    class D4 : public C0, chf::type_info::with<D4> {};

    class E0 : public D0, chf::type_info::with<E0> {};
    class E1 : public D0, chf::type_info::with<E1> {};
    class E2 : public D0, chf::type_info::with<E2> {};
    class E3 : public D0, chf::type_info::with<E3> {};
    class E4 : public D0, chf::type_info::with<E4> {};

    class F0 : public E0, chf::type_info::with<F0> {};
    class F1 : public E0, chf::type_info::with<F1> {};
    class F2 : public E0, chf::type_info::with<F2> {};
    class F3 : public E0, chf::type_info::with<F3> {};
    class F4 : public E0, chf::type_info::with<F4> {};

#define TYPES \
A0, A1, A2, A3, A4, \
B0, B1, B2, B3, B4, \
C0, C1, C2, C3, C4, \
D0, D1, D2, D3, D4, \
E0, E1, E2, E3, E4, \
F0, F1, F2, F3, F4

}}