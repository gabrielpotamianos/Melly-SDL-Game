#pragma once
#include <string>
#include "SDL_rect.h"
#include <vector>

using namespace std;

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
class Bitmap;
 
class Bitmap
{
private:

	//SDL variables
	SDL_Surface*   m_pbitmapSurface;
	SDL_Texture*   m_pbitmapTexture;
	SDL_Renderer*  m_pRenderer;
	SDL_Rect*      m_collider= new SDL_Rect();

	//variables
	int  m_x, m_y;
	string name;

	//convert pixels regardless their type
	Uint32 getpixel(SDL_Surface *surface, int x, int y);

public:
	//store pixels 
	vector<vector<bool>> pixels;

	//if sprite is flipped whether not
	bool pixelsFlipped = false;

	//contructors
	Bitmap();
	Bitmap(SDL_Renderer* renderer, std::string fileName,int x, int y, bool useTransparency = false,string name= string());
	
	//destructors
	~Bitmap();

	//functions
	void draw(int x=0, int y=0, bool left = 0);
	void setPos(int x, int y);
	void getPixels(vector<vector<bool>> &pxl,string filename);
	void flipPixels();
	void displayPixels();
	string getName();
	SDL_Rect* getCollider();
	


};

