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
        explicit QuadTree(const sf::FloatRect& boundary, const unsigned int capacity = 4, const unsigned int depth = 8)
            : m_boundary(boundary) , m_boundaryCapacity(capacity), m_depth(depth) { }

        bool insert(const sf::Vector2f& vector, const T data) {
            if (!m_boundary.contains(vector)) {
                return false;
            }

            if (m_data.size() < m_boundaryCapacity) {
                m_data.push_back({ vector, data });
                return true;
            }

            if (m_isLeaf) {
                return false;
            }

            for (auto& child : m_children) {
                if (child->insert(vector, data)) {
                    return true;
                }
            }

            return false;
        }

        void clear() {
            m_data.clear();

            if (m_isLeaf) {
                return;
            }

            for (auto& child : m_children) {
                child->clear();
            }
        }

        std::vector<T> queryRange(const FloatCircle& boundary) const {
            const sf::FloatRect rect(
                {boundary.x - boundary.radius, boundary.x - boundary.radius},
                {boundary.radius, boundary.radius});

            if (!m_boundary.findIntersection(rect).has_value())
                return std::vector<T>();

            std::vector<T> inRange;
            for (const auto& datum : m_data) {
                if (boundary.contains(datum.point)) {
                    inRange.push_back(datum.data);
                }
            }

            if (m_isLeaf)
                return inRange;

            for (auto& child : m_children) {
                auto childItems = child->queryRange(boundary);

                for (int j = 0; j < childItems.size(); j++) {
                    inRange.push_back(childItems[j]);
                }
            }

            return inRange;
        }

        std::vector<T> queryRange(const sf::FloatRect& boundary) {
            if (!this->m_boundary.findIntersection(boundary).has_value())
                return std::vector<T>();

            std::vector<T> inRange;

            for (int i = 0; i < m_data.size(); i++) {
                const auto datum = m_data[i];
                if (boundary.contains(datum.point))
                    inRange.push_back(datum.data);
            }

            if (m_isLeaf) {
                return inRange;
            }

            for (auto& child : m_children) {
                auto childItems = child->queryRange(boundary);
                for (int j = 0; j < childItems.size(); j++)
                    inRange.push_back(childItems[j]);
            }

            return inRange;
        }

        std::vector<sf::FloatRect> getBoundaries() {
            std::vector<sf::FloatRect> boundaries;

            boundaries.push_back(this->m_boundary);

            if (m_isLeaf)
                return boundaries;

            for (auto& child : m_children) {
                auto childBoundaries = child->getBoundaries();

                for (int j = 0; j < childBoundaries.size(); j++)
                    boundaries.push_back(childBoundaries[j]);
            }

            return boundaries;
        }

    private:
        struct DataHolder {
            sf::Vector2f point;
            T data;
        };

        sf::FloatRect m_boundary;
        std::vector<DataHolder> m_data;
        std::unique_ptr<QuadTree> m_children[4];
        bool m_isLeaf = true; // initially a leaf
        unsigned int m_boundaryCapacity = 4;
        unsigned int m_depth = 8;

        void _createTree() {

            for (int i = 0; i < m_depth; i++) {

            }

            const auto width = m_boundary.size.x / 2;
            const auto height = m_boundary.size.y / 2;
            const sf::Vector2f size = { width, height };
            const auto top = m_boundary.position.y;
            const auto left = m_boundary.position.x;
            const auto bottom = m_boundary.position.y + height;
            const auto right = m_boundary.position.x + width;

            m_children[0] = std::make_unique<QuadTree>(sf::FloatRect({left,top}, size), m_boundaryCapacity);
            m_children[1] = std::make_unique<QuadTree>(sf::FloatRect({right,top}, size), m_boundaryCapacity);
            m_children[2] = std::make_unique<QuadTree>(sf::FloatRect({right,bottom}, size), m_boundaryCapacity);
            m_children[3] = std::make_unique<QuadTree>(sf::FloatRect({left,bottom}, size), m_boundaryCapacity);

            m_isLeaf = false; // no longer a leaf

        }
    };
}
