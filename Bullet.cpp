#include "Bullet.h"
#include "InputHandler.h"
#include "Game.h"
#include "Camera.h"
#include "CollisionManager.h"

void Bullet::moveToMouse()
{
  Vector2D* mousePos = TheInputHandler::Instance()->getMousePosition();
  
  m_velocity = *mousePos - (m_position + *new Vector2D(m_width/2, m_height/2)) + TheCamera::Instance()->getCameraMove();
  m_velocity = m_velocity / m_velocity.length() * speed;

}

void Bullet::draw()
{
  SDLGameObject::draw();
}

void Bullet::update()
{
  checkDelete();

  SDLGameObject::update();
}

void Bullet::checkDelete()
{
  int bulletLeft = m_position.getX();
  int bulletRight = bulletLeft + m_width;
  int bulletTop = m_position.getY();
  int bulletBottom = bulletTop + m_height;

  // 벽과 부딛힐 시
  for (int i = 0; i < TheGame::Instance()->getWallObjects().size(); i++)
  {
      int objectLeft = TheGame::Instance()->getWallObjects()[i]->getPosition().getX();
      int objectRight = objectLeft + TheGame::Instance()->getWallObjects()[i]->getWidth();
      int objectTop = TheGame::Instance()->getWallObjects()[i]->getPosition().getY();
      int objectBottom = objectTop + TheGame::Instance()->getWallObjects()[i]->getHeight();

      // 충돌 시
      if (TheCollisionManager::Instance()->isCollisionSquareToSquare(bulletLeft, bulletRight, bulletTop, bulletBottom,
          objectLeft, objectRight, objectTop, objectBottom))
      {
          TheGame::Instance()->deleteBulletObject(this);
      }
  }

  // 화면 밖으로 벗어날 시
  if (!TheCollisionManager::Instance()->isCollisionSquareToSquare(bulletRight, bulletLeft, bulletBottom, bulletTop,
      0, TheGame::Instance()->getWindowWidth(), TheCamera::Instance()->getCameraMove().getY(), TheGame::Instance()->getWindowHeight() + TheCamera::Instance()->getCameraMove().getY()))
  {
      TheGame::Instance()->deleteBulletObject(this);
  }
}