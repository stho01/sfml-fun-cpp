//
// Created by stenm on 30.04.2025.
//


#pragma once

#include "Explosion.h"
#include "ParticleRenderer.h"

class ExplosionRenderer {
  ParticleRenderer& _particleRenderer;

public:
  ExplosionRenderer(ParticleRenderer& particleRenderer);
  ~ExplosionRenderer();
  void render(Explosion& explosion) const;
};
