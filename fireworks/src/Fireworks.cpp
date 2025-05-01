//
// Created by stho on 10.04.2025.
//

#include "Fireworks.h"
#include <cmath>
#include <execution>
#include <iostream>
#include <numbers>
#include "ExplosionUpdater.h"

Fireworks::Fireworks(sf::RenderWindow* window)
    : GameBase(window)
    , _particleRenderer(*window)
    , _explosionRenderer(_particleRenderer)
{
    setClearColor(sf::Color::Black);
    window->setFramerateLimit(450);
}

void Fireworks::initialize() {
    Logger::Info("Initialized sprites");

    _explosionUpdater = std::make_unique<ExplosionUpdater>(*this);

    _earth.setOrigin({
        _earth.getRadius(),
        _earth.getRadius()
    });
    _earth.setPosition({
        static_cast<float>(windowWidth()) / 2.f,
        static_cast<float>(windowHeight()) / 2.f
    });
    _earth.setFillColor(sf::Color::Transparent);
    _earth.setOutlineColor(sf::Color::Green);
    _earth.setOutlineThickness(-1);

    _earthTexture = std::make_unique<sf::Texture>("assets/earth.png");
    _earthSprite = std::make_unique<sf::Sprite>(*_earthTexture);
    _earthSprite->setScale({
        _earth.getRadius() / static_cast<float>(_earthTexture->getSize().x) * 2.f,
        _earth.getRadius() / static_cast<float>(_earthTexture->getSize().y) * 2.f
    });
    _earthSprite->setPosition(_earth.getPosition() - _earth.getOrigin());

    this->setMouseButtonPressedHandler([this](const sf::Mouse::Button button) {
        if (button == sf::Mouse::Button::Left) {
            Explosion explosion(150);
            explosion.setStrength(stho::RandomNumber::nextFloat(90.f, 110.f));
            explosion.setPosition(static_cast<sf::Vector2f>(getMousePosition()));

            const auto particles = explosion.particles();
            for (auto i = 0; i < particles.size(); i++) {
                auto& particle = particles[i];
                const auto angleOfVelocity = i / std::numbers::pi * 2;
                const auto direction = sf::Vector2f(
                    static_cast<float>(cos(angleOfVelocity)),
                    static_cast<float>(sin(angleOfVelocity))
                );

                const auto variance = stho::RandomNumber::nextFloat(-explosion.getStrength()*0.9f, 0.f);
                const auto velocity = direction * (explosion.getStrength() + variance);

                particle.totalLifetime = 1250.f;
                particle.velocity = velocity;
                particle.position = explosion.getPosition();
                particle.mass = stho::RandomNumber::nextFloat(.75f, 1.25f);
            }

            _explosions.push_back(explosion);
        }
    });
}

void Fireworks::update() {
    for (auto& explosion : _explosions) {
        _explosionUpdater->update(explosion);
    }
}

void Fireworks::render() {
    this->m_window->draw(*_earthSprite);
    for (auto& explosion : _explosions) {
        _explosionRenderer.render(explosion);
    }
}

void Fireworks::unload() {
    std::cout << "Game unloaded!" << std::endl;
}

sf::Vector2f Fireworks::getEarthPosition() const {
    return _earth.getPosition();
}