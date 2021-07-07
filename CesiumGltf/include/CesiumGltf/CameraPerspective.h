// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/ExtensibleObject.h"
#include "CesiumGltf/Library.h"
#include <optional>

namespace CesiumGltf {
/**
 * @brief A perspective camera containing properties to create a perspective
 * projection matrix.
 */
struct CESIUMGLTF_API CameraPerspective final : public ExtensibleObject {
  static constexpr const char* TypeName = "CameraPerspective";

  /**
   * @brief The floating-point aspect ratio of the field of view.
   *
   * When this is undefined, the aspect ratio of the canvas is used.
   */
  std::optional<double> aspectRatio;

  /**
   * @brief The floating-point vertical field of view in radians.
   */
  double yfov = double();

  /**
   * @brief The floating-point distance to the far clipping plane.
   *
   * When defined, `zfar` must be greater than `znear`. If `zfar` is undefined,
   * runtime must use infinite projection matrix.
   */
  std::optional<double> zfar;

  /**
   * @brief The floating-point distance to the near clipping plane.
   */
  double znear = double();
};
} // namespace CesiumGltf
