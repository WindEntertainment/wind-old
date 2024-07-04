#include "wind-event-manager/convertor.hpp"
#include <boost/hana.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace wind {
namespace pt = boost::property_tree;
namespace hana = boost::hana;

template <typename Struct>
const char* structToJsonObjectWithName(std::string name, Struct s) {
  pt::ptree tree;
  tree.put("name", name);
  tree.put("data", wind::structToJson<Struct>(s));

  std::ostringstream oss;
  pt::write_json(oss, tree);

  std::string jsonStr = oss.str();
  const char* jsonCStr = jsonStr.c_str();
  return jsonCStr;
};

template <typename Struct>
Struct jsonToStruct(const std::string& json) {
  pt::ptree tree;
  std::istringstream ss(json);
  pt::read_json(ss, tree);

  Struct result;
  hana::for_each(hana::keys(result), [&](auto key) {
    auto value = tree.get<decltype(hana::at_key(result, key))>(key);
    hana::at_key(result, key) = value;
  });

  return result;
}

template <typename Struct>
std::string structToJson(const Struct& s) {
  pt::ptree tree;

  hana::for_each(hana::keys(s), [&](auto key) {
    auto value = hana::at_key(s, key);
    tree.put(key.c_str(), value);
  });

  std::ostringstream oss;
  pt::write_json(oss, tree);
  return oss.str();
}
} // namespace wind
