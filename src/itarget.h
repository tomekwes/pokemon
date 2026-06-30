#pragma once
#include "battle.h"
#include "battler.h"

struct iTarget {

  virtual Battler Resolve(Battle) = 0;
  virtual ~iTarget();
};
