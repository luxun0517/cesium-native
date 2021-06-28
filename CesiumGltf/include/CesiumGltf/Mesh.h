// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "CesiumGltf/Library.h"
#include "CesiumGltf/MeshPrimitive.h"
#include "CesiumGltf/NamedObject.h"
#include <vector>

namespace CesiumGltf {
    /**
     * @brief A set of primitives to be rendered.  A node can contain one mesh.  A node's transform places the mesh in the scene.
     */
    struct CESIUMGLTF_API Mesh final : public NamedObject {
        static inline constexpr const char* TypeName = "Mesh";

        /**
         * @brief An array of primitives, each defining geometry to be rendered with a material.
         */
        std::vector<MeshPrimitive> primitives;

        /**
         * @brief Array of weights to be applied to the Morph Targets.
         */
        std::vector<double> weights;

    };
}
