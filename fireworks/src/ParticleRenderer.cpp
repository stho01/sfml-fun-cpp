//
// Created by stenm on 30.04.2025.
//

#include "ParticleRenderer.h"
#include <cmath>

ParticleRenderer::ParticleRenderer(sf::RenderTarget& renderTarget)
  : _particle(1)
  , _fadeMode(LINEAR)
  , _renderTarget(renderTarget) {
  _particle.setOrigin({1.f, 1.f});
}

ParticleRenderer::~ParticleRenderer() = default;

void ParticleRenderer::render(const Particle& particle) {
  if (particle.isDead()) {
    return;
  }

  double alpha;
  if (_fadeMode == LINEAR)
  {
    alpha = 255.0 - ((particle.age / particle.totalLifetime) * 255.0);
  }
  else
  {
    const auto t = (particle.age / particle.totalLifetime);
    alpha = 255.0 - (pow(2.0, t) * 255.0);
  }

  _particle.setPosition(particle.position);
  _particle.setFillColor(sf::Color(
      particle.r,
      particle.g,
      particle.b,
      static_cast<std::uint8_t>(alpha)));

  _renderTarget.draw(_particle);
}

