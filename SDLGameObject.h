#ifndef _SDLGameObject_H_
#define _SDLGameObject_H_

#include "GameObject.h"
#include "SDL.h"

class SDLGameObject : public GameObject
{
public:
  SDLGameObject(const LoaderParams* pParams); // : GameObject(pParams)
  virtual ~SDLGameObject() {}

  void draw(SDL_RendererFlip flip = SDL_FLIP_NONE);
  void update();
  void clean() {}

  Vector2D getPosition() { return m_position; }
  int getWidth() { return m_width; }
  int getHeight() { return m_height; }

protected:
  Vector2D m_position; // :  m_position(pParams->getX(),pParams->getY())
  Vector2D m_velocity; // :  m_velocity(0, 0)
  Vector2D m_acceleration; // :  m_acceleration(0, 0)
  
  int m_width;
  int m_height;
  int m_currentRow;
  int m_currentFrame;
  string m_textureID;
};

#endif