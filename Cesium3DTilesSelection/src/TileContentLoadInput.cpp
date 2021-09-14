#include "Cesium3DTilesSelection/TileContentLoadInput.h"
#include "Cesium3DTilesSelection/Tileset.h"
#include "CesiumAsync/IAssetResponse.h"

using namespace Cesium3DTilesSelection;
using namespace CesiumAsync;

TileContentLoadInput::TileContentLoadInput(
    const AsyncSystem& asyncSystem_,
    std::shared_ptr<spdlog::logger>&& pLogger_,
    std::shared_ptr<IAssetAccessor>&& pAssetAccessor_,
    std::shared_ptr<IAssetRequest>&& pRequest_,
    const std::optional<gsl::span<const std::byte>>& data_,
    const Tile& tile_)
    : asyncSystem(asyncSystem_),
      pLogger(std::move(pLogger_)),
      pAssetAccessor(std::move(pAssetAccessor_)),
      pRequest(std::move(pRequest_)),
      data(data_ ? *data_ : this->pRequest->response()->data()),
      tileID(tile_.getTileID()),
      tileBoundingVolume(tile_.getBoundingVolume()),
      tileContentBoundingVolume(tile_.getContentBoundingVolume()),
      tileRefine(tile_.getRefine()),
      tileGeometricError(tile_.getGeometricError()),
      tileTransform(tile_.getTransform()),
      contentOptions(
          tile_.getContext()->pTileset->getOptions().contentOptions) {}

TileContentLoadInput::TileContentLoadInput(
    const AsyncSystem& asyncSystem_,
    std::shared_ptr<spdlog::logger>&& pLogger_,
    std::shared_ptr<IAssetAccessor>&& pAssetAccessor_,
    std::shared_ptr<IAssetRequest>&& pRequest_,
    const std::optional<gsl::span<const std::byte>>& data_,
    const TileID& tileID_,
    const BoundingVolume& tileBoundingVolume_,
    const std::optional<BoundingVolume>& tileContentBoundingVolume_,
    TileRefine tileRefine_,
    double tileGeometricError_,
    const glm::dmat4& tileTransform_,
    const TilesetContentOptions& contentOptions_)
    : asyncSystem(asyncSystem_),
      pLogger(std::move(pLogger_)),
      pAssetAccessor(std::move(pAssetAccessor_)),
      pRequest(std::move(pRequest_)),
      data(data_ ? *data_ : this->pRequest->response()->data()),
      tileID(tileID_),
      tileBoundingVolume(tileBoundingVolume_),
      tileContentBoundingVolume(tileContentBoundingVolume_),
      tileRefine(tileRefine_),
      tileGeometricError(tileGeometricError_),
      tileTransform(tileTransform_),
      contentOptions(contentOptions_) {}
