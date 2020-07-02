#pragma once
#include "Bitmap.h"
#include <string>
#include <vector>

using namespace std;

class Entity
{
protected:
	
	//variables
	int               m_x, m_y;

public:
	Bitmap*           m_currBitmap;

	//constructors
	Entity();
	Entity(SDL_Renderer* renderer, string filename);
	Entity(SDL_Renderer* renderer, string filename, int x, int y, bool transparency = false, string name=string());

	//functions

	int getX();
	int getY();
	virtual SDL_Rect* getRect();

	void setX(int x);
	void setY(int y);
	void updateBitmap();

	virtual void draw(int x=0,int y=0,bool left=false);	
	
	virtual void left();
	virtual void right();
	virtual void up();
	virtual void down();


	//destructors
	~Entity();
};

