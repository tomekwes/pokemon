#pragma once

#include "battle.h"
#include "elements.h"
#include "icondition.h"
#include <iostream>

struct OnlyInRain : IBattleCondition {
  bool operator()(Battle battle) override {
    std::cout << "making the check" << std::endl;
    return battle.weather_ == Weather::RAINING;
  }
};
