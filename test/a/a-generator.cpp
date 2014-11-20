#include "a.h"

using namespace chf::test::a;

#include <chf/type_info/generator.hpp>

template struct chf::type_info::registrar<classes>;
