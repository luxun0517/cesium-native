// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/CameraOrthographic.h"
#include "CesiumGltf/CameraPerspective.h"
#include "CesiumGltf/Library.h"
#include "CesiumGltf/NamedObject.h"
#include <optional>

namespace CesiumGltf {
/**
 * @brief A camera's projection.  A node can reference a camera to apply a
 * transform to place the camera in the scene.
 */
struct CESIUMGLTF_API Camera final : public NamedObject {
  static constexpr const char* TypeName = "Camera";

  /**
   * @brief Specifies if the camera uses a perspective or orthographic
   * projection.
   *
   * Based on this, either the camera's `perspective` or `orthographic` property
   * will be defined.
   */
  enum class Type {
    perspective,

    orthographic
  };

  /**
   * @brief An orthographic camera containing properties to create an
   * orthographic projection matrix.
   */
  std::optional<CameraOrthographic> orthographic;

  /**
   * @brief A perspective camera containing properties to create a perspective
   * projection matrix.
   */
  std::optional<CameraPerspective> perspective;

  /**
   * @brief Specifies if the camera uses a perspective or orthographic
   * projection.
   *
   * Based on this, either the camera's `perspective` or `orthographic` property
   * will be defined.
   */
  Type type = Type();
};
} // namespace CesiumGltf
