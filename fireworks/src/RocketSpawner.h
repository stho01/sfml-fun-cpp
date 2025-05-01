//
// Created by stenm on 01.05.2025.
//

#pragma once

#include <extensions/extensions.h>
#include "Rocket.h"

class Fireworks;

class RocketSpawner {
  Fireworks& _game;
  stho::Rangef _strength{68.f, 72.f};
  stho::Rangef _mass{10.f, 15.f};
  stho::Rangef _fuel{45.f, 55.f};
  stho::Rangef _lifetime{500.f, 1500.f};
  stho::Rangei _rocketSpawnCount{1,3};
  stho::Rangef _rocketSpawnTime{50.f, 300.f};
  float _currentSpawnTimeAccumulator = 0.f;
  float _currentSpawnTimer = 0.f;

public:
  explicit RocketSpawner(Fireworks& game);

  void update();
  std::shared_ptr<Rocket> spawnOnSurface() const;
};
