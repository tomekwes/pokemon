#include "battler.h"
#include "elements.h"
#include "pokemons.h"
#include <memory>

std::shared_ptr<Battler> make_machop() {
  return std::make_shared<Battler>(std::string{"Machop"}, 70.0,
                                   std::vector<Element>{Element::FIGHTING},
                                   std::vector<std::unique_ptr<Move>>{});
}
