// This file was generated by generate-gltf-classes.
// DO NOT EDIT THIS FILE!
#include "AnimationChannelJsonHandler.h"
#include "CesiumGltf/AnimationChannel.h"

#include <cassert>
#include <string>

using namespace CesiumGltf;

AnimationChannelJsonHandler::AnimationChannelJsonHandler(
    ReadModelOptions options) noexcept
    : ExtensibleObjectJsonHandler(options),
      _sampler(options),
      _target(options) {}

void AnimationChannelJsonHandler::reset(
    IJsonHandler* pParent,
    AnimationChannel* pObject) {
  ExtensibleObjectJsonHandler::reset(pParent, pObject);
  this->_pObject = pObject;
}

AnimationChannel* AnimationChannelJsonHandler::getObject() {
  return this->_pObject;
}

void AnimationChannelJsonHandler::reportWarning(
    const std::string& warning,
    std::vector<std::string>&& context) {
  if (this->getCurrentKey()) {
    context.emplace_back(std::string(".") + this->getCurrentKey());
  }
  this->parent()->reportWarning(warning, std::move(context));
}

IJsonHandler* AnimationChannelJsonHandler::Key(
    const char* str,
    size_t /*length*/,
    bool /*copy*/) {
  assert(this->_pObject);
  return this->AnimationChannelKey(str, *this->_pObject);
}

IJsonHandler* AnimationChannelJsonHandler::AnimationChannelKey(
    const char* str,
    AnimationChannel& o) {
  using namespace std::string_literals;

  if ("sampler"s == str)
    return property("sampler", this->_sampler, o.sampler);
  if ("target"s == str)
    return property("target", this->_target, o.target);

  return this->ExtensibleObjectKey(str, *this->_pObject);
}
