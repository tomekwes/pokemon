#pragma once

#include "../battle.h"

struct IEffect {

  virtual void Apply(Battle) = 0;

  virtual ~IEffect() = default;
};
