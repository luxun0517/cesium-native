// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/Library.h"

#include <CesiumUtility/ExtensibleObject.h>

namespace CesiumGltf {
/**
 * @brief glTF extension that defines the unlit material model.
 */
struct CESIUMGLTF_API ExtensionKhrMaterialsUnlit final
    : public CesiumUtility::ExtensibleObject {
  static inline constexpr const char* TypeName = "ExtensionKhrMaterialsUnlit";
  static inline constexpr const char* ExtensionName = "KHR_materials_unlit";

  /**
   * @brief Calculates the size in bytes of this object, including the contents
   * of all collections, pointers, and strings. Calling this method may be slow
   * as it requires traversing the object's entire structure.
   */
  int64_t getSizeBytes() const {
    int64_t accum = 0;
    accum += sizeof(ExtensionKhrMaterialsUnlit);
    accum += CesiumUtility::ExtensibleObject::getSizeBytes() -
             sizeof(CesiumUtility::ExtensibleObject);

    return accum;
  }
};
} // namespace CesiumGltf
