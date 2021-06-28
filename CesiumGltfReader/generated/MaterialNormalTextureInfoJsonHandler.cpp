// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#include "MaterialNormalTextureInfoJsonHandler.h"
#include "CesiumGltf/MaterialNormalTextureInfo.h"

#include <cassert>
#include <string>

using namespace CesiumGltf;

MaterialNormalTextureInfoJsonHandler::MaterialNormalTextureInfoJsonHandler(const ReaderContext& context) noexcept : TextureInfoJsonHandler(context), _scale() {}

void MaterialNormalTextureInfoJsonHandler::reset(CesiumJsonReader::IJsonHandler* pParentHandler, MaterialNormalTextureInfo* pObject) {
  TextureInfoJsonHandler::reset(pParentHandler, pObject);
  this->_pObject = pObject;
}

CesiumJsonReader::IJsonHandler* MaterialNormalTextureInfoJsonHandler::readObjectKey(const std::string_view& str) {
  assert(this->_pObject);
  return this->readObjectKeyMaterialNormalTextureInfo(MaterialNormalTextureInfo::TypeName, str, *this->_pObject);
}

CesiumJsonReader::IJsonHandler* MaterialNormalTextureInfoJsonHandler::readObjectKeyMaterialNormalTextureInfo(const std::string& objectType, const std::string_view& str, MaterialNormalTextureInfo& o) {
  using namespace std::string_literals;

  if ("scale"s == str) return property("scale", this->_scale, o.scale);

  return this->readObjectKeyTextureInfo(objectType, str, *this->_pObject);
}
