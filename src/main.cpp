#include "battle.h"
#include "elements.h"
#include "interface/imove.h"
#include "pokemons.h"
#include <iostream>
#include <memory>

int main() {
  std::cout << "A battle begins" << std::endl;

  Battle arena;
  arena.weather_ = Weather::RAIN;
  arena.attacker_ = make_machop();
  arena.defender_ = make_machop();

  arena.attacker_->print_stats();
  arena.defender_->print_stats();
  arena.attacker_->moves_[0]->Execute(arena);
  arena.attacker_->moves_[0]->Execute(arena);
  arena.attacker_->moves_[0]->Execute(arena);
  arena.attacker_->moves_[0]->Execute(arena);
  arena.attacker_->print_stats();
  arena.defender_->print_stats();
}
