#pragma once

struct Battle;

struct IMove {
  virtual void Execute(Battle) = 0;
};
