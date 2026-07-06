#include "battler.h"
#include "effects.h"
#include "elements.h"
#include "interface/inumber.h"
#include "interface/itarget.h"
#include "moves.h"
#include "pokemons.h"
#include <memory>

std::shared_ptr<Battler> make_machop() {
  auto leer = std::make_unique<Leer>(std::make_unique<LowerDefense>(
      std::make_unique<Defender>(),
      std::make_unique<XPercent>(
          std::make_unique<CurrentDefense>(std::make_unique<Defender>()),
          50.0)));
  std::vector<std::unique_ptr<IMove>> moves;
  moves.push_back(std::move(leer));
  return std::make_shared<Battler>(std::string{"Machop"}, 70.0, 50.0,
                                   std::vector<Element>{Element::FIGHTING},
                                   std::move(moves));
}
