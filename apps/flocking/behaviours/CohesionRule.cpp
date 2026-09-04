#include "CohesionRule.h"
#include <glm/glm.hpp>

glm::vec2 CohesionRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 cohesionForce(0.f);

  // glm::length(vec) returns the length of a vector,
  // glm::normalize(vec) returns the normalized vector (length 1) in the same direction as vec.
  float neighboidY = 0.f;
  float neighboidX = 0.f;
  glm::vec2 centerMass;
  // begin solution
  if (neighborhood.empty())
  {
    return cohesionForce;
  }
  for (int i = 0; i < neighborhood.size(); i++)
  {
    neighboidX += neighborhood[i].position.x;
    neighboidY += neighborhood[i].position.y;
  }
  centerMass = glm::vec2(neighboidX / neighborhood.size(), neighboidY / neighborhood.size());
  
  // end solution
  cohesionForce = centerMass - boid.position;
  //cohesionForce = glm::normalize(cohesionForce);
  return cohesionForce;
  //return glm::vec2(0);
  
}
