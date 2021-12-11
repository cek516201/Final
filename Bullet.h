#ifndef _Bullet_H_
#define _Bullet_H_

#include "SDLGameObject.h"

class Bullet : public SDLGameObject
{
public:
  Bullet(const LoaderParams* pParams) : SDLGameObject(pParams)
  {
    moveToMouse();
  }
  void moveToMouse();

  void draw();
  void update();
    void checkDelete();
  void clean() {}

  private:
    const float speed = 5.0;
};

#endif