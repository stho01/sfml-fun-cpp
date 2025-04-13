//
// Created by stho on 11.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Fonts.h"

namespace stho {

class GameFpsRenderer {
public:

    explicit GameFpsRenderer(std::shared_ptr<sf::RenderTarget> renderTarget):
        m_fpsText(Fonts::Roboto()),
        m_renderTarget(std::move(renderTarget)),
        m_showFps(true)
    { }

    ~GameFpsRenderer() = default;

    [[nodiscard]] bool showFps() const { return m_showFps; }
    void setShowFps(const bool show) { m_showFps = show; }
    void render();

private:
    sf::Text m_fpsText;
    std::shared_ptr<sf::RenderTarget> m_renderTarget;
    bool m_showFps;
};

} // stho
