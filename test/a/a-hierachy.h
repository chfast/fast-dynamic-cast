
#pragma once

#define BOOST_MPL_LIMIT_VECTOR_SIZE 50

#include <boost/mpl/vector.hpp>

#include "a.h"

#include "../../fdc-hierarchy.h"

using namespace fdctest::a;

namespace fdc {
template<typename T>
struct get_types {
	using types = boost::mpl::vector<
		Root,
		A0, A1, A2, A3, A4,
		B0, B1, B2, B3, B4,
		C0, C1, C2, C3, C4,
		D0, D1, D2, D3
	>::type;
};
}

ROOT(Root)

TYPE(A0) EXTENDS(Root)
TYPE(A1) NEXTOF(A0)
TYPE(A2) NEXTOF(A1)
TYPE(A3) NEXTOF(A2)
TYPE(A4) NEXTOF(A3)

TYPE(B0) EXTENDS(A0)
TYPE(B1) NEXTOF(B0)
TYPE(B2) NEXTOF(B1)
TYPE(B3) NEXTOF(B2)
TYPE(B4) NEXTOF(B3)

TYPE(C0) EXTENDS(B0)
TYPE(C1) NEXTOF(C0)
TYPE(C2) NEXTOF(C1)
TYPE(C3) NEXTOF(C2)
TYPE(C4) NEXTOF(C3)

TYPE(D0) EXTENDS(C0)
TYPE(D1) NEXTOF(D0)
TYPE(D2) NEXTOF(D1)
TYPE(D3) NEXTOF(D2)
