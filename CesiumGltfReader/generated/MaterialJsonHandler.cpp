// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#include "MaterialJsonHandler.h"
#include "CesiumGltf/Material.h"

#include <cassert>
#include <string>

using namespace CesiumGltf;

MaterialJsonHandler::MaterialJsonHandler(ReadModelOptions options) noexcept
    : NamedObjectJsonHandler(options),
      _pbrMetallicRoughness(options),
      _normalTexture(options),
      _occlusionTexture(options),
      _emissiveTexture(options),
      _emissiveFactor(options),
      _alphaMode(options),
      _alphaCutoff(options),
      _doubleSided(options) {}

void MaterialJsonHandler::reset(IJsonHandler* pParent, Material* pObject) {
  NamedObjectJsonHandler::reset(pParent, pObject);
  this->_pObject = pObject;
}

Material* MaterialJsonHandler::getObject() { return this->_pObject; }

void MaterialJsonHandler::reportWarning(
    const std::string& warning,
    std::vector<std::string>&& context) {
  if (this->getCurrentKey()) {
    context.emplace_back(std::string(".") + this->getCurrentKey());
  }
  this->parent()->reportWarning(warning, std::move(context));
}

IJsonHandler*
MaterialJsonHandler::Key(const char* str, size_t /*length*/, bool /*copy*/) {
  assert(this->_pObject);
  return this->MaterialKey(str, *this->_pObject);
}

IJsonHandler* MaterialJsonHandler::MaterialKey(const char* str, Material& o) {
  using namespace std::string_literals;

  if ("pbrMetallicRoughness"s == str)
    return property(
        "pbrMetallicRoughness",
        this->_pbrMetallicRoughness,
        o.pbrMetallicRoughness);
  if ("normalTexture"s == str)
    return property("normalTexture", this->_normalTexture, o.normalTexture);
  if ("occlusionTexture"s == str)
    return property(
        "occlusionTexture",
        this->_occlusionTexture,
        o.occlusionTexture);
  if ("emissiveTexture"s == str)
    return property(
        "emissiveTexture",
        this->_emissiveTexture,
        o.emissiveTexture);
  if ("emissiveFactor"s == str)
    return property("emissiveFactor", this->_emissiveFactor, o.emissiveFactor);
  if ("alphaMode"s == str)
    return property("alphaMode", this->_alphaMode, o.alphaMode);
  if ("alphaCutoff"s == str)
    return property("alphaCutoff", this->_alphaCutoff, o.alphaCutoff);
  if ("doubleSided"s == str)
    return property("doubleSided", this->_doubleSided, o.doubleSided);

  return this->NamedObjectKey(str, *this->_pObject);
}

void MaterialJsonHandler::AlphaModeJsonHandler::reset(
    IJsonHandler* pParent,
    Material::AlphaMode* pEnum) {
  JsonHandler::reset(pParent);
  this->_pEnum = pEnum;
}

IJsonHandler* MaterialJsonHandler::AlphaModeJsonHandler::String(
    const char* str,
    size_t /*length*/,
    bool /*copy*/) {
  using namespace std::string_literals;

  assert(this->_pEnum);

  if ("OPAQUE"s == str)
    *this->_pEnum = Material::AlphaMode::OPAQUE;
  else if ("MASK"s == str)
    *this->_pEnum = Material::AlphaMode::MASK;
  else if ("BLEND"s == str)
    *this->_pEnum = Material::AlphaMode::BLEND;
  else
    return nullptr;

  return this->parent();
}
