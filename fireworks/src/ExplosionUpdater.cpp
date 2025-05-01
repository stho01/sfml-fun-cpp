//
// Created by stenm on 01.05.2025.
//

#include "ExplosionUpdater.h"

#include <execution>
#include <extensions/extensions.h>
#include "Fireworks.h"

ExplosionUpdater::ExplosionUpdater(Fireworks& fireworks) : _fireworks(fireworks), _airResistance(0.01f) {
}

ExplosionUpdater::~ExplosionUpdater() = default;

void ExplosionUpdater::setAirResistance(const float airResistance) {
  _airResistance = airResistance;
}

float ExplosionUpdater::getAirResistance() const {
  return _airResistance;
}

void ExplosionUpdater::update(Explosion& explosion) const {
  for (const auto& particle : explosion.particles()) {

    particle->age += stho::Timer::deltaTimeSeconds() * 1000.f;

    const auto distance = particle->position - _fireworks.getEarthPosition();
    if (distance.lengthSquared() == 0.f) {
      continue;
    }

    const auto gravityForce = distance.normalized() * _fireworks.GRAVITY * _airResistance;

    sf::Vector2f direction{0.f, 0.f};
    if (particle->velocity.lengthSquared() != 0.f) {
      direction = particle->velocity.normalized();
    }
    const auto airResistanceDecay = -(direction * 0.1f);

    sf::Vector2f acceleration = {0.f, 0.f};
    acceleration += gravityForce / particle->mass;
    acceleration += airResistanceDecay / particle->mass;

    // particle->acceleration += (gravityForce + airResistanceDecay) / particle->mass * stho::Timer::deltaTimeSeconds();
    particle->velocity += acceleration;
    particle->position += particle->velocity * stho::Timer::deltaTimeSeconds();
  }
}