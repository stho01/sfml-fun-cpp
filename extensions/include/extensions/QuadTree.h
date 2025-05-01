//
// Created by stho on 12.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <utility>
#include "FloatCircle.h"
#include "ObjectPool.h"

namespace stho {

    template<typename T>
    class QuadTree
    {
    private:
        struct Node {
            sf::Vector2f point;
            T data;
        };

    public:
        explicit QuadTree(const sf::FloatRect& boundary, const unsigned int capacity = 4)
            : m_boundary(boundary), m_children{}, m_boundaryCapacity(capacity) {}

        explicit QuadTree(const sf::FloatRect& boundary, const unsigned int capacity, std::string name, const int depth)
            : m_name(std::move(name)), m_depth(depth), m_boundary(boundary), m_children{}, m_boundaryCapacity(capacity) {}

        bool insert(const sf::Vector2f& vector, const T data) {
            return insert({vector, data});
        }

        bool insert(const Node& node) {
            if (!m_boundary.contains(node.point)) {
                return false;
            }

            if (m_nodes.size() < m_boundaryCapacity && m_isLeaf) {
                m_nodes.push_back(node);
                return true;
            }

            if (m_isLeaf)
                _subdivide();

            for (auto& child : m_children) {
                if (child->insert(node)) {
                    return true;
                }
            }

            return false;
        }

        void clear() {
            m_nodes.clear();

            if (m_isLeaf) {
                return;
            }

            for (const auto& child : m_children) {
                child->clear();
            }
            m_isLeaf = true;
        }

        std::list<T> queryRange(const FloatCircle& circle) const {
            const auto size = circle.radius * 2;
            const sf::FloatRect rect(
                { circle.x - circle.radius, circle.y - circle.radius},
                { size, size });

            std::list<T> result;
            queryRangeRecursive(circle, rect, result);
            return result;
        }

        void queryRangeRecursive(const FloatCircle& circle, const sf::FloatRect& quadrant, std::list<T>& nodes) const {
            if (!m_boundary.findIntersection(quadrant).has_value()) {
                return;
            }

            if (m_isLeaf) {
                for (const auto& node : m_nodes) {
                    if (circle.contains(node.point)) {
                        nodes.push_back(node.data);
                    }
                }
            } else {
                for (auto& child : m_children) {
                    child->queryRangeRecursive(circle, quadrant, nodes);
                }
            }
        }

        std::list<T> queryRange(const sf::FloatRect& boundary) const {
            std::list<T> nodes;
            queryRangeRecursive(boundary, nodes);
            return nodes;
        }

        void queryRangeRecursive(const sf::FloatRect& boundary, std::list<T>& nodes) const {
            if (!this->m_boundary.findIntersection(boundary).has_value()) {
                return;
            }

            if (m_isLeaf) {

                for (int i = 0; i < m_nodes.size(); i++) {
                    const auto datum = m_nodes[i];

                    if (boundary.contains(datum.point)) {
                        nodes.push_back(datum.data);
                    }
                }

            } else {
                for (auto& child : m_children) {
                    child->queryRangeRecursive(boundary, nodes);
                }
            }
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
        std::string m_name;
        int m_depth = 0;
        // ObjectPool<QuadTree> m_pool;
        sf::FloatRect m_boundary;
        std::vector<Node> m_nodes;
        std::shared_ptr<QuadTree> m_children[4];
        bool m_isLeaf = true; // initially a leaf
        unsigned int m_boundaryCapacity = 4;

        void _subdivide() {
            const auto width = m_boundary.size.x / 2;
            const auto height = m_boundary.size.y / 2;
            const sf::Vector2f size = { width, height };
            const auto top = m_boundary.position.y;
            const auto left = m_boundary.position.x;
            const auto bottom = m_boundary.position.y + height;
            const auto right = m_boundary.position.x + width;

            int nextDepth = m_depth + 1;
            m_children[0] = ObjectPool<QuadTree>::shared()->acquire(sf::FloatRect({left,top}, size), m_boundaryCapacity, "northwest", nextDepth);
            m_children[1] = ObjectPool<QuadTree>::shared()->acquire(sf::FloatRect({right,top}, size), m_boundaryCapacity, "northeast", nextDepth);
            m_children[2] = ObjectPool<QuadTree>::shared()->acquire(sf::FloatRect({right,bottom}, size), m_boundaryCapacity, "southeast", nextDepth);
            m_children[3] = ObjectPool<QuadTree>::shared()->acquire(sf::FloatRect({left,bottom}, size), m_boundaryCapacity, "southwest", nextDepth);

            for (auto& node : m_nodes) {
                for (auto& child : m_children) {
                    child->insert(node.point, node.data);
                }
            }

            m_nodes.clear();
            m_isLeaf = false; // no longer a leaf
        }
    };
}
