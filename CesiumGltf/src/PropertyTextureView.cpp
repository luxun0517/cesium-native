#include "CesiumGltf/PropertyTextureView.h"

namespace CesiumGltf {
PropertyTextureView::PropertyTextureView(
    const Model& model,
    const PropertyTexture& propertyTexture) noexcept
    : _pModel(&model),
      _pPropertyTexture(&propertyTexture),
      _pClass(nullptr),
      _status() {
  const ExtensionModelExtStructuralMetadata* pMetadata =
      model.getExtension<ExtensionModelExtStructuralMetadata>();

  if (!pMetadata) {
    this->_status = PropertyTextureViewStatus::ErrorMissingMetadataExtension;
    return;
  }

  if (!pMetadata->schema) {
    this->_status = PropertyTextureViewStatus::ErrorMissingSchema;
    return;
  }

  const auto& classIt =
      pMetadata->schema->classes.find(propertyTexture.classProperty);
  if (classIt == pMetadata->schema->classes.end()) {
    this->_status = PropertyTextureViewStatus::ErrorClassNotFound;
    return;
  }

  this->_pClass = &classIt->second;
}

const ClassProperty*
PropertyTextureView::getClassProperty(const std::string& propertyId) const {
  if (_status != PropertyTextureViewStatus::Valid) {
    return nullptr;
  }

  auto propertyIter = _pClass->properties.find(propertyId);
  if (propertyIter == _pClass->properties.end()) {
    return nullptr;
  }

  return &propertyIter->second;
}

PropertyViewStatusType PropertyTextureView::getTextureSafe(
    const int32_t textureIndex,
    int32_t& samplerIndex,
    int32_t& imageIndex) const noexcept {
  if (textureIndex < 0 ||
      static_cast<size_t>(textureIndex) >= _pModel->textures.size()) {
    return PropertyTexturePropertyViewStatus::ErrorInvalidTexture;
  }

  const Texture& texture = _pModel->textures[static_cast<size_t>(textureIndex)];
  samplerIndex = texture.sampler;
  imageIndex = texture.source;

  return PropertyTexturePropertyViewStatus::Valid;
}

PropertyViewStatusType
PropertyTextureView::checkSampler(const int32_t samplerIndex) const noexcept {
  if (samplerIndex < 0 ||
      static_cast<size_t>(samplerIndex) >= _pModel->samplers.size()) {
    return PropertyTexturePropertyViewStatus::ErrorInvalidSampler;
  }

  // TODO: check if sampler filter values are supported

  return PropertyTexturePropertyViewStatus::Valid;
}

PropertyViewStatusType
PropertyTextureView::checkImage(const int32_t imageIndex) const noexcept {
  if (imageIndex < 0 ||
      static_cast<size_t>(imageIndex) >= _pModel->images.size()) {
    return PropertyTexturePropertyViewStatus::ErrorInvalidImage;
  }

  const CesiumUtility::IntrusivePointer<ImageCesium>& pImage =
      _pModel->images[static_cast<size_t>(imageIndex)].pCesium;

  if (pImage->width < 1 || pImage->height < 1) {
    return PropertyTexturePropertyViewStatus::ErrorEmptyImage;
  }

  if (pImage->bytesPerChannel > 1) {
    return PropertyTexturePropertyViewStatus::ErrorInvalidBytesPerChannel;
  }

  return PropertyTexturePropertyViewStatus::Valid;
}

PropertyViewStatusType PropertyTextureView::checkChannels(
    const std::vector<int64_t>& channels,
    const ImageCesium& image) const noexcept {
  if (channels.size() <= 0 || channels.size() > 4) {
    return PropertyTexturePropertyViewStatus::ErrorInvalidChannels;
  }

  int64_t imageChannelCount = static_cast<int64_t>(image.channels);
  for (size_t i = 0; i < channels.size(); i++) {
    if (channels[i] < 0 || channels[i] >= imageChannelCount) {
      return PropertyTexturePropertyViewStatus::ErrorInvalidChannels;
    }
  }

  return PropertyTexturePropertyViewStatus::Valid;
}

} // namespace CesiumGltf
