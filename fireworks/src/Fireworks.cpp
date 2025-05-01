//
// Created by stho on 10.04.2025.
//

#include "Fireworks.h"
#include <execution>
#include <iostream>
#include "ExplosionUpdater.h"
#include "Rocket.h"

Fireworks::Fireworks(sf::RenderWindow* window)
    : GameBase(window)
{
    setClearColor(sf::Color::Black);
    window->setFramerateLimit(250);
}

Fireworks::~Fireworks() {
    _explosions.clear();
    _earthTexture.reset();
    _earthSprite.reset();
    _explosionUpdater.reset();
}

void Fireworks::initialize() {
    Logger::Info("Initialized sprites");

    _particleRenderer = std::make_unique<ParticleRenderer>(*getWindow());
    _explosionRenderer = std::make_unique<ExplosionRenderer>(*_particleRenderer);
    _explosionUpdater = std::make_unique<ExplosionUpdater>(*this);
    _rocketRenderer = std::make_unique<RocketRenderer>(*getWindow(), *_particleRenderer);
    _rocketSpawner = std::make_unique<RocketSpawner>(*this);
    _explosionSpawner = std::make_unique<ExplosionSpawner>();
    _rocketUpdater = std::make_unique<RocketUpdater>(*this, *_explosionSpawner);

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
            // auto explosion = _explosionSpawner->spawn(static_cast<sf::Vector2f>(getMousePosition()));
            // _explosions.insert(std::move(explosion));
            _rockets.insert(_rocketSpawner->spawnOnSurface());
        }
    });
}

void Fireworks::update() {
    _rocketSpawner->update();

    for (auto& rocket : _rockets) {
        _rocketUpdater->update(*rocket);
    }
    for (auto& explosion : _explosions) {
        _explosionUpdater->update(*explosion);
    }

    erase_if(_explosions, [](const auto& explosion) { return explosion->isDone(); });
    erase_if(_rockets, [](const auto& rocket) { return rocket->isDead(); });
}

void Fireworks::render() {
    this->m_window->draw(*_earthSprite);
    for (auto& explosion : _explosions) {
        _explosionRenderer->render(*explosion);
    }
    for (auto& rocket : _rockets) {
        _rocketRenderer->render(*rocket);
    }
}

void Fireworks::unload() {
    std::cout << "Game unloaded!" << std::endl;
}

sf::Vector2f Fireworks::getEarthPosition() const {
    return _earth.getPosition();
}

float Fireworks::getEarthRadius() const {
    return _earth.getRadius();
}

void Fireworks::addRocket(std::shared_ptr<Rocket> rocket) {
    _rockets.insert(std::move(rocket));
}

void Fireworks::addExplosion(std::shared_ptr<Explosion> explosion) {
    _explosions.insert(std::move(explosion));
}


