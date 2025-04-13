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
        explicit GameBase(std::shared_ptr<sf::RenderWindow> window);
        virtual ~GameBase() = default;

        void start();
        void stop() const;

        [[nodiscard]] std::shared_ptr<sf::RenderWindow> getWindow() const { return m_window; }
        [[nodiscard]] sf::Vector2u windowSize() const { return m_window->getSize(); }
        [[nodiscard]] int windowWidth() const { return m_window->getSize().x; }
        [[nodiscard]] int windowHeight() const { return m_window->getSize().y; }
        [[nodiscard]] sf::Vector2<float> windowCenter() const { return sf::Vector2f(windowWidth() / 2, windowHeight() / 2); }
        [[nodiscard]] sf::FloatRect windowBounds() const {
            return sf::FloatRect({0,0}, {static_cast<float>(windowWidth()), static_cast<float>(windowHeight())});
        }
        [[nodiscard]] sf::Vector2i getMousePosition() const {
            return sf::Mouse::getPosition(*m_window);
        }

        void setClearColor(const sf::Color color) {
            m_clearColor = color;
        }

        [[nodiscard]] sf::Color getClearColor() const {
            return m_clearColor;
        }

        void setKeyPressedHandler(std::function<void(sf::Keyboard::Key)> handler) {
            m_keyPressed = std::move(handler);
        }

    protected:
        virtual void initialize() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void unload() = 0;

    protected:
        std::shared_ptr<sf::RenderWindow> m_window{ nullptr };

    private:

        sf::Color m_clearColor{ sf::Color::Black };
        GameFpsRenderer m_fpsRenderer;
        std::function<void(sf::Keyboard::Key)> m_keyPressed;

    };
}

