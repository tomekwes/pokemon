#pragma once

#include "battle.h"
#include "imove.h"
#include <iostream>

struct Example : public Move {
  using Move::Move;
  void Execute(Battle battle) override {
    std::cout << "Move " << name_ << " executed" << std::endl;
    (void)battle;
  }
};
