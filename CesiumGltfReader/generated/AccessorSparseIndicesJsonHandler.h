// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/AccessorSparseIndices.h"
#include "ExtensibleObjectJsonHandler.h"
#include "IntegerJsonHandler.h"
#include <CesiumGltf/Reader.h>

namespace CesiumGltf {
struct AccessorSparseIndices;

class AccessorSparseIndicesJsonHandler : public ExtensibleObjectJsonHandler {
public:
  AccessorSparseIndicesJsonHandler(ReadModelOptions options) noexcept;
  void reset(IJsonHandler* pHandler, AccessorSparseIndices* pObject);
  AccessorSparseIndices* getObject();
  virtual void reportWarning(
      const std::string& warning,
      std::vector<std::string>&& context = std::vector<std::string>()) override;

  virtual IJsonHandler* Key(const char* str, size_t length, bool copy) override;

protected:
  IJsonHandler*
  AccessorSparseIndicesKey(const char* str, AccessorSparseIndices& o);

private:
  AccessorSparseIndices* _pObject = nullptr;
  IntegerJsonHandler<int32_t> _bufferView;
  IntegerJsonHandler<int64_t> _byteOffset;
  IntegerJsonHandler<AccessorSparseIndices::ComponentType> _componentType;
};
} // namespace CesiumGltf
