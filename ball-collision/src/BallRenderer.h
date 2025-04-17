//
// Created by stenm on 16.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <extensions/extensions.h>
#include "Ball.h"

class BallRenderer {
    public:
        explicit BallRenderer(sf::RenderTarget* renderTarget);
        void render(const Ball* ball);

    private:
        sf::RenderTarget* _renderTarget;
        sf::CircleShape _shape{};
        stho::LineShape _line{0,0,0,0};
};
