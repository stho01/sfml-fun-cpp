﻿//
// Created by stenm on 01.05.2025.
//

#include "RocketUpdater.h"
#include <extensions/extensions.h>
#include "Fireworks.h"

RocketUpdater::RocketUpdater(Fireworks& game, ExplosionSpawner& spawner)
  : _game(game), _spawner(spawner) {}

void RocketUpdater::update(Rocket& rocket) {
  _updateAge(rocket);

  if (rocket.isDead()) {
    _game.addExplosion(_spawner.spawn(rocket.position, rocket.velocity));
    return;
  }

  _updatePosition(rocket);
  _updateTrail(rocket);

  if (_intersectsWithEarth(rocket))
    _handleEarthIntersection(rocket);

  _useFuel(rocket);
}

void RocketUpdater::_updateAge(Rocket& rocket) {
  rocket.age += stho::Timer::deltaTimeMilliseconds();
}

void RocketUpdater::_updatePosition(Rocket& rocket) const {
  const auto gravity = (rocket.position - _game.getEarthPosition()).normalized() * _game.GRAVITY;

  auto force = stho::Vector2f::ZERO;
  if (rocket.hasFuel())
    force = rocket.direction.normalized() * rocket.strength;

  // Logger::Info("Rocket dir {}", stho::Vector2f::asString(rocket.direction));

  sf::Vector2f acceleration = stho::Vector2f::ZERO;
  acceleration += gravity / rocket.mass;
  acceleration += force / rocket.mass;

  rocket.velocity += acceleration;
  rocket.position += rocket.velocity * stho::Timer::deltaTimeSeconds();
}

void RocketUpdater::_updateTrail(Rocket& rocket) {
  for (const auto& particle : rocket.trail) {
    particle->age += stho::Timer::deltaTimeMilliseconds();
  }
  std::erase_if(rocket.trail, [](const auto& particle) { return particle->isDead(); });
  rocket.trailTimeSinceLastEmit += stho::Timer::deltaTimeMilliseconds();

  if (rocket.hasFuel() && rocket.trailTimeSinceLastEmit >= rocket.trailEmitTime) {
    rocket.trailTimeSinceLastEmit = 0.f;
    const auto particle = stho::ObjectPool<Particle>::shared()->acquire();
    particle->position = rocket.position;
    particle->totalLifetime = 200.0f;
    particle->mass = 1.f;
    particle->r = 255.f;
    particle->g = 165.f;
    particle->b = 74.f;
    rocket.trail.push_back(particle);
  }
}

bool RocketUpdater::_intersectsWithEarth(const Rocket& rocket) const {
  return (rocket.position - _game.getEarthPosition()).lengthSquared() <= _game.getEarthRadius() * _game.getEarthRadius();
}

void RocketUpdater::_handleEarthIntersection(Rocket& rocket) const {
  if (const auto dotProduct = rocket.velocity.dot(_game.getEarthPosition()); dotProduct > 0) {
    rocket.acceleration = stho::Vector2f::ZERO;
  }

  const auto intersectionPoint = _game.getEarthPosition() + (rocket.position - _game.getEarthPosition()).normalized() * _game.getEarthRadius();
  rocket.position = intersectionPoint;
  rocket.velocity = stho::Vector2f::ZERO;
  rocket.done = true;
}

void RocketUpdater::_useFuel(Rocket& rocket) {
  const auto decline = 200.f * stho::Timer::deltaTimeSeconds();
  rocket.fuel = std::max(0.f, rocket.fuel - decline);
}
