#pragma once

namespace chf
{
namespace type_info
{

using index_t = unsigned long long;

template<typename T>
index_t get_class_index();

template<typename T>
struct root
{
	index_t class_index = 0;
};

template<typename T>
struct with
{
	with()
	{
		auto t = static_cast<T*>(this);
		t->class_index = get_class_index<T>();
	}
};

}
}
