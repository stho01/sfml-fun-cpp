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
            Interval(int ms, std::function<void()> callback)
                : m_callback(std::move(callback)),
                  m_time(std::chrono::milliseconds(ms)),
                  m_elapsed(std::chrono::milliseconds(0)),
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
            std::chrono::milliseconds m_time;
            std::chrono::milliseconds m_elapsed;
        };

        static void update() {
            auto now = std::chrono::steady_clock::now();
            if (!m_previous.has_value()) {
                DeltaTime = std::chrono::milliseconds(0);
            } else {
                DeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_previous.value());
            }
            m_previous = now;

            const double seconds = DeltaTime.count() / 1000.0;
            Fps = seconds > 0 ? static_cast<int>(std::round(1.0 / seconds)) : 0;

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

        static std::chrono::milliseconds DeltaTime;
        static int Fps;

        static float deltaTimeSeconds() {
            const auto dtSec = std::chrono::duration_cast<std::chrono::seconds>(DeltaTime).count();
            return static_cast<float>(dtSec);
        }

    private:
        static inline std::optional<std::chrono::steady_clock::time_point> m_previous;
        static inline std::vector<std::shared_ptr<Interval>> m_intervals;

    };

    // definisjon av statiske variabler
    inline std::chrono::milliseconds Timer::DeltaTime = std::chrono::milliseconds(0);
    inline int Timer::Fps = 0;

} // namespace stho
