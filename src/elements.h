#pragma once

#include <array>
enum class Element {
  FIRE,
  WATER,
  GRASS,
  DRAGON,
  ELECTRIC,
  FIGHTING,
  GHOST,
  FAIRY,
  PSYCHIC
};

enum class Weather { RAIN, SNOW, FOG, NONE };

inline double same_type_boost(const Element pokemon_elem,
                              const Element move_elem) {

  if (pokemon_elem == move_elem) {
    return 1.5;
  }
  return 1.0;
}
