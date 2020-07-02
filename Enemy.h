#pragma once
#include "Entity.h"
#include <string>
#include <vector>
#include "SDL_rect.h"

using namespace std;

enum ENEMY {
	patrol=3
};


class Enemy :
	public Entity
{
private:
	//containers
	vector<Bitmap*>   m_pAnimations;

	//variables
	int m_currFrame, m_lastFrame, m_initFrame;
	bool leftSided = false;

public:
	//constructors
	Enemy();
	Enemy(SDL_Renderer* renderer, string filename);
	Enemy(SDL_Renderer* renderer, string filename, int x, int y, bool transparency = false, string name = string());

	SDL_Rect* getRect();

	void left();
	void right();
	void up();
	void down();
	void dead();

	void draw(bool left, int x=0,int y=0);
	void updateBitmap();

	//Frames functions
	void addFrame(SDL_Renderer* renderer, string filename, int x = 0, int y = 0, bool transparency = false,string name=string());
	void setCurrFrame(int frame);
	void setLastFrame(int frame);
	void setLeftFacingSide(bool left);
	Bitmap* getCurrAnimation();

	int getCurrFrame();
	int getLastFrame();
	bool getLeftFacingSide();

	~Enemy();
};

