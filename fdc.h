
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
	static const auto value = 1;
};

template<typename T>
struct index_of<T, Kind::other>
{
	static const auto value = index_of<type<T>::PrevT>::value + 1;
};


template<typename T, Kind = type<T>::kind>
struct id_of
{
	static const auto value = 0; //static_cast<uint64_t>(-1);
};

template<typename T>
struct id_of<T, Kind::first>
{
	//static const auto offset = (8 * (8 - tier_of<T>::value));
	//static const auto value = id_of<type<T>::BaseT>::value & ~(uint64_t(1) << offset);
	static const auto mask = 0x0100000000000000 >> (8*(tier_of<T>::value - 1));
	static const auto value = id_of<type<T>::BaseT>::value | mask;
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
	auto bid = id<BaseT>::value;	// static const
	auto tier = id<BaseT>::tier;	// static const

	auto did = d->_typeid;

	// TODO: Optimization
	//if (did == bid)
	//	return true;

	static const uint64_t FULL_MASK = -1;
	auto mask = FULL_MASK >> (8 * tier);	// static const
	auto mdid = did & ~mask;
	auto r = mdid == bid;
	return r;
}

}