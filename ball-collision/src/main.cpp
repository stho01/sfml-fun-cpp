#include <extensions/extensions.h>
#include "Game.h"

int main() {
    const auto window = stho::WindowFactory::CreateDefault();
    Game game(window);
    game.initialize();
    game.start();
}