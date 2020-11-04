#pragma once

#include "Cesium3DTiles/BoundingVolume.h"
#include "Cesium3DTiles/Gltf.h"
#include "Cesium3DTiles/IAssetRequest.h"
#include "Cesium3DTiles/Library.h"
#include "Cesium3DTiles/RasterMappedTo3DTile.h"
#include "Cesium3DTiles/RasterOverlayTile.h"
#include "Cesium3DTiles/TileContext.h"
#include "Cesium3DTiles/TileID.h"
#include "Cesium3DTiles/TileRefine.h"
#include "Cesium3DTiles/TileSelectionState.h"
#include "CesiumUtility/DoublyLinkedList.h"
#include <atomic>
#include <glm/mat4x4.hpp>
#include <gsl/span>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace Cesium3DTiles {
    class Tileset;
    class TileContent;
    class RasterOverlayTileProvider;
    struct TileContentLoadResult;

    class CESIUM3DTILES_API Tile {
    public:
        /**
         * The current state of this tile in the loading process.
         */
        enum class LoadState {
            /**
             * This tile is in the process of being destroyed. Any pointers to it
             * will soon be invalid.
             */
            Destroying = -2,

            /**
             * Something went wrong while loading this tile.
             */
            Failed = -1,

            /**
             * The tile is not yet loaded at all, beyond the metadata in tileset.json.
             */
            Unloaded = 0,

            /**
             * The tile content is currently being loaded. Note that while a tile is in this state, its
             * \ref Tile::getContent, \ref Tile::setContent, \ref Tile::getState, and \ref Tile::setState
             * methods may be called from the load thread.
             */
            ContentLoading = 1,

            /**
             * The tile content has finished loading.
             */
            ContentLoaded = 2,

            /**
             * The tile is completely done loading.
             */
            Done = 3
        };

        Tile();
        ~Tile();
        Tile(Tile& rhs) noexcept = delete;
        Tile(Tile&& rhs) noexcept;
        Tile& operator=(Tile&& rhs) noexcept;

        void prepareToDestroy();

        Tileset* getTileset() { return this->_pContext->pTileset; }
        const Tileset* getTileset() const { return this->_pContext->pTileset; }
        
        TileContext* getContext() { return this->_pContext; }
        const TileContext* getContext() const { return this->_pContext; }
        void setContext(TileContext* pContext) { this->_pContext = pContext; }

        Tile* getParent() { return this->_pParent; }
        const Tile* getParent() const { return this->_pParent; }
        void setParent(Tile* pParent) { this->_pParent = pParent; }

        gsl::span<const Tile> getChildren() const { return gsl::span<const Tile>(this->_children); }
        gsl::span<Tile> getChildren() { return gsl::span<Tile>(this->_children); }
        void createChildTiles(size_t count);
        void createChildTiles(std::vector<Tile>&& children);

        const BoundingVolume& getBoundingVolume() const { return this->_boundingVolume; }
        void setBoundingVolume(const BoundingVolume& value) { this->_boundingVolume = value; }

        const std::optional<BoundingVolume>& getViewerRequestVolume() const { return this->_viewerRequestVolume; }
        void setViewerRequestVolume(const std::optional<BoundingVolume>& value) { this->_viewerRequestVolume = value; }

        double getGeometricError() const { return this->_geometricError; }
        void setGeometricError(double value) { this->_geometricError = value; }

        TileRefine getRefine() const { return this->_refine; }
        void setRefine(TileRefine value) { this->_refine = value; }

        /**
         * Gets the transformation matrix for this tile. This matrix does _not_ need to be multiplied
         * with the tile's parent's transform as this has already been done.
         */
        const glm::dmat4x4& getTransform() const { return this->_transform; }
        void setTransform(const glm::dmat4x4& value) { this->_transform = value; }

        const TileID& getTileID() const { return this->_id; }
        void setTileID(const TileID& id);

        const std::optional<BoundingVolume>& getContentBoundingVolume() const { return this->_contentBoundingVolume; }
        void setContentBoundingVolume(const std::optional<BoundingVolume>& value) { this->_contentBoundingVolume = value; }

        TileContentLoadResult* getContent() { return this->_pContent.get(); }
        const TileContentLoadResult* getContent() const { return this->_pContent.get(); }

        void* getRendererResources() const { return this->_pRendererResources; }

        LoadState getState() const { return this->_state.load(std::memory_order::memory_order_acquire); }

        TileSelectionState& getLastSelectionState() { return this->_lastSelectionState; }
        const TileSelectionState& getLastSelectionState() const { return this->_lastSelectionState; }
        void setLastSelectionState(const TileSelectionState& newState) { this->_lastSelectionState = newState; }

        /**
         * Determines if this tile is currently renderable.
         */
        bool isRenderable() const;

        void loadContent();

        bool unloadContent();

        /**
         * Gives this tile a chance to update itself each render frame.
         * @param previousFrameNumber The number of the previous render frame.
         * @param currentFrameNumber The number of the current render frame.
         */
        void update(uint32_t previousFrameNumber, uint32_t currentFrameNumber);

    protected:
        void setState(LoadState value);
        void contentResponseReceived(IAssetRequest* pRequest);
        std::optional<CesiumGeospatial::BoundingRegion> generateTextureCoordinates();
        void upsampleParent();

    private:
        // Position in bounding-volume hierarchy.
        TileContext* _pContext;
        Tile* _pParent;
        std::vector<Tile> _children;

        // Properties from tileset.json.
        // These are immutable after the tile leaves TileState::Unloaded.
        BoundingVolume _boundingVolume;
        std::optional<BoundingVolume> _viewerRequestVolume;
        double _geometricError;
        TileRefine _refine;
        glm::dmat4x4 _transform;

        TileID _id;
        std::optional<BoundingVolume> _contentBoundingVolume;

        // Load state and data.
        std::atomic<LoadState> _state;
        std::unique_ptr<IAssetRequest> _pContentRequest;
        std::unique_ptr<TileContentLoadResult> _pContent;
        void* _pRendererResources;

        // Selection state
        TileSelectionState _lastSelectionState;

        // Overlays
        std::vector<RasterMappedTo3DTile> _rasterTiles;

        CesiumUtility::DoublyLinkedListPointers<Tile> _loadedTilesLinks;

    public:
        typedef CesiumUtility::DoublyLinkedList<Tile, &Tile::_loadedTilesLinks> LoadedLinkedList;
    };

}
