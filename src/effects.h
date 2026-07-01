#pragma once

#include "battle.h"
#include "ieffect.h"

struct NoEffect : IEffect {
  void Apply(Battle) {}
};
