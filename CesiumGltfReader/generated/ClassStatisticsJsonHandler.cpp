// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#include "ClassStatisticsJsonHandler.h"

#include "CesiumGltf/ClassStatistics.h"

#include <cassert>
#include <string>

using namespace CesiumGltf;

ClassStatisticsJsonHandler::ClassStatisticsJsonHandler(
    const ReaderContext& context) noexcept
    : ExtensibleObjectJsonHandler(context), _count(), _properties(context) {}

void ClassStatisticsJsonHandler::reset(
    CesiumJsonReader::IJsonHandler* pParentHandler,
    ClassStatistics* pObject) {
  ExtensibleObjectJsonHandler::reset(pParentHandler, pObject);
  this->_pObject = pObject;
}

CesiumJsonReader::IJsonHandler*
ClassStatisticsJsonHandler::readObjectKey(const std::string_view& str) {
  assert(this->_pObject);
  return this->readObjectKeyClassStatistics(
      ClassStatistics::TypeName,
      str,
      *this->_pObject);
}

CesiumJsonReader::IJsonHandler*
ClassStatisticsJsonHandler::readObjectKeyClassStatistics(
    const std::string& objectType,
    const std::string_view& str,
    ClassStatistics& o) {
  using namespace std::string_literals;

  if ("count"s == str)
    return property("count", this->_count, o.count);
  if ("properties"s == str)
    return property("properties", this->_properties, o.properties);

  return this->readObjectKeyExtensibleObject(objectType, str, *this->_pObject);
}
