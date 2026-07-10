#pragma once

#include "battle.h"
#include "battler.h"
#include "interface/icondition.h"
#include "interface/ieffect.h"
#include "interface/itarget.h"
#include "utils.h"
#include <cmath>
#include <memory>
#include <vector>

struct NoEffect : IEffect {
  void Apply(Battle &) override {}
};

struct SequenceEffects : IEffect {

  void Apply(Battle &b) override {
    for (const auto &ef : effects_) {
      ef->Apply(b);
    }
  }

  std::vector<IEffect *> effects_;
};

struct Condition : IEffect {

  Condition(std::unique_ptr<ICondition<Battle>> c) : cond_(std::move(c)) {}
  void Apply(Battle &b) override {
    bool result = (*cond_)(b);

    if (result && on_pass_.has_value()) {
      on_pass_.value()->Apply(b);
    }
    if (!result && on_fail_.has_value()) {
      on_fail_.value()->Apply(b);
    }
  }

  std::optional<std::unique_ptr<IEffect>> on_pass_;
  std::optional<std::unique_ptr<IEffect>> on_fail_;
  std::unique_ptr<ICondition<Battle>> cond_;
};

struct FormulaDamage : IEffect {

  void Apply(Battle &b) override {

    // auto m =
    //     modifier(double weather, double critical, double stab, double type);
  }

  // Modifier = Targets x Weather x Critical x Random x STAB x Type
  // thats a full formula but I will skip Targets for now since its 1v1
  // Targets: 1.0 if it's a single-target battle (like a standard 1v1).
  // Weather: 1.5 if a weather condition boosts the move type, 0.5 if it weakens
  //  it (Weather doesn't affect Fighting-type moves like Rock Smash, so
  //  it's 1.0). Critical: 1.5 if the move lands a critical hit (1.0 otherwise).
  // Random: A random decimal factor between 0.85 and 1.00. (In the actual code,
  //  it picks a random integer between 85 and 100, then divides by 100). STAB
  // (Same-Type Attack Bonus): 1.5 if the Pokémon using Rock Smash is a
  //  Fighting-type. 1.0 if it is any other type. Type: The type-effectiveness
  //  multiplier against the target (can be 0.0, 0.25, 0.5, 1.0, 2.0, or 4.0).
  //  For example, Rock Smash vs. a Normal-type Pokémon is Super Effective
  //  (2.0).

  inline double modifier(double weather, double critical, double stab,
                         double type) const {
    return weather * critical * stab * type;
  }

  // d = floor( ( floor((2xlevel)/5 +2 ) * power  x A/D) / 50) + 2 x modifier
  // Level: The level of the attacking Pokémon (1–100).
  // Power: The base power of the move. For Rock Smash, this is 20.
  // A (Effective Attack): The current Attack stat of your Pokémon (factoring in
  //  its stat stages). Because Rock Smash is a Physical move, it uses Attack
  //  (not Sp. Atk).
  // D (Effective Defense): The current Defense stat of the
  //  target Pokémon (factoring in its stat stages before Rock Smash hits). It
  //  uses Defense (not Sp. Def).
  inline double formula(int pokemonLevel, double movePower,
                        double pokemonAttack, double pokemonDefense,
                        double modifier) const {
    return floor((floor((2.0 * pokemonLevel) / 5.0 + 2) * movePower *
                  (pokemonAttack / pokemonDefense)) /
                 50.0) +
           2 * modifier;
  }
};

struct LowerDefense : IEffect {

  LowerDefense(std::unique_ptr<ITarget> t) : target_(std::move(t)) {}

  void Apply(Battle &b) {
    auto who = target_->Resolve(b);
    const auto err = who->defense_.lower_stage();
    if (err != StageStatError::OK) {
      std::cout << utils::to_string(err) << std::endl;
    }
  }

  std::unique_ptr<ITarget> target_;
};
