//
// Created by stho on 12.04.2025.
//

#include "AgentUpdater.h"
#include <extensions/extensions.h>
#include "FlockingBehaviour.h"

void AgentUpdater::update(Agent& agent)
{
    agent.acceleration = this->flock(agent);
    agent.velocity = this->limitMagnitude(agent.acceleration + agent.velocity, maxSpeed);
    agent.pos += agent.velocity * static_cast<float>(stho::Timer::instance().getDeltaTimeSeconds());
    this->wraparound(agent);
}

sf::Vector2f AgentUpdater::flock(const Agent& agent) {
    auto neighbors = this->m_flockingBehaviour->getNeighbors(agent);

    if (neighbors.size() == 0)
        return agent.acceleration;

    auto alignment = sf::Vector2f(0.0f, 0.0f);
    auto cohesion = sf::Vector2f(0.0f, 0.0f);
    auto separation = sf::Vector2f(0.0f, 0.0f);
    auto separationCount = 0;

    for (auto i = 0; i < neighbors.size(); i++) {
        const auto neighbor = neighbors[i];
        auto distanceFromNeighbor = agent.pos - neighbor->pos;

        alignment += neighbor->velocity;
        cohesion += neighbor->pos;

        if ((agent.pos - neighbor->pos).lengthSquared() < (agent.neighborhoodRadius * agent.neighborhoodRadius) * .5) {
            separation += distanceFromNeighbor.normalized() / distanceFromNeighbor.length();
            separationCount++;
        }
    }

    alignment = this->steer(agent, (alignment / (float)neighbors.size()).normalized() * maxSpeed);
    cohesion = this->steer(agent, ((cohesion / (float)neighbors.size()) - agent.pos).normalized() * maxSpeed);
    separation = separationCount == 0 ? separation : this->steer(agent, (separation / (float)separationCount).normalized() * maxSpeed);

    return
        alignment * alignmentAmount
        + cohesion * cohesionAmount
        + separation * separationAmount;
}

void AgentUpdater::wraparound(Agent& agent) {
    auto x = agent.pos.x;
    auto y = agent.pos.y;

    auto screenWidth = this->m_flockingBehaviour->windowWidth();
    auto screenHeight = this->m_flockingBehaviour->windowHeight();
    if ((agent.pos.x + agent.size) < 0) x = screenWidth + agent.size - 1;
    if ((agent.pos.x - agent.size) > screenWidth) x = -agent.size + 1;
    if ((agent.pos.y + agent.size) < 0) y = screenHeight + agent.size - 1;
    if ((agent.pos.y - agent.size) > screenHeight) y = -agent.size + 1;

    agent.pos = sf::Vector2f(x, y);
}

sf::Vector2f AgentUpdater::steer(const Agent& agent, const sf::Vector2f& desired) {
    auto steer = desired - agent.velocity;
    steer = this->limitMagnitude(steer, maxSteeringForce);
    return steer;
}

sf::Vector2f AgentUpdater::limitMagnitude(sf::Vector2f baseVector, const float& maxMagnitude) {
    if (baseVector.lengthSquared() > maxMagnitude * maxMagnitude) {
        baseVector = baseVector.normalized() * maxMagnitude;
    }
    return baseVector;
}