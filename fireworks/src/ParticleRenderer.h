//
// Created by stenm on 30.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Particle.h"

enum ParticleFade {
  LINEAR,
  EXPONENTIAL
};


class ParticleRenderer {
  sf::CircleShape _particle;
  ParticleFade _fadeMode;
  sf::RenderTarget& _renderTarget;

public:
  explicit ParticleRenderer(sf::RenderTarget& renderTarget);
  ~ParticleRenderer();
  void render(const Particle& particle);
};