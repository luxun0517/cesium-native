// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "NamedObjectJsonHandler.h"

#include <CesiumGltf/ExtensionModelMaxarMeshVariantsValue.h>
#include <CesiumJsonReader/StringJsonHandler.h>

namespace CesiumJsonReader {
class JsonReaderOptions;
}

namespace CesiumGltfReader {
class ExtensionModelMaxarMeshVariantsValueJsonHandler
    : public CesiumGltfReader::NamedObjectJsonHandler {
public:
  using ValueType = CesiumGltf::ExtensionModelMaxarMeshVariantsValue;

  ExtensionModelMaxarMeshVariantsValueJsonHandler(
      const CesiumJsonReader::JsonReaderOptions& options) noexcept;
  void reset(
      IJsonHandler* pParentHandler,
      CesiumGltf::ExtensionModelMaxarMeshVariantsValue* pObject);

  virtual IJsonHandler* readObjectKey(const std::string_view& str) override;

protected:
  IJsonHandler* readObjectKeyExtensionModelMaxarMeshVariantsValue(
      const std::string& objectType,
      const std::string_view& str,
      CesiumGltf::ExtensionModelMaxarMeshVariantsValue& o);

private:
  CesiumGltf::ExtensionModelMaxarMeshVariantsValue* _pObject = nullptr;
  CesiumJsonReader::StringJsonHandler _name;
};
} // namespace CesiumGltfReader
