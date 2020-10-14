#include "Cesium3DTiles/IPrepareRendererResources.h"
#include "Cesium3DTiles/RasterMappedTo3DTile.h"
#include "Cesium3DTiles/RasterOverlayCollection.h"
#include "Cesium3DTiles/RasterOverlayTileProvider.h"
#include "Cesium3DTiles/Tile.h"
#include "Cesium3DTiles/Tileset.h"
#include "Cesium3DTiles/TilesetExternals.h"

namespace Cesium3DTiles {

    RasterMappedTo3DTile::RasterMappedTo3DTile(
        const std::shared_ptr<RasterOverlayTile>& pRasterTile,
        const CesiumGeometry::Rectangle& textureCoordinateRectangle
    ) :
        _pLoadingTile(pRasterTile),
        _pReadyTile(nullptr),
        _textureCoordinateID(0),
        _textureCoordinateRectangle(textureCoordinateRectangle),
        _translation(0.0, 0.0),
        _scale(1.0, 1.0),
        _state(AttachmentState::Unattached)
    {
    }

    RasterMappedTo3DTile::MoreDetailAvailable RasterMappedTo3DTile::update(Tile& tile) {
        if (this->getState() == AttachmentState::Attached) {
            return this->_pReadyTile && this->_pReadyTile->getID().level < this->_pReadyTile->getTileProvider().getMaximumLevel()
                ? MoreDetailAvailable::Yes
                : MoreDetailAvailable::No;
        }

        // If the loading tile has failed, try its parent.
        while (this->_pLoadingTile && this->_pLoadingTile->getState() == RasterOverlayTile::LoadState::Failed && this->_pLoadingTile->getID().level > 0) {
            CesiumGeometry::QuadtreeTileID thisID = this->_pLoadingTile->getID();
            CesiumGeometry::QuadtreeTileID parentID(thisID.level - 1, thisID.x >> 1, thisID.y >> 1);
            this->_pLoadingTile = this->_pLoadingTile->getTileProvider().getTile(parentID);
        }

        // If the loading tile is now ready, make it the ready tile.
        if (this->_pLoadingTile && this->_pLoadingTile->getState() >= RasterOverlayTile::LoadState::Loaded) {
            // Unattach the old tile
            if (this->_pReadyTile && this->getState() != AttachmentState::Unattached) {
                TilesetExternals& externals = tile.getTileset()->getExternals();
                externals.pPrepareRendererResources->detachRasterInMainThread(
                    tile,
                    this->getTextureCoordinateID(),
                    *this->_pReadyTile,
                    this->_pReadyTile->getRendererResources(),
                    this->getTextureCoordinateRectangle()
                );
                this->_state = AttachmentState::Unattached;
            }

            // Mark the loading tile read.
            this->_pReadyTile = this->_pLoadingTile;
            this->_pLoadingTile.reset();

            // Compute the translation and scale for the new tile.
            this->computeTranslationAndScale(tile);
        }

        // Find the closest ready ancestor tile.
        if (this->_pLoadingTile) {
            RasterOverlayTileProvider& tileProvider = this->_pLoadingTile->getTileProvider();

            std::shared_ptr<RasterOverlayTile> candidate;
            CesiumGeometry::QuadtreeTileID id = this->_pLoadingTile->getID();
            while (id.level > 0) {
                --id.level;
                id.x >>= 1;
                id.y >>= 1;

                candidate = tileProvider.getTileWithoutRequesting(id);
                if (candidate && candidate->getState() >= RasterOverlayTile::LoadState::Loaded) {
                    break;
                }
            }

            if (candidate && candidate->getState() >= RasterOverlayTile::LoadState::Loaded && candidate != this->_pReadyTile) {
                if (this->getState() != AttachmentState::Unattached) {
                    TilesetExternals& externals = tile.getTileset()->getExternals();
                    externals.pPrepareRendererResources->detachRasterInMainThread(
                        tile,
                        this->getTextureCoordinateID(),
                        *this->_pReadyTile,
                        this->_pReadyTile->getRendererResources(),
                        this->getTextureCoordinateRectangle()
                    );
                    this->_state = AttachmentState::Unattached;
                }

                this->_pReadyTile = candidate;

                // Compute the translation and scale for the new tile.
                this->computeTranslationAndScale(tile);
            }
        }

        // Attach the ready tile if it's not already attached.
        if (this->_pReadyTile && this->getState() == RasterMappedTo3DTile::AttachmentState::Unattached) {
            this->_pReadyTile->loadInMainThread();

            TilesetExternals& externals = tile.getTileset()->getExternals();
            externals.pPrepareRendererResources->attachRasterInMainThread(
                tile,
                this->getTextureCoordinateID(),
                *this->_pReadyTile,
                this->_pReadyTile->getRendererResources(),
                this->getTextureCoordinateRectangle(),
                this->getTranslation(),
                this->getScale()
            );

            this->_state = this->_pLoadingTile ? AttachmentState::TemporarilyAttached : AttachmentState::Attached;
        }

        // TODO: check more precise raster overlay tile availability, rather than just max level?
        if (this->_pLoadingTile) {
            return MoreDetailAvailable::Unknown;
        } else {
            return this->_pReadyTile && this->_pReadyTile->getID().level < this->_pReadyTile->getTileProvider().getMaximumLevel()
                ? MoreDetailAvailable::Yes
                : MoreDetailAvailable::No;
        }
    }

    void RasterMappedTo3DTile::computeTranslationAndScale(Tile& tile) {
        if (!this->_pReadyTile) {
            return;
        }

        const CesiumGeospatial::BoundingRegion* pRegion = std::get_if<CesiumGeospatial::BoundingRegion>(&tile.getBoundingVolume());
        const CesiumGeospatial::BoundingRegionWithLooseFittingHeights* pLooseRegion = std::get_if<CesiumGeospatial::BoundingRegionWithLooseFittingHeights>(&tile.getBoundingVolume());
        
        const CesiumGeospatial::GlobeRectangle* pRectangle = nullptr;
        if (pRegion) {
            pRectangle = &pRegion->getRectangle();
        } else if (pLooseRegion) {
            pRectangle = &pLooseRegion->getBoundingRegion().getRectangle();
        }

        if (!pRectangle) {
            return;
        }

        RasterOverlayTileProvider& tileProvider = this->_pReadyTile->getTileProvider();
        CesiumGeometry::Rectangle geometryRectangle = projectRectangleSimple(tileProvider.getProjection(), *pRectangle);
        CesiumGeometry::Rectangle imageryRectangle = tileProvider.getTilingScheme().tileToRectangle(this->_pReadyTile->getID());

        double terrainWidth = geometryRectangle.computeWidth();
        double terrainHeight = geometryRectangle.computeHeight();

        double scaleX = terrainWidth / imageryRectangle.computeWidth();
        double scaleY = terrainHeight / imageryRectangle.computeHeight();
        this->_translation = glm::dvec2(
            (scaleX * (geometryRectangle.minimumX - imageryRectangle.minimumX)) / terrainWidth,
            (scaleY * (geometryRectangle.minimumY - imageryRectangle.minimumY)) / terrainHeight
        );
        this->_scale = glm::dvec2(scaleX, scaleY);
    }

}
