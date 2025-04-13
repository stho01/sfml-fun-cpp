//
// Created by stho on 11.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>

namespace stho {
    class Fonts {
    public:
        static std::unique_ptr<sf::Font> createRoboto() {
            auto font = std::make_unique<sf::Font>("assets/extensions/Roboto-Regular.ttf");
            return font;
        }

        // Returnerer en referanse til en delt instans
        static const sf::Font& Roboto() {
            static sf::Font font("assets/extensions/Roboto-Regular.ttf");
            return font;
        }
    };
}