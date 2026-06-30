#pragma once
#include "battle.h"
#include "battler.h"

struct ITarget {

  virtual Battler Resolve(Battle) = 0;
  virtual ~ITarget();
};

struct Attacker : ITarget {

  Battler Resolve(Battle batttle) override { return batttle.attacker_; }
};

struct Defender : ITarget {

  Battler Resolve(Battle batttle) override { return batttle.defender_; }
};
