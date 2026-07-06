#pragma once

#include "elements.h"
#include "interface/imove.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Battler {

  std::string name_{};
  double hp_{};
  double defense_{};
  std::vector<Element> elements_{};
  std::vector<std::unique_ptr<IMove>> moves_{};

  void print_stats() {
    std::cout << "Hp: " << hp_ << " Defense " << defense_ << std::endl;
  }
};
