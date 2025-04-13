#pragma once

#include <SFML/Graphics.hpp>

namespace stho {

    struct WindowSize {
        unsigned int width;
        unsigned int height;
    } constexpr DEFAULT_WINDOW_SIZE {1920, 1080};

    class WindowFactory {
    public:
        static sf::RenderWindow* CreateDefault(const WindowSize size = DEFAULT_WINDOW_SIZE)
        {
            const sf::VideoMode videoMode({ size.width, size.height });
            sf::ContextSettings settings;
            settings.antiAliasingLevel = 8;

            return new sf::RenderWindow(
                videoMode,
                "Game",
                sf::State::Windowed,
                settings);
        }
    };

}