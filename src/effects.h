#pragma once

#include "battle.h"
#include "battler.h"
#include "interface/icondition.h"
#include "interface/ieffect.h"
#include "interface/itarget.h"
#include "utils.h"
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

struct Condition : IEffect {

  Condition(std::unique_ptr<ICondition<Battle>> c) : cond_(std::move(c)) {}
  void Apply(Battle &b) override {
    bool result = (*cond_)(b);

    if (result && on_pass_.has_value()) {
      on_pass_.value()->Apply(b);
    }
    if (!result && on_fail_.has_value()) {
      on_fail_.value()->Apply(b);
    }
  }

  std::optional<std::unique_ptr<IEffect>> on_pass_;
  std::optional<std::unique_ptr<IEffect>> on_fail_;
  std::unique_ptr<ICondition<Battle>> cond_;
};

struct LowerDefense : IEffect {

  LowerDefense(std::unique_ptr<ITarget> t) : target_(std::move(t)) {}

  void Apply(Battle &b) {
    auto who = target_->Resolve(b);
    const auto err = who->defense_.lower_stage();
    if (err != StageStatError::OK) {
      std::cout << utils::to_string(err) << std::endl;
    }
  }

  std::unique_ptr<ITarget> target_;
};
