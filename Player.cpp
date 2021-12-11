#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "CollisionManager.h"
#include "Goal.h"

Player* Player::s_pInstance = 0;

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{

}

void Player::draw()
{
  SDLGameObject::draw(flip);
}

void Player::update()
{
  handleInput();
  checkCollision();
  updateSprite();

  SDLGameObject::update();
}

void Player::handleInput()
{
    // 바닥을 딛고 있을 시
    if (onGround == true)
    {
        // 스페이스 바를 누르면
        if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
        {
            m_velocity.setX(0);

            // 눌렀을 때 1프레임
            if (temp_SPACEBAR)
            {
                temp_SPACEBAR = false;
                jumpingPower = (float)SDL_GetTicks() / 1000;
            }
        }
        // 스페이스 바를 떼면
        else
        {
            // 뗐을 때 1프레임
            if (!temp_SPACEBAR)
            {
                temp_SPACEBAR = true;

                jumpingPower = (float)SDL_GetTicks() / 1000 - jumpingPower; // 누른시간 1초당 1

                if (jumpingPower > 1)
                    jumpingPower = 1.0; // 1초가 최대

                m_velocity.setY(-7.5 * jumpingPower);
                onGround = false;
                setGravity();

                if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
                {
                    m_velocity.setX(-jumpSpeed);
                }
                else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
                {
                    m_velocity.setX(jumpSpeed);
                }
                else
                {
                    m_velocity.setX(0);
                }
            }
            else
            {
                // 버그수정용
                if (!(m_velocity.getX() == jumpSpeed) && !(m_velocity.getX() == -jumpSpeed))
                {
                    // 좌우 이동
                    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
                    {
                        m_velocity.setX(-groundSpeed);
                    }
                    else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
                    {
                        m_velocity.setX(groundSpeed);
                    }
                    else
                    {
                        m_velocity.setX(0);
                    }
                }
            }
        }
    }
    else
    {
        // 공중 감속
        m_velocity.setX(m_velocity.getX() * 0.99);
    }

    // 마우스 왼쪽 눌렀을 때 1프레임
    if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && temp_MOUSEBUTTONLEFT)
    {
        temp_MOUSEBUTTONLEFT = false;

        int bulletWidth = 20;
        int bulletHeight = 20;
        TheGame::Instance()->createBulletObject(m_position.getX() + m_width / 2 - bulletWidth / 2, m_position.getY() + m_height / 2 - bulletHeight / 2, bulletWidth, bulletHeight);
    }
    // 마우스 왼쪽 뗐을 때 1프레임
    else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && !temp_MOUSEBUTTONLEFT)
    {
        temp_MOUSEBUTTONLEFT = true;
    }
}

void Player::setGravity()
{
    m_acceleration.setY(0.15);

    if (m_velocity.getY() > 7.5)
        m_velocity.setY(7.5);
}

void Player::checkCollision()
{
    int playerLeft = m_position.getX();
    int playerRight = playerLeft + m_width;
    int playerTop = m_position.getY();
    int playerBottom = playerTop + m_height;

    int count = 0;

    //벽과 충돌 시
    for (int i = 0; i < TheGame::Instance()->getWallObjects().size(); i++)
    {
        int objectLeft = TheGame::Instance()->getWallObjects()[i]->getPosition().getX();
        int objectRight = objectLeft + TheGame::Instance()->getWallObjects()[i]->getWidth();
        int objectTop = TheGame::Instance()->getWallObjects()[i]->getPosition().getY();
        int objectBottom = objectTop + TheGame::Instance()->getWallObjects()[i]->getHeight();

        // 충돌 시
        if (TheCollisionManager::Instance()->isCollisionSquareToSquare(playerLeft, playerRight, playerTop, playerBottom,
            objectLeft, objectRight, objectTop, objectBottom))
        {
            // 아랫방향
            if (m_velocity.getY() > 0 && playerBottom >= objectTop && playerBottom <= objectTop + m_velocity.getY())
            {
                m_position.setY(objectTop - m_height);
                playerTop = m_position.getY();
                playerBottom = playerTop + m_height;

                m_velocity.setY(0);
                m_acceleration.setY(0.0);
            }
            // 윗방향
            else if (m_velocity.getY() < 0 && playerTop <= objectBottom && playerTop >= objectBottom + m_velocity.getY())
            {
                m_position.setY(objectBottom);
                playerTop = m_position.getY();
                playerBottom = playerTop + m_height;

                m_velocity.setY(0);

                if (!onGround)
                    m_velocity.setX(m_velocity.getX() * 1 / 2);
            }

            // 왼방향
            if (m_velocity.getX() < 0 && playerLeft <= objectRight && playerLeft > objectLeft && playerTop != objectBottom && playerBottom != objectTop)
            {
                m_position.setX(objectRight);

                horizontalCollision();
            }
            // 오른방향
            else if (m_velocity.getX() > 0 && playerRight >= objectLeft && playerRight < objectRight && playerTop != objectBottom && playerBottom != objectTop)
            {
                m_position.setX(objectLeft - m_width);

                horizontalCollision();
            }

            // 바닥을 딛고 있을 시
            if (playerBottom == objectTop)
            {
                count++;
                onGround = true;
            }
        }
    }

    // 바닥을 딛고있지 않을 시
    if (count == 0)
    {
        setGravity();
        onGround = false;
    }

    // 골과 충돌 시
    if (TheCollisionManager::Instance()->isCollisionSquareToSquare(playerLeft, playerRight, playerTop, playerBottom,
        TheGoal::Instance()->getPosition().getX(), TheGoal::Instance()->getPosition().getX() + TheGoal::Instance()->getWidth(), TheGoal::Instance()->getPosition().getY(), TheGoal::Instance()->getPosition().getY() + TheGoal::Instance()->getHeight()))
    {
        TheGame::Instance()->quit();
    }

    // 카메라 좌우측 충돌
    if (m_velocity.getX() < 0 && TheCollisionManager::Instance()->isCollisionSquareToVerticalLine(playerLeft, playerRight, TheCamera::Instance()->getLeft()))
    {
        m_position.setX(0);

        horizontalCollision();
    }
    else if (m_velocity.getX() > 0 && TheCollisionManager::Instance()->isCollisionSquareToVerticalLine(playerLeft, playerRight, TheCamera::Instance()->getRight()))
    {
        m_position.setX(TheGame::Instance()->getWindowWidth() - m_width);

        horizontalCollision();
    }
}

void Player::horizontalCollision()
{
    if (onGround)
        m_velocity.setX(0);
    else
        m_velocity.setX(m_velocity.getX() * -1 / 2);
}
void Player::updateSprite()
{
  if(m_velocity.getX() < 0)
  {
    m_currentFrame = (frameCount++ / 6 + 1) % 6;
    flip = SDL_FLIP_HORIZONTAL;
  }
  else if(m_velocity.getX() > 0)
  {
    m_currentFrame = (frameCount++ / 6 + 1) % 6;
    flip = SDL_FLIP_NONE;
  }
  else
  {
    m_currentFrame = 0;
    frameCount = 0;
  }
}