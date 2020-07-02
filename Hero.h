#pragma once
#include "Entity.h"
#include <string>
#include <vector>
#include "SDL_rect.h"
using namespace std;

enum HERO {
	IDLE = 1, WALK = 5, JUMP, FALL, HURT = 10, DEAD = 14, ATTACK
};

class Hero :
	public Entity
{
private:
	//Animation tools
	vector<Bitmap*>   m_pAnimations;
	int m_currFrame, m_lastFrame, m_initFrame;
	int m_currJump, m_maxJump = 30 ;
	bool is_Jumping=false;
	bool temporary = false;

	SDL_Renderer* m_renderer;
public:

	//constructors
	Hero(SDL_Renderer* renderer, string filename);
	Hero(SDL_Renderer* renderer, string filename, int x, int y, bool transparency = false);

	//functions
	void left();
	void right();
	void up();
	void down();

	//action functions
	void jump();
	void fall();
	void dead();

	// getters
	int  getCurrFrame();
	int  getLastFrame();
	bool getJumpState();
	int  getCurrJump();
	SDL_Rect* getRect();
	Bitmap* getCurrAnimation();

	//draw
	void draw(bool left);

	//setters
	void setCurrJump(int jump);
	void setJumpState(bool state);


	//Frames functions
	void addFrame(SDL_Renderer* renderer, string filename, int x = 0, int y = 0, bool transparency = false, string name = string());
	void setCurrFrame(int frame);
	void setLastFrame(int frame);



	//destructors
	~Hero();
};
