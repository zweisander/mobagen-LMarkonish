#include "../World.h"
#include "../SeededRandom.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>

// Recursive backtracker, in grid units: (0, 0) is the top-left cell, x grows
// right, y grows down — the same units as the World API. The caller seeds
// SeededRandom before the first Step; every decision consumes the seed in
// order, so the maze is deterministic.
//
// Procedure per Step, on the cell at the top of the path stack:
//   1. mark it visited;
//   2. list its visitable (unvisited) neighbors in clockwise order starting
//      from the top: UP, RIGHT, DOWN, LEFT (getVisitables does this);
//   3. none        -> dead end: pop the stack (backtrack). Empty stack = done;
//   4. exactly one -> move to it, do not consume a random number;
//   5. two or more -> consume SeededRandom::next() and pick
//      next() % visitableCount;
//   6. moving opens the wall between the two cells
//      (World::SetNorth/SetEast/SetSouth/SetWest with false).

void RecursiveBacktrackerExample::Clear(World* world) {
  // todo: reset the walk
  // hint:
  //   clear visited and the path stack, then start the walk at the
  //   top-left cell: stack.push_back({0, 0})
  // begin solution
  visited.clear();
  stack.clear();
  stack.push_back({0,0});
  // end solution
}

bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement one iteration of the recursive backtracker
  // hint:
  //   empty stack  -> the maze is done, return false
  //   otherwise, on the cell at the top of the stack:
  //   1. mark it visited;
  //   2. list its visitable neighbors with getVisitables
  //      (already in clockwise order: UP, RIGHT, DOWN, LEFT);
  //   3. none        -> dead end: pop the stack (backtrack);
  //   4. exactly one -> move to it, do not consume a random number;
  //   5. two or more -> consume SeededRandom::next() and pick
  //      next() % visitables.size();
  //   moving = opening the wall between the two cells:
  //     UP    -> w->SetNorth(current, false)
  //     RIGHT -> w->SetEast(current, false)
  //     DOWN  -> w->SetSouth(current, false)
  //     LEFT  -> w->SetWest(current, false)
  //   return true while there is still work (stack not empty after the move)
  // begin solution
  Color32 visColor = {0, 0.5, 0};
  w->SetNodeColor(stack.back(), visColor);
  uint8_t rngcounter = 0;
	if (stack.empty())
	{
		return false;
	}
    std::vector<Point2D> visitables;
    visitables = getVisitables(w, stack.back());
    Point2D temp = stack.back();
	if (visitables.size() == 0) 
	{
      stack.pop_back();

	}
	else if (visitables.size() == 1)
	{
        stack.push_back(visitables[0]);
	}
	else
	{
        int next;
        next = SeededRandom::next(); 
        next = next % visitables.size();
        stack.push_back(visitables[next]);
        rngcounter++;
        SeededRandom::setIndex(rngcounter);
        if (rngcounter == 100)
        {
          rngcounter = 0;
        }
       
	}
        if (temp.y == stack.back().y+1) {
          w->SetNorth(stack.back(), false);
        } else if (temp.x == stack.back().x + 1) {
          w->SetEast(stack.back(), false);
        } else if (temp.y == stack.back().y - 1) {
          w->SetSouth(stack.back(), false);
        } else if (temp.x == stack.back().x - 1) {
          w->SetWest(stack.back(), false);
        }
  // end solution
        if (!stack.empty()) {
          return true;
        }
  
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& point) {
  // todo: list the unvisited neighbors of point, in clockwise order
  // hint:
  //   candidates in order: UP {x, y-1}, RIGHT {x+1, y}, DOWN {x, y+1}, LEFT {x-1, y}
  //   keep a candidate only if it is inside the grid
  //   (0 <= x < w->GetWidth(), 0 <= y < w->GetHeight()) and not visited
  // begin solution
  std::vector<Point2D> unvisited;
  Point2D temp = point;
  temp.y -= 1;
  Color32 visColor = {0, 0.5, 0};
  Color32 compColor;
  
  if (0 <= temp.x && temp.x < w->GetWidth() && 0 <= temp.y && temp.y < w->GetHeight())
  {
    compColor = w->GetNodeColor(temp);
    if (visColor.g != compColor.g) {
      unvisited.push_back(temp);
    }
    
  }
  temp.y = point.y;
  temp.x += 1;
  
  if (0 <= temp.x && temp.x < w->GetWidth() && 0 <= temp.y && temp.y < w->GetHeight()) {
    compColor = w->GetNodeColor(temp);
    if (visColor.g != compColor.g) {
      unvisited.push_back(temp);
    }
  }
  temp.x = point.x;
  temp.y += 1;
  if (0 <= temp.x && temp.x < w->GetWidth() && 0 <= temp.y && temp.y < w->GetHeight()) {
    compColor = w->GetNodeColor(temp);
    if (visColor.g != compColor.g) {
      unvisited.push_back(temp);
    }
  }
  temp.y = point.y;
  temp.x -= 1;
  if (0 <= temp.x && temp.x < w->GetWidth() && 0 <= temp.y && temp.y < w->GetHeight()) {
    compColor = w->GetNodeColor(temp);
    if (visColor.g != compColor.g) {
      unvisited.push_back(temp);
    }
  }
  // end solution
  return unvisited;
}
