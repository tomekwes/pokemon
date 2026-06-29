#pragma once

#include "battle.h"
#include "icondition.h"
#include "imove.h"
#include <iostream>
#include <memory>

struct Example : public Move {
  using Move::Move;
  void Execute(Battle battle) override {
    std::cout << "Move " << name_ << " executed" << std::endl;
    (void)battle;
  }
};

struct WithPrecondition : public IMove {

  WithPrecondition(std::unique_ptr<IMove> mv,
                   std::unique_ptr<ICondition<Battle>> bc)
      : move_(std::move(mv)), cond_(std::move(bc)) {}
  std::unique_ptr<IMove> move_;
  std::unique_ptr<ICondition<Battle>> cond_;

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
