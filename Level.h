#pragma once
#include "SDL.h"
#include <vector>
#include <string>
#include "Bitmap.h"
#include "Entity.h"
#include "Enemy.h"
#include <fstream>
using namespace std;

class Level
{
private:
	ifstream read;
	vector<string> level;
	vector<Enemy*> monsters;

	Enemy* monster;
	int m_blockWidth, m_blockHeight,lvl_x,lvl_y,levelColumns, monsterNO=0;
	bool left = true;

public:
	//variables
	vector<Bitmap*> solidObjects;

	//constructors
	Level();
	Level(SDL_Renderer* renderer,int x, int y);

	//functions
	void loadLevel(SDL_Renderer * m_renderer,int index,int x,int y);
	void levelDraw();
	void monsterPatrol();
	//destructors
	~Level();
};

