#pragma once

#include "battler.h"
#include "elements.h"
#include <memory>

struct Battle {
  std::shared_ptr<Battler> attacker_;
  std::shared_ptr<Battler> defender_;
  Weather weather_;

  void SwapPositions() { std::swap(attacker_, defender_); }
};
