#include <extensions/extensions.h>
#include "Game.h"

int main() {
    const auto window = stho::WindowFactory::CreateDefault({900,900});
    Game game(window);
    game.initialize();
    game.start();
}