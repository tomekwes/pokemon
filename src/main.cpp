#include "battler.h"
#include "elements.h"
#include <iostream>

int main() {
  std::cout << "A battle begins" << std::endl;

  Battler b1{"b1", 100.0, {Element::DRAGON}};
}
