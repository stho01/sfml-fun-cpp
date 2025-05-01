//
// Created by stenm on 01.05.2025.
//

#pragma once

#include <SFML/Graphics.hpp>

struct Rocket {
  sf::Vector2f position{};
  sf::Vector2f velocity{};
  sf::Vector2f acceleration{};
  sf::Vector2f direction{};
  float fuel{1.f};
  float mass{1.f};
  float strength{1.f};
  float age{};
  float totalLifetime{};
  bool done{false};

  bool hasFuel() const { return fuel > 0; }
  bool isDead() const { return done || age >= totalLifetime; }
};