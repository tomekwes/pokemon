#pragma once

#include "battle.h"
#include "elements.h"
#include "icondition.h"
#include "utils.h"
#include <concepts>
#include <iostream>

struct InRain : IBattleCondition {
  bool operator()(Battle battle) override {
    std::cout << "InRain making the check" << std::endl;
    return battle.weather_ == Weather::RAINING;
  }
};

struct InSnow : IBattleCondition {
  bool operator()(Battle battle) override {
    std::cout << "InSnow making the check" << std::endl;
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
