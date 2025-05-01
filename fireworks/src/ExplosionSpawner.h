//
// Created by stenm on 01.05.2025.
//


#pragma once

#include <SFML/Graphics.hpp>
#include "Explosion.h"
#include "extensions/extensions.h"

class ExplosionSpawner {
  stho::Rangef _density{150.f,250.f};
  stho::Rangef _lifetime{1000.f, 2000.f};
  stho::Rangef _strength{100.f, 140.f};
  std::vector<sf::Color> _colors;

public:
  ExplosionSpawner();
  std::shared_ptr<Explosion> spawn(sf::Vector2f pos, sf::Vector2f relativeSpeed);

};
