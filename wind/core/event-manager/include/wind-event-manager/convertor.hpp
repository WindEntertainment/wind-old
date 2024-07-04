#pragma once
#include <iostream>
#include <string>

namespace wind {

template <typename Struct>
const char* structToJsonObjectWithName(std::string name, Struct s);

template <typename Struct>
Struct jsonToStruct(const std::string& json);

template <typename Struct>
std::string structToJson(const Struct& s);

} // namespace wind
