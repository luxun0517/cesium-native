// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "ArrayJsonHandler.h"
#include "DoubleJsonHandler.h"
#include "IntegerJsonHandler.h"
#include "NamedObjectJsonHandler.h"
#include <CesiumGltf/Reader.h>

namespace CesiumGltf {
struct Node;

class NodeJsonHandler : public NamedObjectJsonHandler {
public:
  NodeJsonHandler(ReadModelOptions options) noexcept;
  void reset(IJsonHandler* pHandler, Node* pObject);
  Node* getObject();
  virtual void reportWarning(
      const std::string& warning,
      std::vector<std::string>&& context = std::vector<std::string>()) override;

  virtual IJsonHandler* Key(const char* str, size_t length, bool copy) override;

protected:
  IJsonHandler* NodeKey(const char* str, Node& o);

private:
  Node* _pObject = nullptr;
  IntegerJsonHandler<int32_t> _camera;
  ArrayJsonHandler<int32_t, IntegerJsonHandler<int32_t>> _children;
  IntegerJsonHandler<int32_t> _skin;
  ArrayJsonHandler<double, DoubleJsonHandler> _matrix;
  IntegerJsonHandler<int32_t> _mesh;
  ArrayJsonHandler<double, DoubleJsonHandler> _rotation;
  ArrayJsonHandler<double, DoubleJsonHandler> _scale;
  ArrayJsonHandler<double, DoubleJsonHandler> _translation;
  ArrayJsonHandler<double, DoubleJsonHandler> _weights;
};
} // namespace CesiumGltf
