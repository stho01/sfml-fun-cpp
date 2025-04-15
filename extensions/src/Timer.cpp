// //
// // Created by stho on 02.04.2025.
// //
//
// #include "extensions/Timer.h"
// #include "extensions/Logger.h"
//
// std::chrono::high_resolution_clock::time_point stho::Timer::m_prevTime;
// std::chrono::duration<double> stho::Timer::m_deltaTime;
// int stho::Timer::m_fps;
//
// void stho::Timer::update() {
//     const auto now = std::chrono::high_resolution_clock::now();
//     m_deltaTime = std::chrono::duration<double, std::milli>(now - m_prevTime);
//     m_prevTime = now;
//     m_fps = static_cast<int>(1.0f / m_deltaTime.count());
// }
//
// int stho::Timer::fps(){
//     return m_fps;
// }
//
// std::chrono::duration<std::chrono::microseconds> stho::Timer::getDeltaTime(){
//     return m_deltaTime;
// }
//
// double stho::Timer::getDeltaTimeSeconds() {
//     const auto deltaTime = m_deltaTime.count();
//     // const auto msg = std::format("Delta Time: {:.12f} seconds", deltaTime);
//     // Logger::Info(msg);
//     return deltaTime;
// }
//
// double stho::Timer::getDeltaTimeMilliseconds() {
//     return m_deltaTime.count() * 1000;
// }
//
// stho::Timer::Interval::Interval(long long ms, std::function<void()> callback) :
//     m_callback(std::move(callback)),
//     m_elapsedMicroseconds(std::chrono::milliseconds(ms)),
//     m_time(std::chrono::microseconds(ms)) {}
//
// void stho::Timer::Interval::UpdateInterval() {
//     const auto& dt = getDeltaTime();
//     m_elapsedMicroseconds =  m_elapsedMicroseconds + dt;
// }