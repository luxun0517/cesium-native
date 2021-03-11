// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CameraOrthographicJsonHandler.h"
#include "CameraPerspectiveJsonHandler.h"
#include "CesiumGltf/Camera.h"
#include "NamedObjectJsonHandler.h"
#include <CesiumGltf/Reader.h>

namespace CesiumGltf {
struct Camera;

class CameraJsonHandler : public NamedObjectJsonHandler {
public:
  CameraJsonHandler(ReadModelOptions options) noexcept;
  void reset(IJsonHandler* pHandler, Camera* pObject);
  Camera* getObject();
  virtual void reportWarning(
      const std::string& warning,
      std::vector<std::string>&& context = std::vector<std::string>()) override;

  virtual IJsonHandler* Key(const char* str, size_t length, bool copy) override;

protected:
  IJsonHandler* CameraKey(const char* str, Camera& o);

private:
  class TypeJsonHandler : public JsonHandler {
  public:
    TypeJsonHandler(ReadModelOptions options) noexcept : JsonHandler(options) {}
    void reset(IJsonHandler* pParent, Camera::Type* pEnum);
    virtual IJsonHandler*
    String(const char* str, size_t length, bool copy) override;

  private:
    Camera::Type* _pEnum = nullptr;
  };

  Camera* _pObject = nullptr;
  CameraOrthographicJsonHandler _orthographic;
  CameraPerspectiveJsonHandler _perspective;
  TypeJsonHandler _type;
};
} // namespace CesiumGltf
