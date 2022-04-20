#pragma once

#include <Cesium3DTilesSelection/Exp_ErrorList.h>
#include <Cesium3DTilesSelection/Exp_TilesetContentLoader.h>
#include <Cesium3DTilesSelection/Tile.h>
#include <CesiumGeometry/Axis.h>

#include <memory>
#include <vector>

namespace Cesium3DTilesSelection {
struct LoaderCreditResult {
  std::string creditText;

  bool showOnScreen;
};

struct TilesetContentLoaderResult {
  std::unique_ptr<TilesetContentLoader> pLoader;

  std::unique_ptr<Tile> pRootTile;

  CesiumGeometry::Axis gltfUpAxis{CesiumGeometry::Axis::Y};

  std::vector<LoaderCreditResult> credits;

  ErrorList errors;
};
} // namespace Cesium3DTilesSelection
