//
// Created by stenm on 30.04.2025.
//

#pragma once

#include <span>
#include <SFML/Graphics.hpp>
#include "Particle.h"

class Explosion {
  std::vector<std::shared_ptr<Particle>> _particles;
  float _strength{1.f};
  sf::Vector2f _position{0.f, 0.f};

public:
  explicit Explosion(int particleCount);
  ~Explosion();
  std::span<std::shared_ptr<Particle>> particles();
  void setStrength(float strength);
  float getStrength() const;
  void setPosition(const sf::Vector2f& position);
  sf::Vector2f getPosition() const;
  bool isDone() const;
};
