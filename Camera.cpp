#include "Camera.h"
#include "Game.h"
#include "Player.h"
#include "Background.h"

Camera* Camera::s_pInstance = 0;

Camera::Camera() : cameraMove(0, 0)
{
	Left = 0;
	Right = Left + TheGame::Instance()->getWindowWidth();
	Top = TheBackground::Instance()->getHeight() - TheGame::Instance()->getWindowHeight();
	Bottom = Top + TheGame::Instance()->getWindowHeight();
}

void Camera::update()
{
	//Left += (ThePlayer::Instance()->getPosition().getX() + ThePlayer::Instance()->getWidth() / 2 - getHorizontalCenter()) / 100;
	//Right = Left + TheGame::Instance()->getWindowWidth();;

	//cameraMove.setX(getHorizontalCenter() - TheGame::Instance()->getWindowHeight()/2);

	Top += (ThePlayer::Instance()->getPosition().getY()+ThePlayer::Instance()->getHeight()/2 - getVerticalCenter() - TheGame::Instance()->getWindowHeight()/4) / 25;
	Bottom = Top + TheGame::Instance()->getWindowHeight();

	cameraMove.setY(getVerticalCenter() - TheGame::Instance()->getWindowHeight()/2);
}