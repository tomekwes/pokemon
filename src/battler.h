#pragma once

#include "elements.h"
#include "interface/imove.h"
#include <memory>
#include <string>
#include <vector>

struct Battler {

  std::string name_{};
  double hp_{};
  std::vector<Element> elements_{};
  std::vector<std::unique_ptr<Move>> moves_{};
};
