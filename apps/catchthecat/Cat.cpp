#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(CatWorld* world) {
  std::vector<Point2D> catPath = generatePath(world);
  Point2D newLoc;
  if (!catPath.empty())
  {
    newLoc = catPath.back();
    if (world->catCanMoveToPosition(newLoc)) 
    {
      world->lastMove = newLoc;
      return newLoc;
    }
  } else {
    return world->getCat();
  }
 
}

/*if (!catPath.empty())
  {
    auto rand = Random::Range(0, 5);
    auto pos = world->getCat();
    switch (rand) {
      case 0:
        return CatWorld::NE(pos);
      case 1:
        return CatWorld::NW(pos);
      case 2:
        return CatWorld::E(pos);
      case 3:
        return CatWorld::W(pos);
      case 4:
        return CatWorld::SW(pos);
      case 5:
        return CatWorld::SE(pos);
      default:
        throw std::runtime_error("random out of range");
    }
        
  } else {*/