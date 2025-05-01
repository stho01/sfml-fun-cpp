//
// Created by stenm on 01.05.2025.
//

#include "Explosion.h"
#include "extensions/ObjectPool.h"

Explosion::Explosion(const int particleCount)
{
  for (auto i = 0; i < particleCount; i++) {
    auto particle = stho::ObjectPool<Particle>::shared()->acquire();
    _particles.push_back(std::move(particle));
  }
}

Explosion::~Explosion() {
  _particles.clear();
}

std::span<std::shared_ptr<Particle>> Explosion::particles() {
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
    if (!particle->isDead()) {
      return false;
    }
  }
  return true;
}