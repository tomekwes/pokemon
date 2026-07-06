#pragma once
#include "../battle.h"
#include "../battler.h"
#include <memory>

struct ITarget {

  virtual std::shared_ptr<Battler> Resolve(Battle const &) = 0;
  virtual ~ITarget() = default;
};

struct Attacker : ITarget {

  std::shared_ptr<Battler> Resolve(Battle const &battle) override {
    return battle.attacker_;
  }
};

struct Defender : ITarget {

  std::shared_ptr<Battler> Resolve(Battle const &battle) override {
    return battle.defender_;
  }
};
