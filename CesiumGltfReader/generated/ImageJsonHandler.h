// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/Image.h"
#include "IntegerJsonHandler.h"
#include "NamedObjectJsonHandler.h"
#include "StringJsonHandler.h"
#include <CesiumGltf/Reader.h>

namespace CesiumGltf {
struct Image;

class ImageJsonHandler : public NamedObjectJsonHandler {
public:
  ImageJsonHandler(const ReadModelOptions& options) noexcept;
  void reset(IJsonHandler* pHandler, Image* pObject);
  Image* getObject();
  virtual void reportWarning(
      const std::string& warning,
      std::vector<std::string>&& context = std::vector<std::string>()) override;

  virtual IJsonHandler* Key(const char* str, size_t length, bool copy) override;

protected:
  IJsonHandler* ImageKey(const char* str, Image& o);

private:
  class MimeTypeJsonHandler : public JsonHandler {
  public:
    MimeTypeJsonHandler(const ReadModelOptions& options) noexcept
        : JsonHandler(options) {}
    void reset(IJsonHandler* pParent, Image::MimeType* pEnum);
    virtual IJsonHandler*
    String(const char* str, size_t length, bool copy) override;

  private:
    Image::MimeType* _pEnum = nullptr;
  };

  Image* _pObject = nullptr;
  StringJsonHandler _uri;
  MimeTypeJsonHandler _mimeType;
  IntegerJsonHandler<int32_t> _bufferView;
};
} // namespace CesiumGltf
