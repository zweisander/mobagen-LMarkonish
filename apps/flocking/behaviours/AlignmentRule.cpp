#include "AlignmentRule.h"
#include <glm/glm.hpp>

glm::vec2 AlignmentRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 averageVelocity(0.f);
  // glm::vec2 can be divided by a float, which will divide each component of the vector by that float.

  // begin solution
  float neighboidY = 0.f;
  float neighboidX = 0.f;
  for (int i = 0; i < neighborhood.size(); i++) {
    neighboidX += neighborhood[i].velocity.x;
    neighboidY += neighborhood[i].velocity.y;
  }
  neighboidX = neighboidX / (neighborhood.size() + 0.00001);
  neighboidY = neighboidY / (neighborhood.size() + 0.00001);
  averageVelocity = glm::vec2(neighboidX, neighboidY);

  return averageVelocity;
  //return glm::vec2(0);
  // end solution
}
