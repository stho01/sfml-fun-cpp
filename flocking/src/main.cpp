#include <SFML/Graphics.hpp>
#include <extensions/extensions.h>
#include "FlockingBehaviour.h"
#include <cmath>

int main() {
    const auto window = stho::WindowFactory::CreateDefault();
    FlockingBehaviour game(window);
    game.initialize();

    game.setKeyPressedHandler([&game](const sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Key::C)
            game.toggleShowCollider();
        if (key == sf::Keyboard::Key::N)
            game.toggleShowNeighborhood();
        if (key == sf::Keyboard::Key::Num1)
            game.selectFirst();
        if (key == sf::Keyboard::Key::Tab)
            game.selectNext();
        if (key == sf::Keyboard::Key::Up)
            game.setAgentSpeed(std::min(game.getAgentSpeed() + 4.0f, 150.0f));
        if (key == sf::Keyboard::Key::Down)
            game.setAgentSpeed(std::min(game.getAgentSpeed() - 4.0f, 0.0f));
        if (key == sf::Keyboard::Key::R)
            game.reset();
        if (key == sf::Keyboard::Key::Q)
            game.stop();
        if (key == sf::Keyboard::Key::T)
            game.toggleQuadTreeRendering();
        if (key == sf::Keyboard::Key::Y)
            game.toggleQuadTree();
        // if (key == sf::Keyboard::Key::Left)
        //     game.setQuadTreeCapacity(std::max(1, game.getQuadTreeCapacity() - 1));
        // if (key == sf::Keyboard::Key::.Right)
        //     game.QuadTreeCapacity += 1;
        if (key == sf::Keyboard::Key::S)
            game.spawnAgent();
        if (key == sf::Keyboard::Key::D)
            game.removeLastAgent();
    });

    game.start();
}