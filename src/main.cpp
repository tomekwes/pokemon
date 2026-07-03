#include "battle.h"
#include "battler.h"
#include "conditions.h"
#include "elements.h"
#include "interface/imove.h"
#include "interface/itarget.h"
#include "moves.h"
#include "pokemons.h"
#include <iostream>
#include <memory>

int main() {
  std::cout << "A battle begins" << std::endl;

  Battle arena;
  arena.weather_ = Weather::RAINING;
  arena.attacker_ = make_machop();
  arena.defender_ = make_machop();

  Example mv(std::string("double tap"), Element::FIGHTING);
  mv.Execute(arena);

  arena.SwapPositions();

  WithPrecondition mv2(
      std::make_unique<Example>("Fireball", Element::FIRE),
      std::make_unique<And<Battle, InRain, InSnow>>(InRain{}, InSnow{}));

  mv2.Execute(arena);

  std::cout << For{std::make_unique<Attacker>(),
                   std::make_unique<HasElement>(Element::ELECTRIC)}(arena)
            << std::endl;
}
