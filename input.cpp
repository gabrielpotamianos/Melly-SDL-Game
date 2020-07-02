#include "input.h"
#include <iostream>
using namespace std;

void input::update(void)
{
	while (SDL_PollEvent(&m_eventt) != NULL)
	{
		switch (m_eventt.type)
		{
			case SDL_KEYDOWN:
			{		
					SDL_Keycode keyPressed = m_eventt.key.keysym.sym;
					switch (keyPressed)
					{
					case SDLK_ESCAPE:
						m_keyPressed[KEY_ESCAPE] = true;
						break;
					case SDLK_LEFT:
						m_keyPressed[KEY_LEFT] = true;
						break;
					case SDLK_RIGHT:
						m_keyPressed[KEY_RIGHT] = true;
						break;
					case SDLK_UP:
						m_keyPressed[KEY_UP] = true;
						break;
					case SDLK_DOWN:
						m_keyPressed[KEY_DOWN] = true;
						break;
					case SDLK_e:
						m_keyPressed[KEY_E] = true;
						break;
					case SDLK_f:
						m_keyPressed[KEY_F] = true;
						break;
					case SDLK_v:
						m_keyPressed[KEY_V] = true;
						break;
					case SDLK_r:
						m_keyPressed[KEY_R] = true;
						break;
					case SDLK_g:
						m_keyPressed[KEY_G] = true;
						break;
					}
					break;
				}
			case SDL_KEYUP:
			{
				SDL_Keycode keyPressed = m_eventt.key.keysym.sym;
				switch (keyPressed)
				{
				case SDLK_ESCAPE:
					m_keyPressed[KEY_ESCAPE] = false;
					break;
				case SDLK_LEFT:
					m_keyPressed[KEY_LEFT] = false;
					break;
				case SDLK_RIGHT:
					m_keyPressed[KEY_RIGHT] = false;
					break;
				case SDLK_UP:
					m_keyPressed[KEY_UP] = false;
					break;
				case SDLK_DOWN:
					m_keyPressed[KEY_DOWN] = false;
					break;
				case SDLK_e:
					m_keyPressed[KEY_E] = false;
					break;
				case SDLK_f:
					m_keyPressed[KEY_F] = false;
					break;
				case SDLK_v:
					m_keyPressed[KEY_V] = false;
					break;
				case SDLK_r:
					m_keyPressed[KEY_R] = false;
					break;
				case SDLK_g:
					m_keyPressed[KEY_G] = false;
					break;
				}
				break;
			}
			case SDL_QUIT:
				setKey(KEY_ESCAPE, true);
				break;
			default:
			break;
		}
	}
}

bool input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_keyPressed[key];
}

void input::setKey(KEYS_PRESSED_LIST key, bool state)
{
	m_keyPressed[key]=state;
}



input::input()
{
	for (int i = 0; i < SIZE_OF_KEYS_PRESSED_ENUM; i++)
	{
		m_keyPressed[i] = false;
	}
}


input::~input()
{
}
