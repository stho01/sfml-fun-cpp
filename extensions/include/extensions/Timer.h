#pragma once

#include <chrono>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>
#include <cmath>

namespace stho {

    class Timer {
    public:
        class Interval {
        public:
            Interval(const long long ms, std::function<void()> callback)
                : m_callback(std::move(callback)),
                  m_time(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::milliseconds(ms))),
                  m_elapsed(std::chrono::microseconds(0)),
                  pause(false) {}

            void update() {
                if (pause) return;
                m_elapsed += DeltaTime;
                if (m_elapsed >= m_time) {
                    m_callback();
                    m_elapsed -= m_time;
                }
            }

            bool pause;

        private:
            std::function<void()> m_callback;
            std::chrono::microseconds m_time;
            std::chrono::microseconds m_elapsed;
        };

        static void update() {
            auto now = std::chrono::steady_clock::now();
            if (!m_previous.has_value()) {
                DeltaTime = std::chrono::microseconds(0);
            } else {
                DeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - m_previous.value());
            }
            m_previous = now;

            const double seconds = static_cast<double>(DeltaTime.count()) / 1000000.0f;
            Fps = seconds > 0 ? static_cast<int>(std::round(1.0f / seconds)) : 0;

            for (auto& interval : m_intervals) {
                if (interval) interval->update();
            }
        }

        static std::shared_ptr<Interval> setInterval(int ms, std::function<void()> callback) {
            auto interval = std::make_shared<Interval>(ms, std::move(callback));
            m_intervals.push_back(interval);
            return interval;
        }

        static void clearInterval(const std::shared_ptr<Interval>& interval) {
            m_intervals.erase(std::ranges::remove(m_intervals, interval).begin(), m_intervals.end());
        }

        static std::chrono::microseconds DeltaTime;
        static int Fps;

        static float deltaTimeSeconds() {
            return  DeltaTime.count() / 1000000.0f;
        }

        static std::chrono::high_resolution_clock::time_point getTimestamp() {
            return std::chrono::high_resolution_clock::now();
        }

        static double getElapsed(const std::chrono::high_resolution_clock::time_point timestamp) {
            const auto diff = std::chrono::high_resolution_clock::now() - timestamp;
            const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
            return static_cast<double>(duration) / 1000000.0;
        }

    private:
        static inline std::optional<std::chrono::steady_clock::time_point> m_previous;
        static inline std::vector<std::shared_ptr<Interval>> m_intervals;

    };

    // definisjon av statiske variabler
    inline std::chrono::microseconds Timer::DeltaTime = std::chrono::microseconds(0);
    inline int Timer::Fps = 0;

} // namespace stho
