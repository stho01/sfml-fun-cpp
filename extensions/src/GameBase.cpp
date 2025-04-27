//
// Created by stho on 02.04.2025.
//

#include <SFML/Graphics.hpp>
#include "extensions/GameBase.h"
#include "extensions/Timer.h"
#include "extensions/Logger.h"

stho::GameBase::GameBase(sf::RenderWindow* window):
    m_window(window),
    m_fpsRenderer(static_cast<sf::RenderTarget*>(window))
{
    Logger::Instance().Start();
    Logger::Info("Game created");
}

stho::GameBase::~GameBase() {
    Logger::Info("GameBase destroyed");
    delete this->m_window;
}

sf::RenderWindow* stho::GameBase::getWindow() const {
    return m_window;
}

sf::Vector2u stho::GameBase::windowSize() const {
    return m_window->getSize();
}

unsigned int stho::GameBase::windowWidth() const {
    return m_window->getSize().x;
}

unsigned int stho::GameBase::windowHeight() const {
    return m_window->getSize().y;
}

sf::Vector2<float> stho::GameBase::windowCenter() const {
    return {
        static_cast<float>(windowWidth()) / 2.0f,
        static_cast<float>(windowHeight()) / 2.0f
    };
}

sf::FloatRect stho::GameBase::windowBounds() const {
    return {
        {0,0},
        {static_cast<float>(windowWidth()), static_cast<float>(windowHeight())}
    };
}

sf::Vector2i stho::GameBase::getMousePosition() const {
    return sf::Mouse::getPosition(*m_window);
}

void stho::GameBase::setClearColor(const sf::Color color) {
    m_clearColor = color;
}

sf::Color stho::GameBase::getClearColor() const {
    return m_clearColor;
}

void stho::GameBase::setKeyPressedHandler(std::function<void(sf::Keyboard::Key)> handler) {
    m_keyPressed = std::move(handler);
}

void stho::GameBase::setMouseButtonPressedHandler(std::function<void(sf::Mouse::Button)> handler) {
    m_mouseButtonPressed = std::move(handler);
}

void stho::GameBase::setWindowResizeHandler(std::function<void(sf::Vector2u)> handler) {
    m_resizeHandler = std::move(handler);
}

void stho::GameBase::start() {
    Logger::Info("Game started");

    Timer::update(); // reset timers after initialization

    while (this->m_window->isOpen()) {
        Timer::update();

        while (const std::optional event = this->m_window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                this->m_window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (this->m_keyPressed) {
                    this->m_keyPressed(keyPressed->code);
                }
            }
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (this->m_mouseButtonPressed) {
                    this->m_mouseButtonPressed(mouseButtonPressed->button);
                }
            }
            else if (const auto* resizeEvent = event->getIf<sf::Event::Resized>()) {
                if (this->m_resizeHandler) {
                    this->m_resizeHandler(resizeEvent->size);
                }
            }
        }

        this->m_window->clear(m_clearColor);
        update();
        render();
        this->m_fpsRenderer.render();
        this->m_window->display();
    }
}

void stho::GameBase::stop() const {
    this->m_window->close();
    Logger::Info("Game stopped");
}
