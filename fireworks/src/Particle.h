//
// Created by stenm on 30.04.2025.
//

#pragma once

struct Particle {
  std::uint8_t r{255};
  std::uint8_t g{255};
  std::uint8_t b{255};
  sf::Vector2f position{0.f, 0.f};
  sf::Vector2f velocity{0.f, 0.f};
  sf::Vector2f acceleration{0.f, 0.f};
  float age{0.f};
  float totalLifetime{0.f};
  float mass{0.f};
  bool isDead() const { return age >= totalLifetime; }

  void setPosition(const sf::Vector2f& position) {
    this->position = position;
  }
};