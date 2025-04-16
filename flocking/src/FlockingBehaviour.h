//
// Created by stho on 12.04.2025.
//

#pragma once

#include <extensions/extensions.h>
#include "Agent.h"

class AgentRenderer;
class AgentUpdater;



class FlockingBehaviour final : public stho::GameBase {
  struct Diagnostics {
    double updateElapsed {0};
    double quadTreeUpdateElapsed {0};
    double agentUpdateElapsed {0};
    double getNeighborhoodElapsed{0};
  } diagnostics;

public:

  explicit FlockingBehaviour(sf::RenderWindow* window);

  void initialize() override;
  void update() override;
  void render() override;
  void unload() override;

  void reset();

  const Agent* getSelectedAgent() const { return m_agents[m_selectedIndex]; }

  bool getShowCollider() const { return m_showCollider; }
  void toggleShowCollider() { m_showCollider = !m_showCollider; }

  bool getShowNeighborhood() const { return m_showNeighborhood; }
  void toggleShowNeighborhood() { m_showNeighborhood = !m_showNeighborhood; }

  bool getRenderQuadTree() const { return m_renderQuadTree; }
  void toggleQuadTreeRendering() { m_renderQuadTree = !m_renderQuadTree; }
  void toggleQuadTree() { m_useQuadTree = !m_useQuadTree; }

  // int getQuadTreeCapacity() const { return m_quadTree.boundaryCapacity; }
  // void setQuadTreeCapacity(const int size) { m_quadTree.boundaryCapacity = size; }

  void selectFirst() { m_selectedIndex = 0; }
  void selectNext() { m_selectedIndex = m_selectedIndex++ % m_agents.size(); }

  float getAgentSpeed() const;
  void setAgentSpeed(float speed) const;

  std::list<Agent*> getNeighbors(const Agent* agent);

  void spawnAgent();
  void removeLastAgent();

private:
  std::unique_ptr<stho::QuadTree<Agent*>> m_quadTree{nullptr};
  std::vector<Agent*> m_agents;
  stho::ObjectPool<Agent>* m_agentPool{};
  AgentRenderer* m_agentRenderer{};
  AgentUpdater* m_agentUpdater{};
  bool m_showCollider{false};
  bool m_showNeighborhood{false};
  bool m_renderQuadTree{true};
  bool m_useQuadTree{true};
  int m_numberOfAgents{300};
  int m_selectedIndex{0};
  void _applyRandomPositionAndDirectionToAgents();
};