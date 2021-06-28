// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/ExtensibleObject.h"
#include "CesiumGltf/Library.h"

namespace CesiumGltf {
    /**
     * @brief An orthographic camera containing properties to create an orthographic projection matrix.
     */
    struct CESIUMGLTF_API CameraOrthographic final : public ExtensibleObject {
        static inline constexpr const char* TypeName = "CameraOrthographic";

        /**
         * @brief The floating-point horizontal magnification of the view. Must not be zero.
         */
        double xmag = double();

        /**
         * @brief The floating-point vertical magnification of the view. Must not be zero.
         */
        double ymag = double();

        /**
         * @brief The floating-point distance to the far clipping plane. `zfar` must be greater than `znear`.
         */
        double zfar = double();

        /**
         * @brief The floating-point distance to the near clipping plane.
         */
        double znear = double();

    };
}
