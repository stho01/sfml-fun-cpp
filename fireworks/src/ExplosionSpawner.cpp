//
// Created by stenm on 01.05.2025.
//

#include "ExplosionSpawner.h"
#include <numbers>

ExplosionSpawner::ExplosionSpawner()
  : _density({150.f,250.f})
  , _lifetime({1000.f, 1500.f})
  , _strength({40.f, 80.f})
{
  _colors.push_back(sf::Color::Red);
  _colors.push_back(sf::Color::Green);
  _colors.push_back(sf::Color::Blue);
}


std::shared_ptr<Explosion> ExplosionSpawner::spawn(const sf::Vector2f pos) {
  const auto density = stho::RandomNumber::nextFloat(_density);
  const auto explosion = stho::ObjectPool<Explosion>::shared()->acquire(density);
  explosion->setStrength(stho::RandomNumber::nextFloat(_strength));
  explosion->setPosition(pos);

  const auto lifeTime = stho::RandomNumber::nextFloat(_lifetime);

  const auto particles = explosion->particles();
  for (auto i = 0; i < particles.size(); i++) {
    const auto& particle = particles[i];
    const auto angleOfVelocity = i / std::numbers::pi * 2;
    const auto direction = sf::Vector2f(
        static_cast<float>(cos(angleOfVelocity)),
        static_cast<float>(sin(angleOfVelocity))
    );

    const auto variance = stho::RandomNumber::nextFloat(-explosion->getStrength() * 0.9f, 0.f);
    const auto velocity = direction * (explosion->getStrength() + variance);
    const auto color = _colors[stho::RandomNumber::next(0, _colors.size()-1)];

    particle->r = color.r;
    particle->g = color.g;
    particle->b = color.b;
    particle->totalLifetime = lifeTime;
    particle->velocity = velocity;
    particle->position = explosion->getPosition();
    particle->mass = stho::RandomNumber::nextFloat(.75f, 1.25f);
  }

  return explosion;
}