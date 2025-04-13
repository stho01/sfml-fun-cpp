//
// Created by stho on 02.04.2025.
//

#pragma once

#include <chrono>
#include <thread>

namespace stho {

    class Timer {

    public:
        static void update();
        static int fps();
        static std::chrono::duration<double> getDeltaTime();
        static double getDeltaTimeSeconds();
        static double getDeltaTimeMilliseconds();

    private:
        static std::chrono::high_resolution_clock::time_point m_prevTime;
        static std::chrono::duration<double> m_deltaTime;
        static int m_fps;
    };
}

