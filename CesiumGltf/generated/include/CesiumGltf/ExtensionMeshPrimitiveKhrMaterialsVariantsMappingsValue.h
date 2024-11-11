// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/Library.h"

#include <CesiumUtility/ExtensibleObject.h>

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace CesiumGltf {
/**
 * @brief ExtensionMeshPrimitiveKhrMaterialsVariants Mappings Value
 */
struct CESIUMGLTF_API ExtensionMeshPrimitiveKhrMaterialsVariantsMappingsValue
    final : public CesiumUtility::ExtensibleObject {
  static inline constexpr const char* TypeName =
      "ExtensionMeshPrimitiveKhrMaterialsVariantsMappingsValue";

  /**
   * @brief An array of variant index values.
   *
   * An array of index values that reference variants defined in the glTF root's
   * extension object.
   */
  std::vector<int32_t> variants;

  /**
   * @brief The material associated with the set of variants.
   *
   * A reference to the material associated with the given array of variants.
   */
  int32_t material = -1;

  /**
   * @brief The user-defined name of this variant material mapping.
   *
   * The optional user-defined name of this variant material mapping.  This is
   * not necessarily unique.
   */
  std::optional<std::string> name;

  /**
   * @brief Calculates the size in bytes of this object, including the contents
   * of all collections, pointers, and strings. Calling this method may be slow
   * as it requires traversing the object's entire structure.
   */
  int64_t getSizeBytes() const {
    int64_t accum = 0;
    accum += sizeof(ExtensionMeshPrimitiveKhrMaterialsVariantsMappingsValue);
    accum += CesiumUtility::ExtensibleObject::getSizeBytes() -
             sizeof(CesiumUtility::ExtensibleObject);
    accum += sizeof(int32_t) * this->variants.capacity();
    if (this->name) {
      accum += this->name->capacity() * sizeof(char);
    }
    return accum;
  }
};
} // namespace CesiumGltf
