#ifndef _Goal_H_
#define _Goal_H_

#include "SDLGameObject.h"

class Goal;

typedef Goal TheGoal;

class Goal : public SDLGameObject
{
private:
	Goal(const LoaderParams* pParams) : SDLGameObject(pParams) {}
	static Goal* s_pInstance;

public:
	static Goal* Instance(int x = 0, int y = 0, int width = 0, int height = 0, const string& textureID = "")
	{
		if (s_pInstance == 0)
			s_pInstance = new Goal(new LoaderParams(x, y, width, height, textureID));

		return s_pInstance;
	}

	void draw();
	void update() {}
	void clean() {}
};

#endif
