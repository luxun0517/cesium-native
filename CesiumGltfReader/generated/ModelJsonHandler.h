// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#pragma once

#include "AccessorJsonHandler.h"
#include "AnimationJsonHandler.h"
#include "AssetJsonHandler.h"
#include "BufferJsonHandler.h"
#include "BufferViewJsonHandler.h"
#include "CameraJsonHandler.h"
#include "CesiumGltf/ReaderContext.h"
#include "CesiumJsonReader/ArrayJsonHandler.h"
#include "CesiumJsonReader/IntegerJsonHandler.h"
#include "CesiumJsonReader/StringJsonHandler.h"
#include "ExtensibleObjectJsonHandler.h"
#include "ImageJsonHandler.h"
#include "MaterialJsonHandler.h"
#include "MeshJsonHandler.h"
#include "NodeJsonHandler.h"
#include "SamplerJsonHandler.h"
#include "SceneJsonHandler.h"
#include "SkinJsonHandler.h"
#include "TextureJsonHandler.h"

namespace CesiumGltf {
  struct ReaderContext;
  struct Model;

  class ModelJsonHandler : public ExtensibleObjectJsonHandler {
  public:
    using ValueType = Model;

    ModelJsonHandler(const ReaderContext& context) noexcept;
    void reset(IJsonHandler* pParentHandler, Model* pObject);

    virtual IJsonHandler* readObjectKey(const std::string_view& str) override;

  protected:
    IJsonHandler* readObjectKeyModel(const std::string& objectType, const std::string_view& str, Model& o);

  private:

    Model* _pObject = nullptr;
    CesiumJsonReader::ArrayJsonHandler<std::string, CesiumJsonReader::StringJsonHandler> _extensionsUsed;
    CesiumJsonReader::ArrayJsonHandler<std::string, CesiumJsonReader::StringJsonHandler> _extensionsRequired;
    CesiumJsonReader::ArrayJsonHandler<Accessor, AccessorJsonHandler> _accessors;
    CesiumJsonReader::ArrayJsonHandler<Animation, AnimationJsonHandler> _animations;
    AssetJsonHandler _asset;
    CesiumJsonReader::ArrayJsonHandler<Buffer, BufferJsonHandler> _buffers;
    CesiumJsonReader::ArrayJsonHandler<BufferView, BufferViewJsonHandler> _bufferViews;
    CesiumJsonReader::ArrayJsonHandler<Camera, CameraJsonHandler> _cameras;
    CesiumJsonReader::ArrayJsonHandler<Image, ImageJsonHandler> _images;
    CesiumJsonReader::ArrayJsonHandler<Material, MaterialJsonHandler> _materials;
    CesiumJsonReader::ArrayJsonHandler<Mesh, MeshJsonHandler> _meshes;
    CesiumJsonReader::ArrayJsonHandler<Node, NodeJsonHandler> _nodes;
    CesiumJsonReader::ArrayJsonHandler<Sampler, SamplerJsonHandler> _samplers;
    CesiumJsonReader::IntegerJsonHandler<int32_t> _scene;
    CesiumJsonReader::ArrayJsonHandler<Scene, SceneJsonHandler> _scenes;
    CesiumJsonReader::ArrayJsonHandler<Skin, SkinJsonHandler> _skins;
    CesiumJsonReader::ArrayJsonHandler<Texture, TextureJsonHandler> _textures;
  };
}
