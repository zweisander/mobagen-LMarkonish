#ifndef AGENT_H
#define AGENT_H

#include <glm/glm.hpp>
#include <functional>
#include <vector>
#include <queue>

// Point2D is now glm::ivec2 — same x,y interface, no OOP wrapper needed.
using Point2D = glm::ivec2;
namespace glm {
  inline bool operator<(const glm::ivec2& a, const glm::ivec2& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
  }
}
  // namespace glm

// Hash specialization so Point2D (= glm::ivec2) works in unordered containers.
namespace std {
  template <> struct hash<glm::ivec2> {
    std::size_t operator()(const glm::ivec2& v) const noexcept {
      std::size_t seed = std::hash<int>{}(v.x);
      seed ^= std::hash<int>{}(v.y) + 0x9e3779b9u + (seed << 6) + (seed >> 2);
      return seed;
    }
  };
}  // namespace std

class CatWorld;

class Agent {
public:
  explicit Agent() = default;
  virtual ~Agent() = default;

  virtual Point2D Move(CatWorld*) = 0;

  std::vector<Point2D> generatePath(CatWorld* w);

  //bool contains(queue<Point2D> q, Point2D target);
};

#endif  // AGENT_H
