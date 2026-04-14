#pragma once

#include "battle.h"
#include "imove.h"
#include <iostream>

struct Example : public IMove {

  void Execute(Battle battle) override {
    std::cout << "Move executed" << std::endl;
    (void)battle;
  }
};
