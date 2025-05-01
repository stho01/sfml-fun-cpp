//
// Created by stenm on 01.05.2025.
//


#pragma once

#include <SFML/Graphics.hpp>

#include "Explosion.h"
#include "extensions/extensions.h"

class ExplosionSpawner {
  stho::Rangef _density;
  stho::Rangef _lifetime;
  stho::Rangef _strength;
  std::vector<sf::Color> _colors;

public:
  ExplosionSpawner();
  std::shared_ptr<Explosion> spawn(sf::Vector2f pos);

};
