#pragma once
#include "../battle.h"
#include "interface/itarget.h"
#include <memory>

struct INumber {

  virtual double Calculate(Battle &battle) = 0;

  virtual ~INumber() = default;
};

struct Always100 : INumber {

  double Calculate(Battle &) override { return 100.0; }
};

struct CurrentDefense : INumber {

  CurrentDefense(std::unique_ptr<ITarget> t) : target_(std::move(t)) {}

  double Calculate(Battle &b) override {
    return target_->Resolve(b)->defense_.get_stat_value();
  }

  std::unique_ptr<ITarget> target_;
};

struct XPercent : INumber {

  XPercent(std::unique_ptr<INumber> n, double p)
      : n_(std::move(n)), p_(p / 100.0) {}

  double Calculate(Battle &b) override { return n_->Calculate(b) * p_; }

  std::unique_ptr<INumber> n_;
  double p_;
};
