// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include <CesiumGltf/Library.h>
#include <CesiumUtility/ExtensibleObject.h>

#include <cstdint>
#include <string>

namespace CesiumGltf {
/**
 * @brief The descriptor of the animated property.
 */
struct CESIUMGLTF_API AnimationChannelTarget final
    : public CesiumUtility::ExtensibleObject {
  /**
   * @brief The original name of this type.
   */
  static constexpr const char* TypeName = "AnimationChannelTarget";

  /**
   * @brief Known values for The name of the node's TRS property to animate, or
   * the `"weights"` of the Morph Targets it instantiates. For the
   * `"translation"` property, the values that are provided by the sampler are
   * the translation along the X, Y, and Z axes. For the `"rotation"` property,
   * the values are a quaternion in the order (x, y, z, w), where w is the
   * scalar. For the `"scale"` property, the values are the scaling factors
   * along the X, Y, and Z axes.
   */
  struct Path {
    /** @brief The translation value. */
    inline static const std::string translation = "translation";

    /** @brief The rotation value. */
    inline static const std::string rotation = "rotation";

    /** @brief The scale value. */
    inline static const std::string scale = "scale";

    /** @brief The weights value. */
    inline static const std::string weights = "weights";
  };

  /**
   * @brief The index of the node to animate. When undefined, the animated
   * object **MAY** be defined by an extension.
   */
  int32_t node = -1;

  /**
   * @brief The name of the node's TRS property to animate, or the `"weights"`
   * of the Morph Targets it instantiates. For the `"translation"` property, the
   * values that are provided by the sampler are the translation along the X, Y,
   * and Z axes. For the `"rotation"` property, the values are a quaternion in
   * the order (x, y, z, w), where w is the scalar. For the `"scale"` property,
   * the values are the scaling factors along the X, Y, and Z axes.
   *
   * Known values are defined in {@link Path}.
   *
   */
  std::string path = Path::translation;

  /**
   * @brief Calculates the size in bytes of this object, including the contents
   * of all collections, pointers, and strings. This will NOT include the size
   * of any extensions attached to the object. Calling this method may be slow
   * as it requires traversing the object's entire structure.
   */
  int64_t getSizeBytes() const {
    int64_t accum = 0;
    accum += int64_t(sizeof(AnimationChannelTarget));
    accum += CesiumUtility::ExtensibleObject::getSizeBytes() -
             int64_t(sizeof(CesiumUtility::ExtensibleObject));

    return accum;
  }
};
} // namespace CesiumGltf
