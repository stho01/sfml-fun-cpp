﻿//
// Created by stho on 12.04.2025.
//

#include <iostream>
#include <extensions/extensions.h>
#include "FlockingBehaviour.h"
#include "AgentRenderer.h"
#include "AgentUpdater.h"

// CTOR::::

FlockingBehaviour::FlockingBehaviour(sf::RenderWindow* window)
  : GameBase(window) {
    setClearColor(sf::Color::Black);
}

// PUBLIC::::

void FlockingBehaviour::initialize() {
    Logger::Info("FlockingBehaviour::initialize");
    m_quadTree = std::make_unique<stho::QuadTree<Agent*>>(windowBounds());
    m_agentPool = new stho::ObjectPool<Agent>();
    m_agentRenderer = new AgentRenderer(this, this->m_window);
    m_agentUpdater = new AgentUpdater(this);
    this->_applyRandomPositionAndDirectionToAgents();

    stho::Timer::setInterval(1000, [&] {
        Logger::Info("[FlockingBehaviour]: diag.updateElapsed {} ms, diag.quadTreeUpdateElapsed: {} ms, diag.agentUpdateElapsed: {} ms, getNeighborhoodElapsed: {} ms",
            diagnostics.updateElapsed * 1000,
            diagnostics.quadTreeUpdateElapsed * 1000,
            diagnostics.agentUpdateElapsed * 1000,
            diagnostics.getNeighborhoodElapsed * 1000);
    });
}

void FlockingBehaviour::unload() {
    Logger::Info("FlockingBehaviour::Game unloading");
    for (const auto agent : m_agents) {
        m_agentPool->release(agent);
    }
    m_agents.clear();
    delete m_agentRenderer;
    delete m_agentUpdater;
    delete m_agentPool;
    m_agentRenderer = nullptr;
    m_agentUpdater = nullptr;
    m_agentPool = nullptr;
}

void FlockingBehaviour::update() {
    const auto startTs = stho::Timer::getTimestamp();
    if (m_useQuadTree) {
        m_quadTree->clear();
        for (const auto& m_agent : m_agents)
            m_quadTree->insert(m_agent->pos, m_agent);
    }
    diagnostics.quadTreeUpdateElapsed = stho::Timer::getElapsed(startTs);

    const auto agentUpdateTimestamp = stho::Timer::getTimestamp();
    for (const auto agent : m_agents) {
        m_agentUpdater->update(agent);
        m_agentRenderer->render(agent);
    }
    diagnostics.agentUpdateElapsed = stho::Timer::getElapsed(agentUpdateTimestamp);

    diagnostics.updateElapsed = stho::Timer::getElapsed(startTs);
}

void FlockingBehaviour::render() {
    if (m_renderQuadTree && m_useQuadTree) {
        const auto boundaries = m_quadTree->getBoundaries();
        for (const auto boundary : boundaries) {
            sf::RectangleShape shape;
            shape.setPosition(boundary.position);
            shape.setSize(boundary.size);
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineColor(sf::Color::Yellow);
            shape.setOutlineThickness(1.0f);
            this->m_window->draw(shape);
        }
    }
}

void FlockingBehaviour::reset() {
    m_showCollider = false;
    setAgentSpeed(20.0f);

    while (!m_agents.empty()) {
        const auto agent = m_agents.back();
        m_agents.pop_back();
        m_agentPool->release(agent);
    }

    _applyRandomPositionAndDirectionToAgents();
}

void FlockingBehaviour::setAgentSpeed(const float speed) const {
    m_agentUpdater->maxSpeed = speed;
}

float FlockingBehaviour::getAgentSpeed() const {
    return m_agentUpdater->maxSpeed;
}

std::list<Agent*> FlockingBehaviour::getNeighbors(const Agent* agent) {
    auto ts = stho::Timer::getTimestamp();
    std::list<Agent*> neighbors;

    if (m_useQuadTree) {
        const stho::FloatCircle neighborhood(agent->pos, agent->neighborhoodRadius);
        const auto potentialNeighbor = m_quadTree->queryRange(neighborhood);

        for (auto i : potentialNeighbor) {
            if (i != agent) {
                neighbors.push_back(i);
            }
        }

    } else {
        for (auto potentialNeighbor : m_agents) {
            if (potentialNeighbor == agent)
                continue;

            const bool inNeighborhood = (potentialNeighbor->pos - agent->pos).lengthSquared() < agent->neighborhoodRadius * agent->neighborhoodRadius;
            if (!inNeighborhood)
                continue;

            neighbors.push_back(potentialNeighbor);
        }
    }

    diagnostics.getNeighborhoodElapsed = stho::Timer::getElapsed(ts);
    return neighbors;
}

void FlockingBehaviour::spawnAgent() {
    const auto randomPosition = stho::RandomNumber::Vector2f(this->windowBounds());
    const auto randomDirection = stho::RandomNumber::vector2fAndReflect(1, 10).normalized();

    const auto agent = m_agentPool->acquire();
    agent->pos = randomPosition;
    agent->acceleration = randomDirection.normalized();
    agent->velocity = randomDirection * m_agentUpdater->maxSpeed * 0.75f;

    m_agents.push_back(agent);
}

void FlockingBehaviour::removeLastAgent() {
    if (!m_agents.empty()) {
        const auto agent = m_agents.back();
        m_agents.pop_back();
        m_agentPool->release(agent);
    }
}


// PRIVATE:::

void FlockingBehaviour::_applyRandomPositionAndDirectionToAgents() {
    for (int i = 0; i < m_numberOfAgents; i++)
        this->spawnAgent();
}