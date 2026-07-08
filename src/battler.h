#pragma once

#include "elements.h"
#include "interface/imove.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

enum class StageStatError : std::uint8_t { OK, WONT_GO_HIGHER, WONT_GO_LOWER };

// So in pokemon stats have stages and they act as multiplyers
// on stats with following formula
// For Positive Stages (0 to +6): (2 + s)/2
// For Negative Stages (-1 to -6): 2/(2 + |s|)
struct StageStat {

  StageStat(double value) : statValue_(value) {}

  StageStatError lower_stage() {
    if (MIN_STAGE == stage_) {
      return StageStatError::WONT_GO_LOWER;
    }

    stage_--;
    return StageStatError::OK;
  }

  StageStatError increase_stage() {
    if (MAX_STAGE == stage_) {
      return StageStatError::WONT_GO_HIGHER;
    }

    stage_++;
    return StageStatError::OK;
  }

  void reset_stage() { stage_ = 0; }

  double get_stat_value() const {

    double retval = statValue_;
    double multiplyer{0.0};
    if (stage_ >= 0) {
      multiplyer = (2.0 + stage_) / 2.0;
    } else {
      multiplyer = 2.0 / (2 + -stage_);
    }

    return std::floor(retval * multiplyer);
  }

  friend std::ostream &operator<<(std::ostream &os, StageStat s);

private:
  std::int8_t stage_{0};
  double statValue_{0.0};
  const std::int8_t MAX_STAGE{6};
  const std::int8_t MIN_STAGE{-6};
};

inline std::ostream &operator<<(std::ostream &os, StageStat s) {
  os << "(" << s.statValue_ << ", " << static_cast<int>(s.stage_) << ")";
  return os;
}

struct Battler {

  std::string name_{};
  double hp_{};
  StageStat defense_;
  std::vector<Element> elements_{};
  std::vector<std::unique_ptr<IMove>> moves_{};

  void print_stats() {
    std::cout << "Hp: " << hp_ << " Defense " << defense_.get_stat_value()
              << std::endl;
  }
};
