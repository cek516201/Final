#ifndef _Player_H_
#define _Player_H_

#include "SDLGameObject.h"

class Player;

typedef Player ThePlayer;

class Player : public SDLGameObject
{
private:
	Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}
	static Player* s_pInstance;

public:
	static Player* Instance(int x = 0, int y = 0, int width = 0, int height = 0, const string& textureID = "")
	{
		if (s_pInstance == 0)
			s_pInstance = new Player(new LoaderParams(x, y, width, height, textureID));

		return s_pInstance;
	}

  void draw();
  void update();
	void handleInput();
		void setGravity();
	void checkCollision();
		void horizontalCollision();
		//void setGravity();
	void updateSprite();
  void clean() {}

private:
  const float groundSpeed = 2.0;
  const float jumpSpeed = 4.0;
  float jumpingPower = 0.0;
  SDL_RendererFlip flip = SDL_FLIP_NONE;

  int frameCount = 0;

  bool temp_SPACEBAR = true; // 스페이스 바를 눌렀을 때 한번만 실행시키기 위한 보조값
  bool temp_MOUSEBUTTONLEFT = true; // 마우스 왼쪽을 눌렀을 때 한번만 실행시키기 위한 보조값

  bool onGround = false;
};

#endif