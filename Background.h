#ifndef _Background_H_
#define _Background_H_

#include "SDLGameObject.h"

class Background;

typedef Background TheBackground;

class Background : public SDLGameObject
{
private:
	Background(const LoaderParams* pParams) : SDLGameObject(pParams) {}
	static Background* s_pInstance;

public:
	static Background* Instance(int x = 0, int y = 0, int width = 0, int height = 0, const string& textureID = "")
	{
		if (s_pInstance == 0)
			s_pInstance = new Background(new LoaderParams(x, y, width, height, textureID));

		return s_pInstance;
	}

	void draw();
	void update() {}
	void clean() {}
};

#endif