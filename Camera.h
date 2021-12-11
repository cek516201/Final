#ifndef _Camera_H_
#define _Camera_H_

#include "Vector2D.h"

class Camera;

typedef Camera TheCamera;

class Camera
{
private:
    Camera();
    static Camera* s_pInstance;

public:
    static Camera* Instance()
    {
        if (s_pInstance == 0)
            s_pInstance = new Camera();

        return s_pInstance;
    }

    void update();

    float getLeft() { return Left; }
    float getRight() { return Right; }
    float getTop() { return Top; }
    float getBottom() { return Bottom; }
    float getHorizontalCenter() const { return (Left + Right) / 2; }
    float getVerticalCenter() const { return (Top + Bottom) / 2; }
    Vector2D getCameraMove() const { return cameraMove; }

private:
    float Left;
    float Right;
    float Top;
    float Bottom;

    Vector2D cameraMove;
};

#endif