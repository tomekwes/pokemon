#pragma once

#include "battle.h"
#include "elements.h"
#include "interface/icondition.h"
#include "interface/itarget.h"
#include "utils.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <random>

using utils::HaveSameCallOperator;

struct InRain : IBattleCondition {
  bool operator()(Battle const &battle) override {
    return battle.weather_ == Weather::RAINING;
  }
};

struct InSnow : IBattleCondition {
  bool operator()(Battle const &battle) override {
    return battle.weather_ == Weather::SNOWING;
  }
};

template <typename T> struct Prob : ICondition<T> {

  Prob(double prob) : rd(), gen(rd()), prob_(prob) {}
  bool operator()(T const &input) override {

    std::bernoulli_distribution dist(prob_);
    return dist(gen);
  }
  std::random_device rd;
  std::mt19937 gen;
  double prob_{0.0};
};

template <typename T, typename LHS, typename RHS>
// by the way that operator accepts one param they need to accept the same thing
  requires HaveSameCallOperator<LHS, RHS, T>
struct And : ICondition<T> {

  And(LHS lhs, RHS rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

  bool operator()(T const &input) override {
    return lhs_(input) && rhs_(input);
  }

  LHS lhs_;
  RHS rhs_;
};

template <typename T, typename LHS, typename RHS>
// by the way that operator accepts one param they need to accept the same thing
  requires HaveSameCallOperator<LHS, RHS, T>
struct Or : ICondition<T> {

  Or(LHS lhs, RHS rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

  bool operator()(T const &input) override {
    return lhs_(input) || rhs_(input);
  }

  LHS lhs_;
  RHS rhs_;
};

struct For : ICondition<Battle> {

  For(std::unique_ptr<ITarget> t, std::unique_ptr<ICondition<Battler>> c)
      : target_(std::move(t)), cond_(std::move(c)) {}

  bool operator()(Battle const &input) override {
    return std::invoke(*cond_, *(target_->Resolve(input)));
  }

  std::unique_ptr<ITarget> target_;
  std::unique_ptr<ICondition<Battler>> cond_;
};

struct HasElement : ICondition<Battler> {

  HasElement(Element e) : elem_{e} {}

  bool operator()(Battler const &input) override {

    auto it = std::find(input.elements_.begin(), input.elements_.end(), elem_);
    return it != input.elements_.end();
  }

  const Element elem_;
};
