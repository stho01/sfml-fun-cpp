//
// Created by stho on 12.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "FloatCircle.h"

namespace stho {

    template<typename T>
    class QuadTree
    {
    public:
        unsigned int boundaryCapacity = 4;

        explicit QuadTree(const sf::FloatRect& boundary)
            : m_boundary(boundary) {}

        bool insert(const sf::Vector2f& vector, const T& data) {
            if (!m_boundary.contains(vector))
                return false;

            if (m_data.size() < this->boundaryCapacity && this->m_northWest == nullptr) {
                this->m_data.push_back({ vector, data });
                return true;
            }

            if (this->m_northWest == nullptr)
                this->_subdivide();

            if (this->m_northEast->insert(vector, data)) return true;
            if (this->m_northWest->insert(vector, data)) return true;
            if (this->m_southEast->insert(vector, data)) return true;
            if (this->m_southWest->insert(vector, data)) return true;

            return false;
        }

        std::vector<T> queryRange(const FloatCircle& boundary) const {
            const auto rect = sf::FloatRect(
            {boundary.x - boundary.radius, boundary.x - boundary.radius},
            {boundary.radius, boundary.radius});

            if (!m_boundary.findIntersection(rect).has_value())
                return std::vector<T>();

            std::vector<T> inRange;
            for (int i = 0; i < m_data.size(); i++) {
                if (auto datum = m_data[i]; boundary.contains(datum.point.x, datum.point.y)) {
                    inRange.push_back(datum.data);
                }
            }

            for (int i = 0; i < m_data.size(); i++) {
                if (auto datum = m_data[i]; boundary.contains(datum.point.x, datum.point.y)) {
                    inRange.push_back(datum.data);
                }
            }

            if (this->m_northWest == nullptr)
                return inRange;

            auto b = m_northEast->queryRange(boundary);
            for (int i = 0; i < b.size(); i++) inRange.push_back(b[i]);
            b = m_northWest->queryRange(boundary);
            for (int i = 0; i < b.size(); i++) inRange.push_back(b[i]);
            b = m_southEast->queryRange(boundary);
            for (int i = 0; i < b.size(); i++) inRange.push_back(b[i]);
            b = m_southWest->queryRange(boundary);
            for (int i = 0; i < b.size(); i++) inRange.push_back(b[i]);

            return inRange;
        }

        std::vector<T> queryRange(const sf::FloatRect& boundary) {
            if (!this->m_boundary.findIntersection(boundary).has_value())
                return std::vector<T*>();

            std::vector<T> inRange;

            for (int i = 0; i < m_data.size(); i++) {
                const auto datum = m_data[i];
                if (boundary.contains(datum.point))
                    inRange.push_back(datum.data);
            }

            if (this->m_northWest == nullptr)
                return inRange;

            auto b = m_northEast.queryRange(boundary);
            for (int i = 0; i < b.size(); i++) inRange.push_back(b[i]);
            b = m_northWest.queryRange(boundary);
            for (int i = 0; i < b.size(); i++) inRange.push_back(b[i]);
            b = m_southEast.queryRange(boundary);
            for (int i = 0; i < b.size(); i++) inRange.push_back(b[i]);
            b = m_southWest.queryRange(boundary);
            for (int i = 0; i < b.size(); i++) inRange.push_back(b[i]);

            return inRange.ToArray();
        }

        std::vector<sf::FloatRect> getBoundaries() {
            std::vector<sf::FloatRect> boundaries;

            boundaries.push_back(this->m_boundary);

            if (this->m_northEast == nullptr)
                return boundaries;

            auto b = this->m_northEast->getBoundaries();
            for (int i = 0; i < b.size(); i++) boundaries.push_back(b[i]);
            b = this->m_northWest->getBoundaries();
            for (int i = 0; i < b.size(); i++) boundaries.push_back(b[i]);
            b = this->m_southEast->getBoundaries();
            for (int i = 0; i < b.size(); i++) boundaries.push_back(b[i]);
            b = this->m_southWest->getBoundaries();
            for (int i = 0; i < b.size(); i++) boundaries.push_back(b[i]);

            return boundaries;
        }



    private:
        struct DataHolder {
            sf::Vector2f point;
            T data;
        };

        sf::FloatRect m_boundary;
        std::vector<DataHolder> m_data;
        std::unique_ptr<QuadTree> m_northEast{nullptr};
        std::unique_ptr<QuadTree> m_northWest{nullptr};
        std::unique_ptr<QuadTree> m_southEast{nullptr};
        std::unique_ptr<QuadTree> m_southWest{nullptr};

        void _subdivide() {
            const auto width = m_boundary.size.x / 2;
            const auto height = m_boundary.size.y / 2;
            const sf::Vector2f size = {width, height};
            const auto top = m_boundary.position.y;
            const auto left = m_boundary.position.x;
            const auto bottom = m_boundary.position.y + m_boundary.size.y;
            const auto right = m_boundary.position.x + m_boundary.size.x;

            m_northWest = std::make_unique<QuadTree>(sf::FloatRect({left,top}, size));
            m_northWest->boundaryCapacity = this->boundaryCapacity;
            m_northEast = std::make_unique<QuadTree>(sf::FloatRect({right,top}, size));
            m_northEast->boundaryCapacity = this->boundaryCapacity;
            m_southEast = std::make_unique<QuadTree>(sf::FloatRect({right,bottom}, size));
            m_southEast->boundaryCapacity = this->boundaryCapacity;
            m_southWest = std::make_unique<QuadTree>(sf::FloatRect({left,bottom}, size));
            m_southWest->boundaryCapacity = this->boundaryCapacity;
        }
    };
}
