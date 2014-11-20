
#include "gen40.hpp"

#define TYPES CLASSES

using namespace chf::test::gen40;

#include <chf/type_info/generator.hpp>

template void chf::type_info::register_classes<CLASSES>();
