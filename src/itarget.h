#pragma once
#include "battle.h"
#include "battler.h"

struct ITarget {

  virtual Battler Resolve(Battle const &) = 0;
  virtual ~ITarget() = default;
};

struct Attacker : ITarget {

  Battler Resolve(Battle const &batttle) override { return batttle.attacker_; }
};

struct Defender : ITarget {

  Battler Resolve(Battle const &batttle) override { return batttle.defender_; }
};
