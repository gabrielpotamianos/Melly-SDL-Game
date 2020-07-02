#include "Hero.h"
#include "SDL.h"
using namespace std;

Hero::Hero(SDL_Renderer * renderer, string filename)
{
	m_renderer = renderer;

	m_x = 0;
	m_y = 0;
	m_currFrame = 0;
	m_currJump = 0;
	m_currBitmap = new Bitmap(renderer, filename, m_x, m_y, true);
	m_pAnimations.push_back(m_currBitmap);

}

Hero::Hero(SDL_Renderer* renderer, string filename, int x, int y, bool transparency)
{
	m_renderer = renderer;

	m_x = x;
	m_y = y;
	m_currFrame = 0;
	m_currJump = 0;
	m_currBitmap = new Bitmap(renderer, filename, x,y,transparency);
	m_pAnimations.push_back(m_currBitmap);
}

void Hero::left()
{
	if (getLastFrame() != WALK)
	{
		setCurrFrame(IDLE);
		setLastFrame(WALK);
	}
	m_x--;
	m_currFrame++;

}

void Hero::right()
{
	if (getLastFrame() != WALK)
	{
		setCurrFrame(IDLE);
		setLastFrame(WALK);
	}
	m_x++;
	m_currFrame++;

}

void Hero::up()
{
	m_y -= 2;
}

void Hero::down()
{
	m_y += 2;
}



void Hero::dead()
{
	m_currFrame++;
}


void Hero::jump()
{

	if (getLastFrame() != JUMP && getLastFrame()!=FALL)
	{
		if(m_currJump<=0)
			is_Jumping = true;

		setCurrFrame(JUMP);
		setLastFrame(JUMP);
	}

	if(m_currJump<m_maxJump&& is_Jumping)
	{
		up();
		m_currJump++;

		if (m_currJump > m_maxJump)
			m_currJump = m_maxJump;
	}
	if (m_currJump == m_maxJump)
		is_Jumping = false;
}

void Hero::fall()
{
	if (m_currJump == m_maxJump)
		is_Jumping = false;

	if (getLastFrame() != FALL)
	{
		setCurrFrame(FALL);
		setLastFrame(FALL);
	}
	if(m_currJump>0)
		m_currJump--;
	down();
}


void Hero::draw(bool left)
{
	if (left && !m_pAnimations[m_currFrame]->pixelsFlipped)
		m_pAnimations[m_currFrame]->flipPixels();

	if (!left&&m_pAnimations[m_currFrame]->pixelsFlipped)
		m_pAnimations[m_currFrame]->flipPixels();

	if (m_currFrame > m_lastFrame)
		m_currFrame = m_initFrame;
	if (m_currFrame <= m_lastFrame)
	{
		if (left)
			m_pAnimations[m_currFrame]->draw(m_x, m_y, left);
		else
			m_pAnimations[m_currFrame]->draw(m_x, m_y);

	}	

	//DO NOT FORGET TO DELETE THE ATTACK OBJ
}



Bitmap * Hero::getCurrAnimation()
{
	return m_pAnimations[m_currFrame];
}



SDL_Rect * Hero::getRect()
{
	return m_pAnimations[m_currFrame]->getCollider();
}

bool Hero::getJumpState()
{
	return is_Jumping;
}

int Hero::getCurrJump()
{
	return m_currJump;
}

void Hero::setCurrJump(int jump)
{
	m_currJump = jump;
 }

void Hero::setJumpState(bool state)
{
	 is_Jumping=state;
}


void Hero::addFrame(SDL_Renderer * renderer, string filename, int x, int y, bool transparency, string name)
{
	if (!x || !y)
	{
		m_currBitmap = new Bitmap(renderer, filename, m_x, m_y, true);
	}
	else
		m_currBitmap = new Bitmap(renderer, filename, x, y, transparency, name);
	m_pAnimations.push_back(m_currBitmap);

}

void Hero::setCurrFrame(int frame)
{
	m_currFrame = frame;
	m_initFrame = frame;
}

void Hero::setLastFrame(int frame)
{
	m_lastFrame = frame;
}

int Hero::getCurrFrame()
{
	return m_currFrame;
}

int Hero::getLastFrame()
{
	return m_lastFrame;
}

Hero::~Hero()
{
	m_currBitmap = nullptr;
	for (int i = 0; i < m_pAnimations.size(); i++)
	{
		delete m_pAnimations[i];
		m_pAnimations[i] = nullptr;
	}

	if (m_currBitmap)
		delete m_currBitmap;

	if (m_renderer)
	{
		m_renderer = nullptr;
		delete m_renderer;
	}

}

