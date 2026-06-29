#pragma once

#include "battle.h"
#include "iattempt.h"
#include "icondition.h"
#include "inumber.h"
#include <memory>

struct Attempt : IAttempt {
  // Animation
  std::unique_ptr<ICondition<Always100>> accuracy_;
  // std::unique_ptr<IEffect> onHit_;
  // std::unique_ptr<IEffect> onMiss_;
  // std::unique_ptr<IEffect> after_;
  void Execute(Battle) override {}
};

struct Combo : IAttempt {

  void Execute(Battle) override {}

  // Animation
  std::unique_ptr<ICondition<Always100>> accuracy_;
  std::unique_ptr<INumber> hits_;
  // std::unique_ptr<IEffect> every_;
};

struct Cascade : IAttempt {

  void Execute(Battle) override {}
  std::vector<std::unique_ptr<IAttempt>> attempts_;
};
