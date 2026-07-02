#pragma once

#include "battle.h"
#include "battler.h"

template <typename T> struct ICondition {
  virtual bool operator()(T const &param) = 0;
  virtual ~ICondition() = default;
};

struct IBattleCondition : ICondition<Battle> {
  virtual bool operator()(Battle const &battle) = 0;
};

struct IBattlerCondition : ICondition<Battler> {
  virtual bool operator()(Battler const &battle) = 0;
};
