#pragma once

#include "elements.h"
#include <string>

struct Battle;

struct IMove {
  virtual void Execute(Battle) = 0;
  virtual ~IMove() = default;
};

struct Move : public IMove {
  Move(std::string name, Element elem) : name_{name}, element_{elem} {}
  std::string name_;
  Element element_;
};
