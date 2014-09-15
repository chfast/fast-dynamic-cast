
#pragma once

namespace fdc {



enum class Kind
{
	root, first, other
};

template<typename T>
struct type
{
};

struct top
{
	static const auto kind = Kind::root;
};

template<typename T>
struct extends
{
	static const auto kind = Kind::first;
	typedef T BaseT;
};

template<typename T>
struct nextof
{
	static const auto kind = Kind::other;
	typedef T PrevT;
};

}

#define ROOT(CLASS) namespace fdc { template<> struct type<CLASS> : top{}; }

#define TYPE(CLASS) namespace fdc { template<> struct type<CLASS> : 
#define EXTENDS(CLASS) extends<CLASS> {}; }
#define NEXTOF(CLASS) nextof<CLASS> {}; }