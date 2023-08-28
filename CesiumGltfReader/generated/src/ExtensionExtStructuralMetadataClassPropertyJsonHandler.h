// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include <CesiumGltf/ExtensionExtStructuralMetadataClassProperty.h>
#include <CesiumJsonReader/BoolJsonHandler.h>
#include <CesiumJsonReader/ExtensibleObjectJsonHandler.h>
#include <CesiumJsonReader/IntegerJsonHandler.h>
#include <CesiumJsonReader/JsonObjectJsonHandler.h>
#include <CesiumJsonReader/StringJsonHandler.h>

namespace CesiumJsonReader {
class JsonReaderOptions;
}

namespace CesiumGltfReader {
class ExtensionExtStructuralMetadataClassPropertyJsonHandler
    : public CesiumJsonReader::ExtensibleObjectJsonHandler {
public:
  using ValueType = CesiumGltf::ExtensionExtStructuralMetadataClassProperty;

  ExtensionExtStructuralMetadataClassPropertyJsonHandler(
      const CesiumJsonReader::JsonReaderOptions& options) noexcept;
  void reset(
      IJsonHandler* pParentHandler,
      CesiumGltf::ExtensionExtStructuralMetadataClassProperty* pObject);

  virtual IJsonHandler* readObjectKey(const std::string_view& str) override;

protected:
  IJsonHandler* readObjectKeyExtensionExtStructuralMetadataClassProperty(
      const std::string& objectType,
      const std::string_view& str,
      CesiumGltf::ExtensionExtStructuralMetadataClassProperty& o);

private:
  CesiumGltf::ExtensionExtStructuralMetadataClassProperty* _pObject = nullptr;
  CesiumJsonReader::StringJsonHandler _name;
  CesiumJsonReader::StringJsonHandler _description;
  CesiumJsonReader::StringJsonHandler _type;
  CesiumJsonReader::StringJsonHandler _componentType;
  CesiumJsonReader::StringJsonHandler _enumType;
  CesiumJsonReader::BoolJsonHandler _array;
  CesiumJsonReader::IntegerJsonHandler<int64_t> _count;
  CesiumJsonReader::BoolJsonHandler _normalized;
  CesiumJsonReader::JsonObjectJsonHandler _offset;
  CesiumJsonReader::JsonObjectJsonHandler _scale;
  CesiumJsonReader::JsonObjectJsonHandler _max;
  CesiumJsonReader::JsonObjectJsonHandler _min;
  CesiumJsonReader::BoolJsonHandler _required;
  CesiumJsonReader::JsonObjectJsonHandler _noData;
  CesiumJsonReader::JsonObjectJsonHandler _defaultProperty;
  CesiumJsonReader::StringJsonHandler _semantic;
};
} // namespace CesiumGltfReader
