//
// Created by stenm on 01.05.2025.
//

#include "RocketRenderer.h"

#include "extensions/Mathf.h"


RocketRenderer::RocketRenderer(sf::RenderTarget& target, ParticleRenderer& particleRenderer)
  : _target(target)
  , _particleRenderer(particleRenderer)
{
  _rocketShape.setRadius(1.f);
  _rocketShape.setPointCount(3.f);
  _rocketShape.setFillColor(sf::Color::White);
  _rocketShape.setScale({.5f, 1.f});
}

void RocketRenderer::render(const Rocket& rocket) {
  const auto radius = rocket.mass * .25f;
  _rocketShape.setPosition(rocket.position);
  _rocketShape.setRotation(stho::Mathf::ToPolarCoordinates(rocket.velocity).getAngle());
  _rocketShape.setRadius(radius);
  _rocketShape.setOrigin({radius, radius});
  _target.draw(_rocketShape);
}


