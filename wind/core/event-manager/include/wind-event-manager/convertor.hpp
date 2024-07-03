#pragma once
#include <boost/hana.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <string>

namespace wind {

namespace pt = boost::property_tree;
namespace hana = boost::hana;

template <typename Struct>
const char* structToJsonObjectWithName(std::string name, Struct s);

template <typename Struct>
Struct jsonToStruct(const std::string& json);

template <typename Struct>
std::string structToJson(const Struct& s);

} // namespace wind
