#pragma once

#include "battler.h"
#include "elements.h"

struct Battle {
  Battler attacker_;
  Battler defender_;
  Weather weather_;

  void SwapPositions() { std::swap(attacker_, defender_); }
};
