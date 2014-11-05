
#pragma once

#define BOOST_MPL_LIMIT_VECTOR_SIZE 50

#include <boost/mpl/vector.hpp>

#include "a.h"


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