#ifndef _Wall_H_
#define _Wall_H_

#include "SDLGameObject.h"

class Wall : public SDLGameObject
{
public:
  Wall(const LoaderParams* pParams) : SDLGameObject(pParams) {}

  void draw();
  void update() {}
  void clean() {}
};

#endif