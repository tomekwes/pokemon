#pragma once

#include "battle.h"
#include "interface/ieffect.h"
#include "interface/inumber.h"
#include "interface/itarget.h"
#include <memory>
#include <vector>

struct NoEffect : IEffect {
  void Apply(Battle &) override {}
};

struct SequenceEffects : IEffect {

  void Apply(Battle &b) override {
    for (const auto &ef : effects_) {
      ef->Apply(b);
    }
  }

  std::vector<IEffect *> effects_;
};

struct LowerDefense : IEffect {

  LowerDefense(std::unique_ptr<ITarget> t, std::unique_ptr<INumber> v)
      : target_(std::move(t)), value_(std::move(v)) {}

  void Apply(Battle &b) {
    auto who = target_->Resolve(b);
    who->defense_ -= value_->Calculate(b);
  }

  std::unique_ptr<ITarget> target_;
  std::unique_ptr<INumber> value_;
};
