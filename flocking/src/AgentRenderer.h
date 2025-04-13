﻿//
// Created by stho on 12.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Agent.h"

class FlockingBehaviour;

struct AgentGeometry {
    float radius;
    sf::Vector2f origin;
};

class AgentRenderer {
public:

    explicit AgentRenderer(
      FlockingBehaviour* flockingBehaviour,
      sf::RenderTarget* renderTarget):
        m_flockingBehaviour(flockingBehaviour),
        m_renderTarget(renderTarget),
        m_ship(24.0f, 3),
        m_collider(24.0f),
        m_neighborhood(24.0f)
    { }

    ~AgentRenderer() = default;

    void render(const Agent& agent);
    void drawCollider(const Agent& agent, const AgentGeometry& geometry);
    void drawNeighborhoodAreas(const Agent& agent, const AgentGeometry& geometry);

private:

    void _drawAgent(const Agent& agent, const AgentGeometry& geometry);
    AgentGeometry _getGeometry(const Agent& agent) const;

    FlockingBehaviour* m_flockingBehaviour;
    sf::RenderTarget* m_renderTarget;
    sf::CircleShape m_ship;
    sf::CircleShape m_collider;
    sf::CircleShape m_neighborhood;
};
