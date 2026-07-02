#pragma once

#include "elements.h"
#include "imove.h"
#include <string>
#include <vector>

struct Battler {

  std::string name_{};
  double hp_{};
  std::vector<Element> elements_{};
  std::vector<Move> moves_{};
};
