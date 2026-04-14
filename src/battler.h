#pragma once

#include "elements.h"
#include <string>
#include <vector>

struct Battler {

  std::string name{};
  double hp{};
  std::vector<Element> elements;
};
