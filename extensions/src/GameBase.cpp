//
// Created by stho on 02.04.2025.
//

#include <SFML/Graphics.hpp>
#include "extensions/GameBase.h"
#include "extensions/Timer.h"
#include "extensions/Logger.h"

stho::GameBase::GameBase(std::shared_ptr<sf::RenderWindow> window):
    m_window(std::move(window)),
    m_fpsRenderer(std::static_pointer_cast<sf::RenderTarget>(window))
{
    Logger::Instance().Info("Game created");
}

void stho::GameBase::start() {
    Logger::Instance().Info("Game started");
    while (this->m_window->isOpen())
    {
        Timer::instance().update();

        while (const std::optional event = this->m_window->pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                this->m_window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape && this->m_keyPressed != nullptr) {
                    this->m_keyPressed(keyPressed->code);
                }
            }
        }

        this->m_window->clear();

        update();
        render();
        this->m_fpsRenderer.render();

        this->m_window->display();
    }
}

void stho::GameBase::stop() const {
    this->m_window->close();
    Logger::Instance().Info("Game stopped");
}
