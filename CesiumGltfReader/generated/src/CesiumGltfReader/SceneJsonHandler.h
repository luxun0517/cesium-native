// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltfReader/NamedObjectJsonHandler.h"

#include <CesiumGltf/Scene.h>
#include <CesiumJsonReader/ArrayJsonHandler.h>
#include <CesiumJsonReader/IntegerJsonHandler.h>

namespace CesiumJsonReader {
class ExtensionReaderContext;
}

namespace CesiumGltfReader {
class SceneJsonHandler : public CesiumGltfReader::NamedObjectJsonHandler {
public:
  using ValueType = CesiumGltf::Scene;

  static void
  populateExtensions(CesiumJsonReader::ExtensionReaderContext& context);

  SceneJsonHandler(
      const CesiumJsonReader::ExtensionReaderContext& context) noexcept;
  void reset(IJsonHandler* pParentHandler, CesiumGltf::Scene* pObject);

  virtual IJsonHandler* readObjectKey(const std::string_view& str) override;

protected:
  IJsonHandler* readObjectKeyScene(
      const std::string& objectType,
      const std::string_view& str,
      CesiumGltf::Scene& o);

private:
  CesiumGltf::Scene* _pObject = nullptr;
  CesiumJsonReader::
      ArrayJsonHandler<int32_t, CesiumJsonReader::IntegerJsonHandler<int32_t>>
          _nodes;
};
} // namespace CesiumGltfReader