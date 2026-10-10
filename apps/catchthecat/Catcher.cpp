#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(CatWorld* world) {
  std::vector<Point2D> catcherPath = generatePath(world);
  Point2D newLoc;
  auto catCheck = world->getCat();
  for (;;) {
    if (!catcherPath.empty()) {
      newLoc = catcherPath.front();
      if (catCheck.x != newLoc.x && catCheck.y != newLoc.y && !world->getContent(newLoc)) {
        return newLoc;
      }
    }
  }
   
}
  /*if (!catcherPath.empty())
  {
    auto side = world->getWorldSideSize() / 2;
    for (;;) {
      Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
      auto cat = world->getCat();
      if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
    }

    
  } else {*/