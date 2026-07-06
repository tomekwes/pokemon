#pragma once

#include "battle.h"
#include "interface/icondition.h"
#include "interface/ieffect.h"
#include "interface/imove.h"
#include <iostream>
#include <memory>

struct Example : public Move {
  using Move::Move;
  void Execute(Battle &battle) override {
    std::cout << "Move " << name_ << " executed by " << battle.attacker_->name_
              << std::endl;
  }
};

struct WithPrecondition : public IMove {

  WithPrecondition(std::unique_ptr<IMove> mv,
                   std::unique_ptr<ICondition<Battle>> bc)
      : move_(std::move(mv)), cond_(std::move(bc)) {}
  std::unique_ptr<IMove> move_;
  std::unique_ptr<ICondition<Battle>> cond_;

  std::string GetName() const override { return "WithPrecondition"; }

  void Execute(Battle &battle) override {
    if ((*cond_)(battle)) {
      move_->Execute(battle);
    } else {
      std::cout << "Move " << move_->GetName() << " failed on this battlefield"
                << std::endl;
    }
  }
};

struct WithAplicability : public IMove {

  WithAplicability(std::unique_ptr<IMove> mv,
                   std::unique_ptr<IBattlerCondition> bc)
      : move_(std::move(mv)), cond_(std::move(bc)) {}

  // maybe better to return move_->GetName() ?
  std::string GetName() const override { return "WithAplicability"; }

  void Execute(Battle &battle) override {
    if ((*cond_)(*battle.defender_)) {
      move_->Execute(battle);
    } else {
      std::cout << "Move " << move_->GetName()
                << " failed against this defender" << std::endl;
    }
  }

  std::unique_ptr<IMove> move_;
  std::unique_ptr<IBattlerCondition> cond_;
};

struct Leer : public IMove {

  Leer(std::unique_ptr<IEffect> ld) : ld_(std::move(ld)) {}

  void Execute(Battle &battle) override { ld_->Apply(battle); }
  std::string GetName() const override { return "Leer"; }
  std::unique_ptr<IEffect> ld_;
};
