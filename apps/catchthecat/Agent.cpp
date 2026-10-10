#include "Agent.h"
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "World.h"


using namespace std;
float heuristic(CatWorld* w, Point2D current) {
  return min((w->getWorldSideSize() / 2 - abs(current.x)), (w->getWorldSideSize() / 2 - abs(current.y)));
}
vector<Point2D> checkVisitable(CatWorld* w, Point2D pos, unordered_map<Point2D, bool> visited, unordered_set<Point2D> frontierset) {
  vector<Point2D> validNeighbors;
  for (const Point2D candidate : CatWorld::neighbors(pos)) {
    if (candidate == pos || !w->isValidPosition(candidate) || w->getContent(candidate)) {
      continue;
    }
    validNeighbors.push_back(candidate);
  }
  return validNeighbors;
}

std::vector<Point2D> Agent::generatePath(CatWorld* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<pair<float,Point2D>, vector<pair<float, Point2D>>, greater<pair<float, Point2D>>> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  unordered_map<Point2D, float> cost;
  // bootstrap state
  auto catPos = w->getCat();
  frontier.emplace(.0f,catPos);
  cost[catPos] = .0f;
  optional<Point2D> borderExit;  // sentinel: no border found yet
  bool shouldContinue = true;
  while (shouldContinue) {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
    float score;
    Point2D current = {0, 0};
    score = frontier.top().first;
    current = frontier.top().second;
    frontier.pop();
    //frontierSet.erase(current);
    visited[current] = true;
    
    //visited.insert(pair(current, true));
    //frontierSet.emplace(current);
    // auto candidatesNeighbors = w->neighbors(current);
    vector<Point2D> neighbors;
    /* for (auto candidate : candidatesNeighbors) {
      if (!w->isValidPosition(candidate) || !visited.contains(candidate) || frontierSet.contains(candidate) || catPos == candidate
          || w->getContent(candidate)) {
        neighbors.push_back(candidate);
      }
    }*/
    
    if (cost[current] + heuristic(w, current) < score) {
      continue;
      
    }
    neighbors = checkVisitable(w, catPos, visited, frontierSet);

    for (Point2D next : neighbors) {
      float currentCost = cost[current] + 1.0f;

      if (cost.end() == cost.find(next) || currentCost < cost[next]) 
      {
      
        cost[next] = currentCost;
        cameFrom[next] = current;
        float calcScore = cost[next] + heuristic(w, next);
        frontier.emplace(calcScore, current);
       
      }
      
      // check if neighbor is exit, break both loops
      if (w->catWinsOnSpace(current)) {
        borderExit = current;
        break;
      }
      if (frontier.empty())
      {
        shouldContinue = false;
      }
    }
  }
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  vector<Point2D> path;
  if (!borderExit.has_value()) {
    return path;
  } else {
    Point2D borderLoc = borderExit.value();
    while (catPos != borderLoc) {
      path.push_back(borderLoc);
      borderLoc = cameFrom.at(borderLoc);
  }
    return path;
  }
 /* bool Agent::contains(queue<Point2D> q, Point2D target) {
  while (!q.empty()) {
    if (q.front() == target) {
      return true;
    }
    q.pop();
  }
  return false; */
}




