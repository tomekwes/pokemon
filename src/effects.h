#pragma once

#include "battle.h"
#include "interface/ieffect.h"
#include <vector>

struct NoEffect : IEffect {
  void Apply(Battle) override {}
};

struct SequenceEffects : IEffect {

  void Apply(Battle b) override {
    for (const auto &ef : effects_) {
      ef->Apply(b);
    }
  }

  std::vector<IEffect *> effects_;
};
