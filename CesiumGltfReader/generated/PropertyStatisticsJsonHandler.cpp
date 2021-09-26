// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#include "PropertyStatisticsJsonHandler.h"

#include "CesiumGltf/PropertyStatistics.h"

#include <cassert>
#include <string>

using namespace CesiumGltf;

PropertyStatisticsJsonHandler::PropertyStatisticsJsonHandler(
    const ReaderContext& context) noexcept
    : ExtensibleObjectJsonHandler(context),
      _min(),
      _max(),
      _mean(),
      _median(),
      _standardDeviation(),
      _variance(),
      _sum(),
      _occurrences() {}

void PropertyStatisticsJsonHandler::reset(
    CesiumJsonReader::IJsonHandler* pParentHandler,
    PropertyStatistics* pObject) {
  ExtensibleObjectJsonHandler::reset(pParentHandler, pObject);
  this->_pObject = pObject;
}

CesiumJsonReader::IJsonHandler*
PropertyStatisticsJsonHandler::readObjectKey(const std::string_view& str) {
  assert(this->_pObject);
  return this->readObjectKeyPropertyStatistics(
      PropertyStatistics::TypeName,
      str,
      *this->_pObject);
}

CesiumJsonReader::IJsonHandler*
PropertyStatisticsJsonHandler::readObjectKeyPropertyStatistics(
    const std::string& objectType,
    const std::string_view& str,
    PropertyStatistics& o) {
  using namespace std::string_literals;

  if ("min"s == str)
    return property("min", this->_min, o.min);
  if ("max"s == str)
    return property("max", this->_max, o.max);
  if ("mean"s == str)
    return property("mean", this->_mean, o.mean);
  if ("median"s == str)
    return property("median", this->_median, o.median);
  if ("standardDeviation"s == str)
    return property(
        "standardDeviation",
        this->_standardDeviation,
        o.standardDeviation);
  if ("variance"s == str)
    return property("variance", this->_variance, o.variance);
  if ("sum"s == str)
    return property("sum", this->_sum, o.sum);
  if ("occurrences"s == str)
    return property("occurrences", this->_occurrences, o.occurrences);

  return this->readObjectKeyExtensibleObject(objectType, str, *this->_pObject);
}
