#pragma once

#include <concepts>

// Concept that checks if two types accept the same
// type to their ::operator()
template <typename T, typename F, typename Param>
concept HaveSameCallOperator = requires(T o1, F o2, Param p) {
  o1(p);
  o2(p);
};
