#pragma once

#include <CesiumGltf/SharedAssetDepot.h>
#include <CesiumUtility/ExtensibleObject.h>
#include <CesiumUtility/IntrusivePointer.h>

#include <atomic>

namespace CesiumGltf {

/**
 * @brief An asset that is potentially shared between multiple objects, such as
 * an image shared between multiple glTF models. This is intended to be the base
 * class for such assets.
 *
 * The lifetime of instances of this class should be managed by reference
 * counting with {@link IntrusivePointer}.
 *
 * @tparam T The type that is _deriving_ from this class. For example, you
 * should declare your class as
 * `class MyClass : public SharedAsset<MyClass> { ... };`
 */
template <typename T>
class CESIUMGLTF_API SharedAsset : public CesiumUtility::ExtensibleObject {
public:
  SharedAsset() = default;

  // Assets can be copied, but the fresh instance has no references and is not
  // in the asset depot.
  SharedAsset(const SharedAsset& rhs)
      : ExtensibleObject(rhs),
        _referenceCount(0),
        _pDepot(nullptr),
        _uniqueAssetId() {}

  // Move construction is not allowed, because existing references to this
  // shared asset would be affected as well.
  SharedAsset(SharedAsset&& rhs) = delete;

  // Assignment does not affect the asset's relationship with the depot, but is
  // useful to assign the data in derived classes.
  SharedAsset& operator=(const SharedAsset& rhs) {
    CesiumUtility::ExtensibleObject::operator=(rhs);
    return *this;
  }

  SharedAsset& operator=(SharedAsset&& rhs) {
    CesiumUtility::ExtensibleObject::operator=(std::move(rhs));
    return *this;
  }

  /**
   * @brief Adds a counted reference to this object. Use
   * {@link CesiumUtility::IntrusivePointer} instead of calling this method
   * directly.
   */
  void addReference() const /*noexcept*/ { ++this->_referenceCount; }

  /**
   * @brief Removes a counted reference from this object. When the last
   * reference is removed, this method will delete this instance. Use
   * {@link CesiumUtility::IntrusivePointer} instead of calling this method
   * directly.
   */
  void releaseReference() const /*noexcept*/ {
    CESIUM_ASSERT(this->_referenceCount > 0);
    const int32_t references = --this->_referenceCount;
    if (references == 0) {
      CesiumUtility::IntrusivePointer<SharedAssetDepot<T>> pDepot =
          this->_pDepot;
      if (pDepot) {
        // Let the depot manage this object's lifetime.
        pDepot->markDeletionCandidate(
            this->_uniqueAssetId,
            const_cast<T*>(static_cast<const T*>(this)));
      } else {
        // No depot, so destroy this object directly.
        delete static_cast<const T*>(this);
      }
    }
  }

private:
  mutable std::atomic<std::int32_t> _referenceCount{0};
  CesiumUtility::IntrusivePointer<SharedAssetDepot<T>> _pDepot;
  std::string _uniqueAssetId;

  // To allow the depot to modify _pDepot and _uniqueAssetId.
  friend class SharedAssetDepot<T>;
};

} // namespace CesiumGltf
