#pragma once

#include "battle.h"

struct IAttempt {
  virtual void Execute(Battle) = 0;
  virtual ~IAttempt() = default;
};
