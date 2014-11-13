
#pragma once

#include <type_traits>

namespace chf
{

template<typename... Ts> struct count_if
    : std::integral_constant<int, 0> {};

template<typename T, typename... Ts> struct count_if<T, Ts...>
    : std::integral_constant<int, std::is_integral<T>::value + count_if<Ts...>::value> {};


static_assert(count_if<int, int, float, void, long>::value == 3, "");
static_assert(count_if<>::value == 0, "");

}