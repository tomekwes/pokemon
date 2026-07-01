#pragma once

#include "battle.h"
#include "elements.h"
#include "icondition.h"
#include "itarget.h"
#include "utils.h"
#include <algorithm>
#include <functional>
#include <memory>

struct InRain : IBattleCondition {
  bool operator()(Battle battle) override {
    return battle.weather_ == Weather::RAINING;
  }
};

struct InSnow : IBattleCondition {
  bool operator()(Battle battle) override {
    return battle.weather_ == Weather::SNOWING;
  }
};

template <typename T, typename LHS, typename RHS>
// by the way that operator accepts one param they need to accept the same thing
  requires HaveSameCallOperator<LHS, RHS, T>
struct And : ICondition<T> {

  And(LHS lhs, RHS rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

  bool operator()(T input) override { return lhs_(input) && rhs_(input); }

  LHS lhs_;
  RHS rhs_;
};

template <typename T, typename LHS, typename RHS>
// by the way that operator accepts one param they need to accept the same thing
  requires HaveSameCallOperator<LHS, RHS, T>
struct Or : ICondition<T> {

  Or(LHS lhs, RHS rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

  bool operator()(T input) override { return lhs_(input) || rhs_(input); }

  LHS lhs_;
  RHS rhs_;
};

struct For : ICondition<Battle> {

  For(std::unique_ptr<ITarget> t, std::unique_ptr<ICondition<Battler>> c)
      : target_(std::move(t)), cond_(std::move(c)) {}

  bool operator()(Battle input) override {
    return std::invoke(*cond_, target_->Resolve(input));
  }

  std::unique_ptr<ITarget> target_;
  std::unique_ptr<ICondition<Battler>> cond_;
};

struct HasElement : ICondition<Battler> {

  HasElement(Element e) : elem_{e} {}

  bool operator()(Battler input) override {

    auto it = std::find(input.elements.begin(), input.elements.end(), elem_);
    return it != input.elements.end();
  }

  const Element elem_;
};
