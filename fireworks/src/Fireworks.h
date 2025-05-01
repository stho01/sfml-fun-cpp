//
// Created by stho on 10.04.2025.
//

#pragma once

#include <unordered_set>
#include <extensions/extensions.h>
#include <SFML/Graphics.hpp>
#include "ExplosionRenderer.h"
#include "ExplosionSpawner.h"
#include "ExplosionUpdater.h"
#include "ParticleRenderer.h"
#include "RocketRenderer.h"
#include "RocketSpawner.h"
#include "RocketUpdater.h"

class Fireworks final : public stho::GameBase {
    std::unique_ptr<sf::Texture> _earthTexture{nullptr};
    std::unique_ptr<sf::Sprite> _earthSprite{nullptr};
    std::unique_ptr<ParticleRenderer> _particleRenderer{nullptr};
    std::unique_ptr<ExplosionRenderer> _explosionRenderer{nullptr};
    std::unique_ptr<ExplosionSpawner> _explosionSpawner{nullptr};
    std::unique_ptr<RocketRenderer> _rocketRenderer{nullptr};
    std::unique_ptr<ExplosionUpdater> _explosionUpdater{nullptr};
    std::unique_ptr<RocketSpawner> _rocketSpawner{nullptr};
    std::unique_ptr<RocketUpdater> _rocketUpdater{nullptr};
    sf::CircleShape _earth{120,60};
    std::unordered_set<std::shared_ptr<Explosion>> _explosions{};
    std::unordered_set<std::shared_ptr<Rocket>> _rockets{};

public:
    const float GRAVITY{-9.81f*.75f};

    explicit Fireworks(sf::RenderWindow* window);
    ~Fireworks() override;
    void initialize() override;
    void update() override;
    void render() override;
    void unload() override;

    sf::Vector2f getEarthPosition() const;
    float getEarthRadius() const;

    void addRocket(std::shared_ptr<Rocket> rocket);
    void addExplosion(std::shared_ptr<Explosion> explosion);
};
