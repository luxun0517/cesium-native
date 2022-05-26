#pragma once

#include <Cesium3DTilesSelection/Exp_TileContent.h>
#include <Cesium3DTilesSelection/Exp_TileContentLoadInfo.h>
#include <CesiumAsync/Future.h>
#include <CesiumAsync/IAssetAccessor.h>

#include <functional>
#include <memory>
#include <vector>

namespace Cesium3DTilesSelection {
class Tile;

enum class TileLoadResultState { Success, Failed, RetryLater };

struct TileLoadResult {
  TileContentKind contentKind;
  TileLoadResultState state;
  std::shared_ptr<CesiumAsync::IAssetRequest> pCompletedRequest;
  std::function<void(Tile&)> tileInitializer;
};

class TilesetContentLoader {
public:
  virtual ~TilesetContentLoader() = default;

  virtual CesiumAsync::Future<TileLoadResult> loadTileContent(
      Tile& tile,
      const TilesetContentOptions& contentOptions,
      const CesiumAsync::AsyncSystem& asyncSystem,
      const std::shared_ptr<CesiumAsync::IAssetAccessor>& pAssetAccessor,
      const std::shared_ptr<spdlog::logger>& pLogger,
      const std::vector<CesiumAsync::IAssetAccessor::THeader>&
          requestHeaders) = 0;
};
} // namespace Cesium3DTilesSelection