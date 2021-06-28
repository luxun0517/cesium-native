// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/Library.h"
#include "CesiumGltf/NamedObject.h"
#include <cstdint>
#include <optional>
#include <string>

namespace CesiumGltf {
    /**
     * @brief Image data used to create a texture. Image can be referenced by URI or `bufferView` index. `mimeType` is required in the latter case.
     */
    struct CESIUMGLTF_API ImageSpec : public NamedObject {
        static inline constexpr const char* TypeName = "Image";

        /**
         * @brief The image's MIME type. Required if `bufferView` is defined.
         */
        enum class MimeType {
            image_jpeg,

            image_png
        };

        /**
         * @brief The uri of the image.
         *
         * Relative paths are relative to the .gltf file.  Instead of referencing an external file, the uri can also be a data-uri.  The image format must be jpg or png.
         */
        std::optional<std::string> uri;

        /**
         * @brief The image's MIME type. Required if `bufferView` is defined.
         */
        std::optional<MimeType> mimeType;

        /**
         * @brief The index of the bufferView that contains the image. Use this instead of the image's uri property.
         */
        int32_t bufferView = -1;

    private:
      /**
       * @brief This class is not mean to be instantiated directly. Use {@link Image} instead.
       */
      ImageSpec() = default;
      friend struct Image;

    };
}
