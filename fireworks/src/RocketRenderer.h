//
// Created by stenm on 01.05.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "ParticleRenderer.h"
#include "Rocket.h"

class RocketRenderer {
  sf::CircleShape _rocketShape;
  sf::RenderTarget& _target;
  ParticleRenderer& _particleRenderer;

public:
  RocketRenderer(sf::RenderTarget& target, ParticleRenderer& particleRenderer);
  void render(const Rocket& rocket);
};
