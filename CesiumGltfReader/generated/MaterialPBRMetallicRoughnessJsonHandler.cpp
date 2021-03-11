// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#include "MaterialPBRMetallicRoughnessJsonHandler.h"
#include "CesiumGltf/MaterialPBRMetallicRoughness.h"

#include <cassert>
#include <string>

using namespace CesiumGltf;

MaterialPBRMetallicRoughnessJsonHandler::
    MaterialPBRMetallicRoughnessJsonHandler(ReadModelOptions options) noexcept
    : ExtensibleObjectJsonHandler(options),
      _baseColorFactor(options),
      _baseColorTexture(options),
      _metallicFactor(options),
      _roughnessFactor(options),
      _metallicRoughnessTexture(options) {}

void MaterialPBRMetallicRoughnessJsonHandler::reset(
    IJsonHandler* pParent,
    MaterialPBRMetallicRoughness* pObject) {
  ExtensibleObjectJsonHandler::reset(pParent, pObject);
  this->_pObject = pObject;
}

MaterialPBRMetallicRoughness*
MaterialPBRMetallicRoughnessJsonHandler::getObject() {
  return this->_pObject;
}

void MaterialPBRMetallicRoughnessJsonHandler::reportWarning(
    const std::string& warning,
    std::vector<std::string>&& context) {
  if (this->getCurrentKey()) {
    context.emplace_back(std::string(".") + this->getCurrentKey());
  }
  this->parent()->reportWarning(warning, std::move(context));
}

IJsonHandler* MaterialPBRMetallicRoughnessJsonHandler::Key(
    const char* str,
    size_t /*length*/,
    bool /*copy*/) {
  assert(this->_pObject);
  return this->MaterialPBRMetallicRoughnessKey(str, *this->_pObject);
}

IJsonHandler*
MaterialPBRMetallicRoughnessJsonHandler::MaterialPBRMetallicRoughnessKey(
    const char* str,
    MaterialPBRMetallicRoughness& o) {
  using namespace std::string_literals;

  if ("baseColorFactor"s == str)
    return property(
        "baseColorFactor",
        this->_baseColorFactor,
        o.baseColorFactor);
  if ("baseColorTexture"s == str)
    return property(
        "baseColorTexture",
        this->_baseColorTexture,
        o.baseColorTexture);
  if ("metallicFactor"s == str)
    return property("metallicFactor", this->_metallicFactor, o.metallicFactor);
  if ("roughnessFactor"s == str)
    return property(
        "roughnessFactor",
        this->_roughnessFactor,
        o.roughnessFactor);
  if ("metallicRoughnessTexture"s == str)
    return property(
        "metallicRoughnessTexture",
        this->_metallicRoughnessTexture,
        o.metallicRoughnessTexture);

  return this->ExtensibleObjectKey(str, *this->_pObject);
}
