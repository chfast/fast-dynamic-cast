
#pragma once

#include <cstdint>

namespace fdc {

template<typename T>
struct tag
{
	tag()
	{
		auto t = static_cast<T*>(this);
		t->_typeid = id<T>::value;
	}
};

struct root
{
public:
	uint64_t _typeid = -1;
};

}