#pragma once
#include "input.h"
#include "SDL.h"
#include "Timer.h"
#include "Level.h"
#include <list>
#include "Hero.h"
#include "Entity.h"
#include <algorithm>
using namespace std;

class GameCore
{
private:

	//SDL variables
	SDL_Window*       m_pWindow;
	SDL_Renderer*     m_pRenderer;
	SDL_Texture*      m_pTexture;

	//variables
	Hero* m_pHero;
	Timer * m_timer=new Timer();
	input* inp = new input();
	Level* m_level;
	Bitmap* background;

	int levelIndex = 1;
	bool left = false;
	bool leftAvail = true;
	bool rightAvail = true;
	bool upAvail = true;



public:
	GameCore();
	
	//functions
	void draw(bool left = 0);
	void gameLoop();
	void checkBoundery();

	bool checkCollision(vector<Bitmap*> a, Bitmap* hero, int left = 0, int right = 0, int down = 0, int up = 0,bool ignoreMonster=false);
	
	~GameCore();
};

