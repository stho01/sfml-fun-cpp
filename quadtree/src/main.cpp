//
// Created by stenm on 13.04.2025.
//

#include <extensions/extensions.h>
#include "Game.h"

int main() {
    const auto window = stho::WindowFactory::CreateDefault();
    Game game(window);
    game.initialize();
    game.setKeyPressedHandler([&game](const sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Key::A) game.toggleSelectionType();
    });
    game.start();
}