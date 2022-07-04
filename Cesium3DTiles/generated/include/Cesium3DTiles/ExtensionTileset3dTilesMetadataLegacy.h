// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "Cesium3DTiles/Extension3dTilesMetadataGroupMetadataLegacy.h"
#include "Cesium3DTiles/Extension3dTilesMetadataSchemaLegacy.h"
#include "Cesium3DTiles/Extension3dTilesMetadataStatisticsLegacy.h"
#include "Cesium3DTiles/Extension3dTilesMetadataTilesetMetadataLegacy.h"
#include "Cesium3DTiles/Library.h"

#include <CesiumUtility/ExtensibleObject.h>

#include <optional>
#include <string>
#include <unordered_map>

namespace Cesium3DTiles {
/**
 * @brief 3D Tiles extension that defines metadata for a tileset.
 */
struct CESIUM3DTILES_API ExtensionTileset3dTilesMetadataLegacy final
    : public CesiumUtility::ExtensibleObject {
  static inline constexpr const char* TypeName =
      "ExtensionTileset3dTilesMetadataLegacy";
  static inline constexpr const char* ExtensionName = "3DTILES_metadata";

  /**
   * @brief An object defining classes and enums.
   */
  std::optional<Cesium3DTiles::Extension3dTilesMetadataSchemaLegacy> schema;

  /**
   * @brief A uri to an external schema file.
   */
  std::optional<std::string> schemaUri;

  /**
   * @brief An object containing statistics about entities.
   */
  std::optional<Cesium3DTiles::Extension3dTilesMetadataStatisticsLegacy>
      statistics;

  /**
   * @brief A dictionary, where each key is a group ID and each value is an
   * object defining the group.
   */
  std::unordered_map<
      std::string,
      Cesium3DTiles::Extension3dTilesMetadataGroupMetadataLegacy>
      groups;

  /**
   * @brief An object containing metadata about the tileset.
   */
  std::optional<Cesium3DTiles::Extension3dTilesMetadataTilesetMetadataLegacy>
      tileset;
};
} // namespace Cesium3DTiles
