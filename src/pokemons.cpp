#include "battler.h"
#include "elements.h"
#include "moves.h"
#include "pokemons.h"
#include <memory>

std::shared_ptr<Battler> make_machop() {
  auto leer = std::make_unique<Leer>();

  std::vector<std::unique_ptr<IMove>> moves;
  moves.push_back(std::move(leer));
  return std::make_shared<Battler>(std::string{"Machop"}, 70.0, 50.0,
                                   std::vector<Element>{Element::FIGHTING},
                                   std::move(moves));
}
