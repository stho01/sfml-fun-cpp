//
// Created by stenm on 01.05.2025.
//

#include "RocketSpawner.h"
#include <numbers>
#include "Fireworks.h"

RocketSpawner::RocketSpawner(Fireworks& game)
  : _game(game) { }

void RocketSpawner::update() {
  _currentSpawnTimeAccumulator += stho::Timer::deltaTimeMilliseconds();
  if (_currentSpawnTimeAccumulator >= _currentSpawnTimer) {
    _currentSpawnTimer = stho::RandomNumber::nextFloat(_rocketSpawnTime);
    const auto spawnCount = stho::RandomNumber::next(_rocketSpawnCount);

    for (int i = 0; i < spawnCount; i++) {
      _game.addRocket(spawnOnSurface());
    }

    _currentSpawnTimeAccumulator = 0;
  }
}

std::shared_ptr<Rocket> RocketSpawner::spawnOnSurface() const {
  const auto angle = stho::RandomNumber::angleDegrees();
  const auto dir = stho::Mathf::getDirectionFromDegrees(angle);
  const auto position = _game.getEarthPosition() + dir * (_game.getEarthRadius() + 10);

  const auto randomAngle =
      stho::Mathf::degreeToRadian(angle)
    + stho::RandomNumber::nextFloat(-1.f, 1.f)
    * std::numbers::pi
    * .13f;

  // Just to make it more interesting.
  const sf::Vector2f randomDir = {
      static_cast<float>(cos(randomAngle)),
      static_cast<float>(sin(randomAngle))
  };

  const auto rocket = stho::ObjectPool<Rocket>::shared()->acquire();
  rocket->strength = stho::RandomNumber::nextFloat(_strength);
  rocket->mass = stho::RandomNumber::nextFloat(_mass);
  rocket->fuel = stho::RandomNumber::nextFloat(_fuel);
  rocket->totalLifetime = stho::RandomNumber::nextFloat(_lifetime);
  rocket->position = position;
  rocket->direction = randomDir;

  // Logger::Info("Rocket spawned");
  return rocket;
}
