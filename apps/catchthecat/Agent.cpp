#include "Agent.h"
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "World.h"


using namespace std;

std::vector<Point2D> Agent::generatePath(CatWorld* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  std::optional<Point2D> borderExit;  // sentinel: no border found yet

  while (!frontier.empty()) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
    Point2D current = {0, 0};
    current = frontier.top();
    frontier.pop();
    frontierSet.erase(current);
    visited.insert(pair(current, true));
    auto candidatesNeighbors = w->neighbors(current);
    vector<Point2D> neighbors;
    /* for (auto candidate : candidatesNeighbors) {
      if (!w->isValidPosition(candidate) || !visited.contains(candidate) || frontierSet.contains(candidate) || catPos == candidate
          || w->getContent(candidate)) {
        neighbors.push_back(candidate);
      }
    }*/
    neighbors = checkVisitable(w, catPos);
    for (int i = 0; i < neighbors.size(); i++) 
    {
      if (cameFrom.contains(neighbors[i])) continue;
      cameFrom.insert(pair(current, neighbors[i]));
      //frontier.push(neighbors[i]);
      frontierSet.emplace(neighbors[i]);
      //check if neighbor is exit, break both loops
      if (w->catWinsOnSpace(neighbors[i]))
      {
        borderExit = neighbors[i];
        break;
      }
    }
    if (borderExit.has_value())
    {
      break;
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  if (w->getWorldSideSize() < 30)
  {
    //return 
  } else {
    return vector<Point2D>();
  }
  
}
 /* bool Agent::contains(queue<Point2D> q, Point2D target) {
  while (!q.empty()) {
    if (q.front() == target) {
      return true;
    }
    q.pop();
  }
  return false;
}
*/

vector<Point2D> checkVisitable(CatWorld* w, Point2D pos)
{ 
    vector<Point2D> validNeighbors;
  for (Point2D candidate : w->neighbors(pos)) {
      if (candidate == pos || !w->isValidPosition(candidate) || w->getContent(candidate))
      {
      continue;
      }
      validNeighbors.push_back(candidate);
  }
  return validNeighbors;
}

float heuristic(CatWorld* w, Point2D current) {
  return std::min((w->getWorldSideSize() / 2 - std::abs(current.x)), (w->getWorldSideSize() / 2 - std::abs(current.y)));
}
