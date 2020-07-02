#pragma once
#include "SDL.h"

//Global Vars
enum KEYS_PRESSED_LIST
{
	KEY_LEFT,KEY_RIGHT,KEY_UP,KEY_DOWN,
	KEY_E,KEY_F,KEY_V,
	KEY_ESCAPE,KEY_R,KEY_G,KEY_B,SIZE_OF_KEYS_PRESSED_ENUM
};

class input
{
public:
	//functions
	void update(void);
	void setKey(KEYS_PRESSED_LIST key, bool state);
	bool KeyIsPressed(KEYS_PRESSED_LIST key);
	
	//constructors
	input();
	
	//destructors
	~input();

private:
	//SDL variables
	SDL_Event m_eventt;

	//variables
	bool      m_keyPressed[SIZE_OF_KEYS_PRESSED_ENUM];
};

