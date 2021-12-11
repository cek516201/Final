#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = 0;

bool CollisionManager::isCollisionSquareToSquare(int obj1Left, int obj1Right, int obj1Top, int obj1Bottom, int obj2Left, int obj2Right, int obj2Top, int obj2Bottom)
{
	if (obj1Left <= obj2Right && obj1Right >= obj2Left && obj1Top <= obj2Bottom && obj1Bottom >= obj2Top)
		return true;

	return false;
}

bool CollisionManager::isCollisionSquareToVerticalLine(int objLeft, int objRight, int LineX)
{
	if (objLeft <= LineX && objRight >= LineX)
		return true;

	return false;
}