//
// Created by stho on 03.04.2025.
//
#pragma once

#include <SFML/Graphics.hpp>

namespace stho {
    struct WindowSize {
        unsigned int width;
        unsigned int height;
    };

    class WindowFactory {

    public:
        static constexpr unsigned int DEFAULT_SCREEN_WIDTH { 1920 };
        static constexpr unsigned int DEFAULT_SCREEN_HEIGHT { 1080 };
        static const WindowSize DEFAULT_WINDOW_SIZE;

        static std::shared_ptr<sf::RenderWindow> CreateDefault(const WindowSize size = DEFAULT_WINDOW_SIZE)
        {
            const sf::VideoMode videoMode({ size.width, size.height });
            sf::ContextSettings settings;
            settings.antiAliasingLevel = 8;

            return std::make_shared<sf::RenderWindow>(
                videoMode,
                "Game",
                sf::State::Windowed,
                settings);
        }
    };
}