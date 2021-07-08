#pragma once

#if __cplusplus >= 201703L

#define CESIUM_NODISCARD [[nodiscard]]
#define CESIUM_UNUSED [[maybe_unused]]

#else

#include <type_traits>

#define CESIUM_NODISCARD
#define CESIUM_UNUSED

namespace std {

enum class byte : unsigned char {};

template <class T>
constexpr typename std::add_const<T>::type& as_const(T& t) noexcept {
  return t;
}

template <class T, class U>
inline constexpr bool is_same_v = is_same<T, U>::value;

} // namespace std

#endif