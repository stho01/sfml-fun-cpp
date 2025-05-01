//
// Created by stenm on 01.05.2025.
//

#pragma once

#include "ExplosionSpawner.h"
#include "Rocket.h"

class Fireworks;

class RocketUpdater {
  Fireworks& _game;
  ExplosionSpawner& _spawner;

public:
  RocketUpdater(Fireworks& game, ExplosionSpawner& spawner);
  void update(Rocket& rocket);

private:
  static void _updateAge(Rocket& rocket);
  void _updatePosition(Rocket& rocket) const;
  static void _updateTrail(Rocket& rocket);
  bool _intersectsWithEarth(const Rocket& rocket) const;
  void _handleEarthIntersection(Rocket& rocket) const;
  static void _useFuel(Rocket& rocket);

};