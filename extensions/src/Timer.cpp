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

int stho::Timer::fps(){
    return instance().m_fps;
}

std::chrono::duration<double> stho::Timer::getDeltaTime(){
    return instance().m_deltaTime;
}

double stho::Timer::getDeltaTimeSeconds() {
    return instance().m_deltaTime.count();
}

double stho::Timer::getDeltaTimeMilliseconds() {
    return instance().m_deltaTime.count() * 1000;
}
