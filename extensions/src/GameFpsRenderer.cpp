//
// Created by stho on 11.04.2025.
//

#include "extensions/GameFpsRenderer.h"
#include "extensions/Timer.h"
#include "extensions/Fonts.h"

namespace stho {

    GameFpsRenderer::GameFpsRenderer(sf::RenderTarget* renderTarget):
            m_fpsText(Fonts::Roboto()),
            m_renderTarget(renderTarget),
            m_showFps(true)
    { }

    void GameFpsRenderer::render() {
        if (!this->m_showFps) return;

        const auto text = L"FPS: " + std::to_wstring(Timer::fps());
        this->m_fpsText.setString(text);
        this->m_fpsText.setPosition(sf::Vector2f(5.0f, 5.0f));
        this->m_fpsText.setCharacterSize(32);
        this->m_fpsText.setFillColor(sf::Color::Red);
        this->m_renderTarget->draw(this->m_fpsText);
    }

} // stho