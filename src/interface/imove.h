#pragma once

#include "../elements.h"
#include <string>

struct Battle;

struct IMove {
  virtual void Execute(Battle &) = 0;
  virtual std::string GetName() const = 0;
  // todo: add get type
  virtual ~IMove() = default;
};

// todo: probably not needed
struct Move : public IMove {
  Move(std::string name, Element elem) : name_{name}, element_{elem} {}
  std::string GetName() const { return name_; }

  std::string name_;
  Element element_;
};
