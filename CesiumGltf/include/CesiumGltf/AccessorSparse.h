// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/AccessorSparseIndices.h"
#include "CesiumGltf/AccessorSparseValues.h"
#include "CesiumGltf/ExtensibleObject.h"
#include "CesiumGltf/Library.h"

#include <cstdint>

namespace CesiumGltf {
/**
 * @brief Sparse storage of attributes that deviate from their initialization
 * value.
 */
struct CESIUMGLTF_API AccessorSparse final : public ExtensibleObject {
  static inline constexpr const char* TypeName = "AccessorSparse";

  /**
   * @brief Number of entries stored in the sparse array.
   *
   * The number of attributes encoded in this sparse accessor.
   */
  int64_t count = int64_t();

  /**
   * @brief Index array of size `count` that points to those accessor attributes
   * that deviate from their initialization value. Indices must strictly
   * increase.
   */
  AccessorSparseIndices indices;

  /**
   * @brief Array of size `count` times number of components, storing the
   * displaced accessor attributes pointed by `indices`. Substituted values must
   * have the same `componentType` and number of components as the base
   * accessor.
   */
  AccessorSparseValues values;
};
} // namespace CesiumGltf
