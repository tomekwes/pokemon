#pragma once
#include "../battle.h"
#include "../battler.h"
#include <memory>

struct ITarget {

  virtual std::shared_ptr<Battler> Resolve(Battle const &) = 0;
  virtual ~ITarget() = default;
};

struct Attacker : ITarget {

  std::shared_ptr<Battler> Resolve(Battle const &batttle) override {
    return batttle.attacker_;
  }
};

struct Defender : ITarget {

  std::shared_ptr<Battler> Resolve(Battle const &batttle) override {
    return batttle.defender_;
  }
};
