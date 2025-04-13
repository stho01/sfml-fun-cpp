//
// Created by stho on 02.04.2025.
//

#pragma once

#include <chrono>
#include <thread>

namespace stho {

    class Timer {

    public:
        static Timer& instance() {
            static Timer instance; // Lages kun én gang, trådtrygt i C++11+
            return instance;
        }

        void update();
        
        static int fps();
        static std::chrono::duration<double> getDeltaTime();
        static double getDeltaTimeSeconds();
        static double getDeltaTimeMilliseconds();

    private:

        Timer() = default; // Privat konstruktør
        ~Timer() = default;

        // Forhindre kopiering og flytting
        Timer(const Timer&) = delete;
        Timer& operator=(const Timer&) = delete;

        std::chrono::high_resolution_clock::time_point m_prevTime{ };
        std::chrono::duration<double> m_deltaTime{ };
        int m_fps{ 0 };

    };

}

