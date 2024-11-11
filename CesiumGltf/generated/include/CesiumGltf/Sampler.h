// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/Library.h"
#include "CesiumGltf/NamedObject.h"

#include <optional>

namespace CesiumGltf {
/**
 * @brief Texture sampler properties for filtering and wrapping modes.
 */
struct CESIUMGLTF_API Sampler final : public CesiumGltf::NamedObject {
  static inline constexpr const char* TypeName = "Sampler";

  /**
   * @brief Known values for Magnification filter.
   */
  struct MagFilter {
    static constexpr int32_t NEAREST = 9728;

    static constexpr int32_t LINEAR = 9729;
  };

  /**
   * @brief Known values for Minification filter.
   */
  struct MinFilter {
    static constexpr int32_t NEAREST = 9728;

    static constexpr int32_t LINEAR = 9729;

    static constexpr int32_t NEAREST_MIPMAP_NEAREST = 9984;

    static constexpr int32_t LINEAR_MIPMAP_NEAREST = 9985;

    static constexpr int32_t NEAREST_MIPMAP_LINEAR = 9986;

    static constexpr int32_t LINEAR_MIPMAP_LINEAR = 9987;
  };

  /**
   * @brief Known values for S (U) wrapping mode.
   */
  struct WrapS {
    static constexpr int32_t CLAMP_TO_EDGE = 33071;

    static constexpr int32_t MIRRORED_REPEAT = 33648;

    static constexpr int32_t REPEAT = 10497;
  };

  /**
   * @brief Known values for T (V) wrapping mode.
   */
  struct WrapT {
    static constexpr int32_t CLAMP_TO_EDGE = 33071;

    static constexpr int32_t MIRRORED_REPEAT = 33648;

    static constexpr int32_t REPEAT = 10497;
  };

  /**
   * @brief Magnification filter.
   *
   * Known values are defined in {@link MagFilter}.
   *
   */
  std::optional<int32_t> magFilter;

  /**
   * @brief Minification filter.
   *
   * Known values are defined in {@link MinFilter}.
   *
   */
  std::optional<int32_t> minFilter;

  /**
   * @brief S (U) wrapping mode.
   *
   * Known values are defined in {@link WrapS}.
   *
   *
   * All valid values correspond to WebGL enums.
   */
  int32_t wrapS = WrapS::REPEAT;

  /**
   * @brief T (V) wrapping mode.
   *
   * Known values are defined in {@link WrapT}.
   *
   */
  int32_t wrapT = WrapT::REPEAT;

  /**
   * @brief Calculates the size in bytes of this object, including the contents
   * of all collections, pointers, and strings. Calling this method may be slow
   * as it requires traversing the object's entire structure.
   */
  int64_t getSizeBytes() const {
    int64_t accum = 0;
    accum += sizeof(Sampler);
    accum += CesiumGltf::NamedObject::getSizeBytes() -
             sizeof(CesiumGltf::NamedObject);

    return accum;
  }
};
} // namespace CesiumGltf
