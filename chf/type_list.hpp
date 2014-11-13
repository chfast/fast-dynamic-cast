
#pragma once

#include <type_traits>

namespace chf
{

template<typename... Ts> struct typelist {};

template<typename...> struct cat;

template<typename T, typename... Ts> struct cat<T, typelist<Ts...>>
{
    using type = typelist<T, Ts...>;
};

template<typename...> struct size;

template<typename... Ts> struct size<typelist<Ts...>>
    : std::integral_constant<size_t, sizeof...(Ts)> {};

}