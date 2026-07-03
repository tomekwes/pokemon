#pragma once
#include "../battle.h"

struct INumber {

  virtual double calculate(Battle battle) = 0;

  virtual ~INumber() = default;
};

struct Always100 : INumber {

  double calculate(Battle) override { return 100.0; }
};
