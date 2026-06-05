#include "battle.h"
#include "battler.h"
#include "conditions.h"
#include "elements.h"
#include "imove.h"
#include "moves.h"
#include <iostream>
#include <memory>

int main() {
  std::cout << "A battle begins" << std::endl;

  Battler b1{"b1", 100.0, {Element::DRAGON}};
  Battle bat;
  bat.weather_ = Weather::RAINING;

  Example mv(std::string("double tap"), Element::FIGHTING);
  mv.Execute(bat);

  WithPrecondition mv2(std::make_unique<Example>("Fireball", Element::FIRE),
                       std::make_unique<OnlyInRain>());
  mv2.Execute(bat);
}
