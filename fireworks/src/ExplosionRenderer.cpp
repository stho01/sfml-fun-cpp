//
// Created by stenm on 30.04.2025.
//

#include "ExplosionRenderer.h"

ExplosionRenderer::ExplosionRenderer(ParticleRenderer& particleRenderer)
  : _particleRenderer(particleRenderer) {
}

ExplosionRenderer::~ExplosionRenderer() = default;

void ExplosionRenderer::render(Explosion& explosion) const {
  for (const auto& particle : explosion.particles()) {
    _particleRenderer.render(*particle);
  }
}
