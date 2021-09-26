// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#include "ClassJsonHandler.h"

#include "CesiumGltf/Class.h"

#include <cassert>
#include <string>

using namespace CesiumGltf;

ClassJsonHandler::ClassJsonHandler(const ReaderContext& context) noexcept
    : ExtensibleObjectJsonHandler(context),
      _name(),
      _description(),
      _properties(context) {}

void ClassJsonHandler::reset(
    CesiumJsonReader::IJsonHandler* pParentHandler,
    Class* pObject) {
  ExtensibleObjectJsonHandler::reset(pParentHandler, pObject);
  this->_pObject = pObject;
}

CesiumJsonReader::IJsonHandler*
ClassJsonHandler::readObjectKey(const std::string_view& str) {
  assert(this->_pObject);
  return this->readObjectKeyClass(Class::TypeName, str, *this->_pObject);
}

CesiumJsonReader::IJsonHandler* ClassJsonHandler::readObjectKeyClass(
    const std::string& objectType,
    const std::string_view& str,
    Class& o) {
  using namespace std::string_literals;

  if ("name"s == str)
    return property("name", this->_name, o.name);
  if ("description"s == str)
    return property("description", this->_description, o.description);
  if ("properties"s == str)
    return property("properties", this->_properties, o.properties);

  return this->readObjectKeyExtensibleObject(objectType, str, *this->_pObject);
}
