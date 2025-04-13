//
// Created by stho on 12.04.2025.
//

#pragma once

#include <vector>

namespace stho {

template<typename T>
class ObjectPool {
public:

    ObjectPool() = default;
    ~ObjectPool() {
        // Slett alt
        for (auto* obj : m_available) {
            delete obj;
        }
    }

    T* acquire() {
        T* obj = nullptr;

        if (!m_available.empty()) {
            obj = m_available.back();
            m_available.pop_back();
        } else {
            obj = new T();
        }

        return obj;
    }

    void release(T* obj) {
        m_available.push_back(obj);
    }

private:
    std::vector<T*> m_available;
};

}