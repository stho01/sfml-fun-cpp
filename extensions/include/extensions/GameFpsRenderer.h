//
// Created by stho on 11.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>

namespace stho {

    class GameFpsRenderer {
    public:

        explicit GameFpsRenderer(sf::RenderTarget* renderTarget);
        ~GameFpsRenderer() = default;

        [[nodiscard]] bool showFps() const { return m_showFps; }
        void setShowFps(const bool show) { m_showFps = show; }
        void render();

    private:
        sf::Text m_fpsText;
        sf::RenderTarget* m_renderTarget;
        bool m_showFps;
    };

} // stho
