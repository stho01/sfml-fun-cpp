#include <extensions/extensions.h>
#include "Fireworks.h"

int main() {
    const auto window = stho::WindowFactory::CreateDefault({1200,950});
    Fireworks fireworks(window);
    fireworks.initialize();
    fireworks.start();
}