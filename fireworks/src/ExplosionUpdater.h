//
// Created by stenm on 01.05.2025.
//

#pragma once
#include "Explosion.h"

class Fireworks;

class ExplosionUpdater {
  Fireworks& _fireworks;
  float _airResistance;

public:
  explicit ExplosionUpdater(Fireworks& fireworks);
  ~ExplosionUpdater();

  void setAirResistance(float airResistance);
  float getAirResistance() const;

  void update(Explosion& explosion) const;
};