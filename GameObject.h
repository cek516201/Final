#ifndef _GameObject_H_
#define _GameObject_H_

#include "Vector2D.h"
#include "LoaderParams.h"

class GameObject
{
public:
  virtual ~GameObject() {}
  
  virtual void draw() = 0;
  virtual void update() = 0;
  virtual void clean() = 0;

  virtual Vector2D getPosition() = 0;
  virtual int getWidth() = 0;
  virtual int getHeight() = 0;

protected:
  GameObject(const LoaderParams* pParams) {}
};

#endif