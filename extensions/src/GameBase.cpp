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
    Logger::Info("Game created");
}

stho::GameBase::~GameBase() {
    Logger::Info("Game destroyed");
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


static long long frameCounter = 0;
static long long totalTimeU = 0;
static double avgU = 0;
static double maxU = std::numeric_limits<int>::min();
static double minU = std::numeric_limits<int>::max();

static long long totalTimeR = 0;
static double avgR = 0;
static double maxR = std::numeric_limits<int>::min();
static double minR = std::numeric_limits<int>::max();

static std::chrono::milliseconds printCounter = std::chrono::milliseconds(0);

void stho::GameBase::start() {
    Logger::Info("Game started");

    Timer::update(); // reset timers after initialization

    while (this->m_window->isOpen())
    {
        Timer::update();

        while (const std::optional event = this->m_window->pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                this->m_window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (this->m_keyPressed) {
                    this->m_keyPressed(keyPressed->code);
                }
            }
        }

        this->m_window->clear();

        frameCounter++;

        auto now = std::chrono::high_resolution_clock::now();
        update();
        auto timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now).count();
        totalTimeU += timeTaken;
        avgU = static_cast<double>(totalTimeU) / static_cast<double>(frameCounter);
        minU = std::min(minU, static_cast<double>(timeTaken));
        maxU = std::max(maxU, static_cast<double>(timeTaken));

        now = std::chrono::high_resolution_clock::now();
        render();
        timeTaken = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - now).count();
        totalTimeR += timeTaken;
        avgR = static_cast<double>(totalTimeR) / static_cast<double>(frameCounter);
        minR = std::min(minU, static_cast<double>(timeTaken));
        maxR = std::max(maxU, static_cast<double>(timeTaken));

        printCounter += Timer::DeltaTime;
        if (printCounter >= std::chrono::seconds(1)) {

            const auto& a = std::format("Avg U: {}, Min U: {}, Max U: {}, Avg R: {}, Min R: {}, Max R: {}",
                avgU,
                minU,
                maxU,
                avgR,
                minR,
                maxR);

            Logger::Info(a);

            printCounter = std::chrono::milliseconds(0);
        }

        this->m_fpsRenderer.render();
        this->m_window->display();
    }
}

void stho::GameBase::stop() const {
    this->m_window->close();
    Logger::Info("Game stopped");
}
