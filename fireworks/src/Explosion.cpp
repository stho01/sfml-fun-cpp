//
// Created by stenm on 01.05.2025.
//

#include "Explosion.h"

Explosion::Explosion(const int density) : _particles(std::vector<Particle>(density)) {
  for (int i = 0; i < density; i++) {
    Particle p;
    p.r = 255;
    p.g = 255;
    p.b = 255;
    p.totalLifetime = 100.0f;
    _particles.push_back(p);
  }
}

std::span<Particle> Explosion::particles() {
  return std::span(_particles);
}

void Explosion::setStrength(const float strength) {
  _strength = strength;
}

float Explosion::getStrength() const {
  return _strength;
}

void Explosion::setPosition(const sf::Vector2f& position) {
  _position = position;
}

sf::Vector2f Explosion::getPosition() const {
  return _position;
}

bool Explosion::isDone() const {
  for (const auto& particle : _particles) {
    if (!particle.isDead()) {
      return false;
    }
  }
  return true;
}