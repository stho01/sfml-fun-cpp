//
// Created by stho on 02.04.2025.
//

#include "extensions/Timer.h"

void stho::Timer::update() {
    const auto now = std::chrono::high_resolution_clock::now();
    m_deltaTime = std::chrono::duration<double, std::milli>(now - m_prevTime);
    m_prevTime = now;
    m_fps = static_cast<int>(1.0f / m_deltaTime.count());
}