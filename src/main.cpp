#include "battle.h"
#include "battler.h"
#include "conditions.h"
#include "elements.h"
#include "imove.h"
#include "itarget.h"
#include "moves.h"
#include <iostream>
#include <memory>

int main() {
  std::cout << "A battle begins" << std::endl;

  Battler dragonite{"Dragonite", 100.0, {Element::DRAGON}};
  Battler pikatchu{"Pikatchu", 100.0, {Element::ELECTRIC}};
  Battle arena;
  arena.weather_ = Weather::RAINING;
  arena.attacker_ = dragonite;
  arena.defender_ = pikatchu;

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
