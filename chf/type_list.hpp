
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

}