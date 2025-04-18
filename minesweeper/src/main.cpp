#include <SFML/Graphics.hpp>
#include <extensions/extensions.h>
#include "Game.h"

int main() {
    const auto window = stho::WindowFactory::CreateDefault({600, 600});

    constexpr int w = 20;
    constexpr int h = 20;
    constexpr int mc = w * h * .15f;

    Game game(window,w,h,mc);

    game.setKeyPressedHandler([&game](const sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Key::R) {
            game.reset();
        }
    });

    game.initialize();
    game.start();
}