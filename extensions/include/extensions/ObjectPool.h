//
// Created by stho on 12.04.2025.
//

#pragma once

#include <vector>
#include "Logger.h"

namespace stho {

    template<typename T>
    class ObjectPool {
        std::vector<T*> _available;

    public:

        ~ObjectPool() {
            Logger::Info("ObjectPool destroyed");
        }

        static ObjectPool* shared() {
            static ObjectPool instance;
            return &instance;
        }

        template<typename... Args>
        std::shared_ptr<T> acquire(Args&&... args) {
            T* obj = nullptr;

            if (!_available.empty()) {
                obj = _available.back();
                _available.pop_back();

                // Rekonstruer objektet på plass
                obj->~T();
                new (obj) T(std::forward<Args>(args)...);
                Logger::Debug("Object reused. AvailableCount={}", this->_available.size());
            } else {
                obj = new T(std::forward<Args>(args)...);
                Logger::Debug("Object created. AvailableCount={}", this->_available.size());
            }

            // Lag en shared_ptr med custom deleter som returnerer objektet til poolen
            return std::shared_ptr<T>(
                obj,
                [this](T* p) {
                    p->~T(); // Destruer objektet
                    this->_available.push_back(p);
                    Logger::Debug("Object returned to pool. AvailableCount={}", this->_available.size());
                }
            );
        }

    };
}