//
// Created by stho on 02.04.2025.
//

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>
#include "extensions/GameFpsRenderer.h"

namespace stho {
    class GameBase {
    public:
        explicit GameBase(sf::RenderWindow* window);
        virtual ~GameBase();

        void start();
        void stop() const;

        [[nodiscard]] sf::RenderWindow* getWindow() const;
        [[nodiscard]] sf::Vector2u windowSize() const;
        [[nodiscard]] unsigned int windowWidth() const;
        [[nodiscard]] unsigned int windowHeight() const;
        [[nodiscard]] sf::Vector2<float> windowCenter() const;
        [[nodiscard]] sf::FloatRect windowBounds() const;
        [[nodiscard]] sf::Vector2i getMousePosition() const;
        void setClearColor(sf::Color color);
        [[nodiscard]] sf::Color getClearColor() const;
        void setKeyPressedHandler(std::function<void(sf::Keyboard::Key)> handler);
        void setMouseButtonPressedHandler(std::function<void(sf::Mouse::Button)> handler);
        void setWindowResizeHandler(std::function<void(sf::Vector2u)> handler);

    protected:
        sf::RenderWindow* m_window{ nullptr };

        virtual void initialize() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void unload() = 0;

    private:
        sf::Color m_clearColor{ sf::Color::Black };
        GameFpsRenderer m_fpsRenderer;
        std::function<void(sf::Keyboard::Key)> m_keyPressed;
        std::function<void(sf::Mouse::Button)> m_mouseButtonPressed;
        std::function<void(sf::Vector2u)> m_resizeHandler;

    };
}

