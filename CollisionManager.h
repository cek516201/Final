#ifndef _CollisionManager_H_
#define _CollisionManager_H_

class CollisionManager;

typedef CollisionManager TheCollisionManager;

class CollisionManager
{
private:
    CollisionManager() {}
    static CollisionManager* s_pInstance;

public:
    static CollisionManager* Instance()
    {
        if (s_pInstance == 0)
            s_pInstance = new CollisionManager();

        return s_pInstance;
    }

    // 사각형과 사각형 사이의 충돌
    bool isCollisionSquareToSquare(int obj1Left, int obj1Right, int obj1Top, int obj1Bottom, int obj2Left, int obj2Right, int obj2Top, int obj2Bottom);

    // 사각형과 수직 선 사이의 충돌
    bool isCollisionSquareToVerticalLine(int objLeft, int objRight, int LineX);
};

#endif