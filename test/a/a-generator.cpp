
#include <chf/type_info/generator.hpp>

#include "a.h"

// Generate identifiers
template chf::type_info::index_t chf::type_info::get_class_index<fdctest::a::A0>();
template chf::type_info::index_t chf::type_info::get_class_index<fdctest::a::A1>();
template chf::type_info::index_t chf::type_info::get_class_index<fdctest::a::B0>();
template chf::type_info::index_t chf::type_info::get_class_index<fdctest::a::B1>();

namespace fdctest {
namespace a {


}}