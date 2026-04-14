#include "battle.h"
#include "battler.h"
#include "elements.h"
#include "moves.h"
#include <iostream>

int main() {
  std::cout << "A battle begins" << std::endl;

  Battler b1{"b1", 100.0, {Element::DRAGON}};
  Battle bat;

  Example mv;
  mv.Execute(bat);
}
