//
// Created by stho on 10.04.2025.
//

#pragma once

#include <extensions/extensions.h>
#include <SFML/Graphics.hpp>

#include "ExplosionRenderer.h"
#include "ParticleRenderer.h"

class Fireworks final : public stho::GameBase {

    std::unique_ptr<sf::Texture> _earthTexture;
    std::unique_ptr<sf::Sprite> _earthSprite;
    ParticleRenderer _particleRenderer;
    ExplosionRenderer _explosionRenderer;
    sf::CircleShape _earth{120,60};

public:
    explicit Fireworks(sf::RenderWindow* window);
    void initialize() override;
    void update() override;
    void render() override;
    void unload() override;
};
