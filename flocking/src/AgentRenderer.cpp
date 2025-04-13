//
// Created by stho on 12.04.2025.
//

#include "AgentRenderer.h"
#include <extensions/Mathf.h>
#include "FlockingBehaviour.h"

void AgentRenderer::render(const Agent& agent) {
    const auto geometry = this->_getGeometry(agent);

    if (this->m_flockingBehaviour->getShowCollider())
        this->drawCollider(agent, geometry);

    const auto selected = this->m_flockingBehaviour->getSelectedAgent();
    if (this->m_flockingBehaviour->getShowNeighborhood() && &agent == &selected)
        this->drawNeighborhoodAreas(agent, geometry);

    this->_drawAgent(agent, geometry);
}

void AgentRenderer::drawCollider(const Agent& agent, const AgentGeometry& geometry) {
    this->m_collider.setRadius(geometry.radius);
    this->m_collider.setOutlineColor(sf::Color::Yellow);
    this->m_collider.setOutlineThickness(1.0f);
    this->m_collider.setFillColor(sf::Color::Transparent);
    this->m_collider.setPosition(agent.pos);
    this->m_collider.setOrigin(geometry.origin);
    this->m_renderTarget->draw(this->m_collider);
}

void AgentRenderer::drawNeighborhoodAreas(const Agent& agent, const AgentGeometry& geometry) {
    this->m_neighborhood.setRadius(agent.neighborhoodRadius);
    this->m_neighborhood.setOutlineColor(sf::Color::Red);
    this->m_neighborhood.setOutlineThickness(1.0f);
    this->m_neighborhood.setFillColor(sf::Color(0xFFAAAA55));
    this->m_neighborhood.setPosition(agent.pos);
    this->m_neighborhood.setOrigin({agent.neighborhoodRadius, agent.neighborhoodRadius});

    this->m_renderTarget->draw(this->m_neighborhood);

    auto separationArea = agent.neighborhoodRadius * .5f;
    this->m_neighborhood.setRadius(separationArea);
    this->m_neighborhood.setOrigin({separationArea, separationArea});
    this->m_renderTarget->draw(this->m_neighborhood);
}

void AgentRenderer::_drawAgent(const Agent& agent, const AgentGeometry& geometry) {
    this->m_ship.setRadius(geometry.radius);
    this->m_ship.setPosition(agent.pos);
    this->m_ship.setScale({0.75f,1.0f});

    this->m_ship.setRotation(stho::Mathf::ToPolarCoordinates(agent.velocity).getAngle());
    this->m_ship.setOrigin(geometry.origin);

    auto selected = this->m_flockingBehaviour->getSelectedAgent();
    auto color =
        &agent == &selected
        ? sf::Color::Green
        : sf::Color::White;

    this->m_ship.setFillColor(color);
    this->m_renderTarget->draw(this->m_ship);
}

AgentGeometry AgentRenderer::_getGeometry(const Agent& agent) const {
    auto radius = agent.size * .5f;
    return { radius, { radius, radius } };
}