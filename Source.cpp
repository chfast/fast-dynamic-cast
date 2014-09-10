
#include <cstdint>

#include <string>


#define H(...)

class A;

std::string debugId(uint64_t id, int tier)
{
    static const uint64_t B = 256;

    id /= (B << ( 8 *(8 - tier - 1)));

    std::string did;
    for (auto i = 0; i < tier; ++i)
    {
        auto r = id % B;
        if (did.empty())
            did = std::to_string(r);
        else
            did = std::to_string(r) + "-" + did;
        id /= B;
    }

    return did;
}

// TODO: Disallow not related classes
template<typename BaseT, typename DerivedT>
bool isa(const DerivedT* d)
{
    auto bid = id<BaseT>::value;
    auto tier = id<BaseT>::tier;

    auto did = d->id;
    const static uint64_t FULL_MASK = -1;
    auto mask = FULL_MASK << (8 * (sizeof(uint64_t) - tier -1));
    auto mdid = did & mask;
    auto r = mdid == bid;
    return r;
}


enum class Kind
{
    root, first, other
};


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
struct tag
{
    tag()
    {
        auto t = static_cast<T*>(this);
        t->id = id<T>::value;
    }
};


class A : tag<A> {
public:
    uint64_t id;
};

class B : public A, tag<B>
{};

class C : public A, tag<C>
{};

class E : public C, tag<E>
{};

class F : public C, tag<F>
{};

class X {};


template<typename T>
struct type
{
};

struct root
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


template<> struct type<A> : root {};
template<> struct type<B> : extends<A> {};
template<> struct type<C> : nextof<B> {};
template<> struct type<E> : extends<C> {};
template<> struct type<F> : nextof<E> {};


// TODO: Optimize root type - always true
template<typename T>
struct id
{    
    static const auto tier = tier_of<T>::value;
    static const auto index = index_of<T>::value;
    static const auto value = id_of<T>::value;
};

int main()
{
    auto ta = id<A>::tier;
    auto tb = id<B>::tier;
    auto tc = id<C>::tier;
    auto te = id<E>::tier;
    auto tf = id<F>::tier;

    auto ia = id<A>::index;
    auto ib = id<B>::index;
    auto ic = id<C>::index;
    auto ie = id<E>::index;
    auto iF = id<F>::index;

    auto iia = id<A>::value;
    auto iib = id<B>::value;
    auto iic = id<C>::value;
    auto iie = id<E>::value;
    auto iiF = id<F>::value;


    C c;

    auto idC = debugId(c.id, id<C>::tier);

    
    F f;
    auto idF = debugId(f.id, id<F>::tier);

    /*C c;
    auto cid = c.id;
    auto _cid = debugId(cid);
    auto xid = id<C>::value;
    auto _xid = debugId(xid);

    auto is1 = isa<A>(&c);
    auto is2 = isa<B>(&c);
    auto is3 = isa<C>(&c);*/
    //auto isX = isa<X>(&c);

    

    return 0;
}

