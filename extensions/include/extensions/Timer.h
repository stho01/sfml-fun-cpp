#pragma once

#include <chrono>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>

namespace stho {

    class Timer {
    public:
        class Interval;

    private:
        static inline std::optional<std::chrono::steady_clock::time_point> _previous;
        static inline std::vector<std::shared_ptr<Interval>> _intervals;

    public:
        static inline auto DeltaTime = std::chrono::microseconds(0);;
        static inline int Fps = 0;

        static void update() {
            auto now = std::chrono::steady_clock::now();
            if (!_previous.has_value()) {
                DeltaTime = std::chrono::microseconds(0);
            } else {
                DeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - _previous.value());
            }
            _previous = now;

            const double seconds = static_cast<double>(DeltaTime.count()) / 1000000.0f;
            Fps = seconds > 0 ? static_cast<int>(std::round(1.0f / seconds)) : 0;

            for (auto& interval : _intervals) {
                if (interval) interval->update();
            }
        }

        static std::shared_ptr<Interval> setInterval(int ms, std::function<void()> callback) {
            auto interval = std::make_shared<Interval>(ms, std::move(callback));
            _intervals.push_back(interval);
            return interval;
        }

        static void clearInterval(const std::shared_ptr<Interval>& interval) {
            _intervals.erase(std::ranges::remove(_intervals, interval).begin(), _intervals.end());
        }

        static float deltaTimeSeconds() {
            return DeltaTime.count() / 1000000.0;
        }

        static float deltaTimeMilliseconds() {
            return  DeltaTime.count() / 1000.0;
        }

        static std::chrono::high_resolution_clock::time_point getTimestamp() {
            return std::chrono::high_resolution_clock::now();
        }

        static double getElapsed(const std::chrono::high_resolution_clock::time_point timestamp) {
            const auto diff = std::chrono::high_resolution_clock::now() - timestamp;
            const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
            return static_cast<double>(duration) / 1000000.0;
        }

        class Interval {
            std::function<void()> _callback;
            std::chrono::microseconds _time;
            std::chrono::microseconds _elapsed;

        public:
            Interval(const long long ms, std::function<void()> callback)
                : _callback(std::move(callback)),
                  _time(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::milliseconds(ms))),
                  _elapsed(std::chrono::microseconds(0)),
                  pause(false) {}

            void update() {
                if (pause) return;
                _elapsed += DeltaTime;
                if (_elapsed >= _time) {
                    _callback();
                    _elapsed -= _time;
                }
            }

            bool pause;
        };
    };
} // namespace stho
