// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#include "AnimationSamplerJsonHandler.h"
#include "CesiumGltf/AnimationSampler.h"

#include <cassert>
#include <string>

using namespace CesiumGltf;

AnimationSamplerJsonHandler::AnimationSamplerJsonHandler(const ReaderContext& context) noexcept : ExtensibleObjectJsonHandler(context), _input(), _interpolation(), _output() {}

void AnimationSamplerJsonHandler::reset(CesiumJsonReader::IJsonHandler* pParentHandler, AnimationSampler* pObject) {
  ExtensibleObjectJsonHandler::reset(pParentHandler, pObject);
  this->_pObject = pObject;
}

CesiumJsonReader::IJsonHandler* AnimationSamplerJsonHandler::readObjectKey(const std::string_view& str) {
  assert(this->_pObject);
  return this->readObjectKeyAnimationSampler(AnimationSampler::TypeName, str, *this->_pObject);
}

CesiumJsonReader::IJsonHandler* AnimationSamplerJsonHandler::readObjectKeyAnimationSampler(const std::string& objectType, const std::string_view& str, AnimationSampler& o) {
  using namespace std::string_literals;

  if ("input"s == str) return property("input", this->_input, o.input);
  if ("interpolation"s == str) return property("interpolation", this->_interpolation, o.interpolation);
  if ("output"s == str) return property("output", this->_output, o.output);

  return this->readObjectKeyExtensibleObject(objectType, str, *this->_pObject);
}

void AnimationSamplerJsonHandler::InterpolationJsonHandler::reset(CesiumJsonReader::IJsonHandler* pParent, AnimationSampler::Interpolation* pEnum) {
  JsonHandler::reset(pParent);
  this->_pEnum = pEnum;
}

CesiumJsonReader::IJsonHandler* AnimationSamplerJsonHandler::InterpolationJsonHandler::readString(const std::string_view& str) {
  using namespace std::string_literals;

  assert(this->_pEnum);

  if ("LINEAR"s == str) *this->_pEnum = AnimationSampler::Interpolation::LINEAR;
  else if ("STEP"s == str) *this->_pEnum = AnimationSampler::Interpolation::STEP;
  else if ("CUBICSPLINE"s == str) *this->_pEnum = AnimationSampler::Interpolation::CUBICSPLINE;
  else return nullptr;

  return this->parent();
}
