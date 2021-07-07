// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/ExtensibleObject.h"
#include "CesiumGltf/Library.h"
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace CesiumGltf {
/**
 * @brief Geometry to be rendered with the given material.
 */
struct CESIUMGLTF_API MeshPrimitive final : public ExtensibleObject {
  static constexpr const char* TypeName = "MeshPrimitive";

  /**
   * @brief The type of primitives to render.
   *
   * All valid values correspond to WebGL enums.
   */
  enum class Mode {
    POINTS = 0,

    LINES = 1,

    LINE_LOOP = 2,

    LINE_STRIP = 3,

    TRIANGLES = 4,

    TRIANGLE_STRIP = 5,

    TRIANGLE_FAN = 6
  };

  /**
   * @brief A dictionary object, where each key corresponds to mesh attribute
   * semantic and each value is the index of the accessor containing attribute's
   * data.
   */
  std::unordered_map<std::string, int32_t> attributes;

  /**
   * @brief The index of the accessor that contains the indices.
   *
   * The index of the accessor that contains mesh indices.  When this is not
   * defined, the primitives should be rendered without indices using
   * `drawArrays()`.  When defined, the accessor must contain indices: the
   * `bufferView` referenced by the accessor should have a `target` equal to
   * 34963 (ELEMENT_ARRAY_BUFFER); `componentType` must be 5121 (UNSIGNED_BYTE),
   * 5123 (UNSIGNED_SHORT) or 5125 (UNSIGNED_INT), the latter may require
   * enabling additional hardware support; `type` must be `"SCALAR"`. For
   * triangle primitives, the front face has a counter-clockwise (CCW) winding
   * order. Values of the index accessor must not include the maximum value for
   * the given component type, which triggers primitive restart in several
   * graphics APIs and would require client implementations to rebuild the index
   * buffer. Primitive restart values are disallowed and all index values must
   * refer to actual vertices. As a result, the index accessor's values must not
   * exceed the following maxima: BYTE `< 255`, UNSIGNED_SHORT `< 65535`,
   * UNSIGNED_INT `< 4294967295`.
   */
  int32_t indices = -1;

  /**
   * @brief The index of the material to apply to this primitive when rendering.
   */
  int32_t material = -1;

  /**
   * @brief The type of primitives to render.
   *
   * All valid values correspond to WebGL enums.
   */
  Mode mode = Mode(4);

  /**
   * @brief An array of Morph Targets, each  Morph Target is a dictionary
   * mapping attributes (only `POSITION`, `NORMAL`, and `TANGENT` supported) to
   * their deviations in the Morph Target.
   */
  std::vector<std::unordered_map<std::string, int32_t>> targets;
};
} // namespace CesiumGltf
