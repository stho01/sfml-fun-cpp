//
// Created by stho on 10.04.2025.
//

#include "Fireworks.h"

#include <execution>
#include <iostream>

Fireworks::Fireworks(sf::RenderWindow* window)
    : GameBase(window)
    , _particleRenderer(*window)
    , _explosionRenderer(_particleRenderer)
{
    setClearColor(sf::Color::Black);
}

void Fireworks::initialize() {
    Logger::Info("Initialized sprites");

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
}

void Fireworks::update() {

}

void Fireworks::render() {
    this->m_window->draw(*_earthSprite);

    Explosion explosion(10);
    explosion.setPosition({100.f, 100.f});
    const auto pos = explosion.getPosition();

    for (auto& particle : explosion.particles()) {
        particle.position.x = pos.x + 100.0f + stho::RandomNumber::nextFloat(-10.f, 10.f);
        particle.position.y = pos.y + 100.0f + stho::RandomNumber::nextFloat(-10.f, 10.f);
        auto i = 0;
    }

    _explosionRenderer.render(explosion);
}

void Fireworks::unload() {
    std::cout << "Game unloaded!" << std::endl;
}