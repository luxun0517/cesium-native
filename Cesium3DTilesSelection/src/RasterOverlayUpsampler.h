#pragma once

#include <Cesium3DTilesSelection/TilesetContentLoader.h>

namespace Cesium3DTilesSelection {
class RasterOverlayUpsampler : public TilesetContentLoader {
public:
  CesiumAsync::Future<TileLoadResult>
  loadTileContent(const TileLoadInput& loadInput) override;

  TileChildrenResult createTileChildren(const Tile& tile) override;

  CesiumGeometry::Axis getTileUpAxis(const Tile& tile) const noexcept override;
};
} // namespace Cesium3DTilesSelection
