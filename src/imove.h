#pragma once

#include "elements.h"
#include "icondition.h"
#include <iostream>
#include <memory>
#include <string>

struct Battle;

struct IMove {
  virtual void Execute(Battle) = 0;
};

struct WithPrecondition : public IMove {

  WithPrecondition(std::unique_ptr<IMove> mv,
                   std::unique_ptr<IBattleCondition> bc)
      : move_(std::move(mv)), cond_(std::move(bc)) {}
  std::unique_ptr<IMove> move_;
  std::unique_ptr<IBattleCondition> cond_;

  void Execute(Battle battle) override {
    if ((*cond_)(battle)) {
      move_->Execute(battle);
    } else {
      std::cout << "Move failed on this battlefiled" << std::endl;
    }
  }
};

struct WithAplicability : public IMove {

  WithAplicability(std::unique_ptr<IMove> mv,
                   std::unique_ptr<IBattlerCondition> bc)
      : move_(std::move(mv)), cond_(std::move(bc)) {}
  std::unique_ptr<IMove> move_;
  std::unique_ptr<IBattlerCondition> cond_;

  void Execute(Battle battle) override {
    if ((*cond_)(battle.defender_)) {
      move_->Execute(battle);
    } else {
      std::cout << "Move failed against this defender" << std::endl;
    }
  }
};

struct Move : public IMove {
  Move(std::string name, Element elem) : name_{name}, element_{elem} {}
  std::string name_;
  Element element_;
};
