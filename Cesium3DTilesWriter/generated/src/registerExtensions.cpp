// This file was generated by generate-classes.
// DO NOT EDIT THIS FILE!

#include "registerExtensions.h"

#include "TilesetJsonWriter.h"

#include <Cesium3DTiles/BoundingVolume.h>
#include <Cesium3DTiles/Extension3dTilesBoundingVolumeS2.h>
#include <Cesium3DTiles/Extension3dTilesImplicitTiling.h>
#include <Cesium3DTiles/Tile.h>
#include <CesiumJsonWriter/ExtensionWriterContext.h>

namespace Cesium3DTilesWriter {

void registerExtensions(CesiumJsonWriter::ExtensionWriterContext& context) {
  (void)context;
  context.registerExtension<
      Cesium3DTiles::BoundingVolume,
      Extension3dTilesBoundingVolumeS2JsonWriter>();
  context.registerExtension<
      Cesium3DTiles::Tile,
      Extension3dTilesImplicitTilingJsonWriter>();
}
} // namespace Cesium3DTilesWriter
