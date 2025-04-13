//
// Created by stho on 12.04.2025.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "Agent.h"

class FlockingBehaviour;

class AgentUpdater {
public:
    float alignmentAmount = 1.0f;
    float separationAmount = 1.85f;
    float cohesionAmount = 1.0f;
    float maxSteeringForce = .95f;
    float maxSpeed = 150.0f;

    explicit AgentUpdater(FlockingBehaviour* flockingBehaviour):
        m_flockingBehaviour(flockingBehaviour) {}

    void update(Agent* agent);
    sf::Vector2f flock(const Agent* agent);
    void wraparound(Agent* agent) const;
    sf::Vector2f steer(const Agent* agent, const sf::Vector2f& desired);
    sf::Vector2f limitMagnitude(sf::Vector2f baseVector, const float& maxMagnitude);
    
private:
    FlockingBehaviour* m_flockingBehaviour{ nullptr };
};
