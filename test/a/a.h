
#pragma once

#include "../../fdc-tag.h"

#include <chf/type_info.hpp>

namespace fdctest {
namespace a {

	class Root : public fdc::root, public chf::type_info::root<Root> {
	public:
		virtual ~Root();
	};


	class A0 : public Root, fdc::tag<A0>, chf::type_info::with<A0> {
	public:
		virtual ~A0();
	};

	class A1 : public Root, fdc::tag<A1>, chf::type_info::with<A1> {
	public:
		virtual ~A1();
	};

	class A2 : public Root, fdc::tag<A2>, chf::type_info::with<A2> {
	public:
		virtual ~A2();
	};

	class A3 : public Root, fdc::tag<A3>, chf::type_info::with<A3> {
	public:
		virtual ~A3();
	};

	class A4 : public Root, fdc::tag<A4>, chf::type_info::with<A4> {
	public:
		virtual ~A4();
	};


	class B0 : public A0, fdc::tag<B0>, chf::type_info::with<B0> {
	public:
		virtual ~B0();
	};
	class B1 : public A0, fdc::tag<B1>, chf::type_info::with<B1> {
	public:
		virtual ~B1();
	};
	class B2 : public A0, fdc::tag<B2>, chf::type_info::with<B2> {
	public:
		virtual ~B2();
	};
	class B3 : public A0, fdc::tag<B3>, chf::type_info::with<B3> {
	public:
		virtual ~B3();
	};
	class B4 : public A0, fdc::tag<B4>, chf::type_info::with<B4> {
	public:
		virtual ~B4();
	};


	class C0 : public B0, fdc::tag<C0>, chf::type_info::with<C0> {
	public:
		virtual ~C0();
	};
	class C1 : public B0, fdc::tag<C1>, chf::type_info::with<C1> {
	public:
		virtual ~C1();
	};
	class C2 : public B0, fdc::tag<C2>, chf::type_info::with<C2> {
	public:
		virtual ~C2();
	};
	class C3 : public B0, fdc::tag<C3>, chf::type_info::with<C3> {
	public:
		virtual ~C3();
	};
	class C4 : public B0, fdc::tag<C4>, chf::type_info::with<C4> {
	public:
		virtual ~C4();
	};


	class D0 : public C0, fdc::tag<D0>, chf::type_info::with<D0> {
	public:
		virtual ~D0();
	};
	class D1 : public C0, fdc::tag<D1>, chf::type_info::with<D1> {
	public:
		virtual ~D1();
	};
	class D2 : public C0, fdc::tag<D2>, chf::type_info::with<D2> {
	public:
		virtual ~D2();
	};
	class D3 : public C0, fdc::tag<D3>, chf::type_info::with<D3> {
	public:
		virtual ~D3();
	};

}}