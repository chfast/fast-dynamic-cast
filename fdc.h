
#pragma once

namespace fdc {


template<typename T, Kind = type<T>::kind>
struct tier_of
{
	static const auto value = 0;
};

template<typename T>
struct tier_of<T, Kind::other>
{
	static const auto value = tier_of<type<T>::PrevT>::value;
};

template<typename T>
struct tier_of<T, Kind::first>
{
	static const auto value = tier_of<type<T>::BaseT>::value + 1;
};


template<typename T, Kind = type<T>::kind>
struct index_of
{
	static const auto value = 0;
};

template<typename T>
struct index_of<T, Kind::other>
{
	static const auto value = index_of<type<T>::PrevT>::value + 1;
};


template<typename T, Kind = type<T>::kind>
struct id_of
{
	static const auto value = 0;
};

template<typename T>
struct id_of<T, Kind::first>
{
	static const auto value = id_of<type<T>::BaseT>::value;
};

template<typename T>
struct id_of<T, Kind::other>
{
	static const auto offset = (8 * (8 - tier_of<T>::value));
	static const auto value = id_of<type<T>::PrevT>::value + (uint64_t(1) << offset);
};

template<typename T>
struct id
{
	static const auto tier = tier_of<T>::value;
	static const auto index = index_of<T>::value;
	static const auto value = id_of<T>::value;
};

template<typename BaseT, typename DerivedT>
bool isa(const DerivedT* d)
{
	auto bid = id<BaseT>::value;
	auto tier = id<BaseT>::tier;

	auto did = d->_typeid;
	const static uint64_t FULL_MASK = -1;
	auto mask = FULL_MASK << (8 * (sizeof(uint64_t) - tier));
	auto mdid = did & mask;
	auto r = mdid == bid;
	return r;
}

}