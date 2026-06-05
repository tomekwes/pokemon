#pragma once

#include "battler.h"
#include "elements.h"

struct Battle {
  Battler attacker_;
  Battler defender_;
  Weather weather_;
};
