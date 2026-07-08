#pragma once

#include "battler.h"
#include <concepts>

namespace utils {
// Concept that checks if two types accept the same
// type to their ::operator()
template <typename T, typename F, typename Param>
concept HaveSameCallOperator = requires(T o1, F o2, Param p) {
  o1(p);
  o2(p);
};

inline constexpr std::string_view to_string(StageStatError e) {
  switch (e) {
  case StageStatError::OK:
    return "OK";
  case StageStatError::WONT_GO_HIGHER:
    return "Higher";
  case StageStatError::WONT_GO_LOWER:
    return "Lower";
  default:
    return "Unknown";
  }
}

} // namespace utils
