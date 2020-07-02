#include "Enemy.h"



Enemy::Enemy()
{
	m_x = 0;
	m_y = 0;
	m_currFrame = 0;
}

Enemy::Enemy(SDL_Renderer * renderer, string filename)
{
	m_x = 0;
	m_y = 0;
	m_currFrame = 0;

	m_currBitmap = new Bitmap(renderer, filename, m_x, m_y, true);
	m_pAnimations.push_back(m_currBitmap);

}

Enemy::Enemy(SDL_Renderer * renderer, string filename, int x, int y, bool transparency,string name)
{
	m_x = x;
	m_y = y;
	m_currFrame = 0;

	m_currBitmap = new Bitmap(renderer, filename, x, y, transparency,name);
	m_pAnimations.push_back(m_currBitmap);

}

SDL_Rect * Enemy::getRect()
{
	return m_pAnimations[m_currFrame]->getCollider();
}

void Enemy::left()
{
	if (getLastFrame() != patrol)
	{
		setCurrFrame(0);
		setLastFrame(patrol);
	}
	m_x--;
	m_currFrame++;

}

void Enemy::right()
{
	if (getLastFrame() != patrol)
	{
		setCurrFrame(0);
		setLastFrame(patrol);
	}
	m_x++;
	m_currFrame++;

}

void Enemy::up()
{
	m_y -=2;
}

void Enemy::down()
{
	m_y+=2;
}

void Enemy::dead()
{
	m_currFrame++;
}

void Enemy::draw(bool left,int x, int y)
{
	if (m_currFrame > m_lastFrame)
		m_currFrame = m_initFrame;
	if (m_currFrame <= m_lastFrame)
	{
		if (x || y)
		{
			if (left)
				m_pAnimations[m_currFrame]->draw(x, y, left);
			else
				m_pAnimations[m_currFrame]->draw(x, y);
		}
		else
		{
			if (left)
				m_pAnimations[m_currFrame]->draw(m_x, m_y, left);
			else
				m_pAnimations[m_currFrame]->draw(m_x, m_y);

		}
	}


}

void Enemy::updateBitmap()
{
	if (m_currFrame > m_lastFrame)
		m_currFrame = m_initFrame;
	m_pAnimations[m_currFrame]->setPos(m_x, m_y);
}

void Enemy::addFrame(SDL_Renderer * renderer, string filename, int x, int y, bool transparency,string name)
{
	if (!x || !y)
	{
		m_currBitmap = new Bitmap(renderer, filename, m_x, m_y, true);
	}
	else
		m_currBitmap = new Bitmap(renderer, filename, x, y, transparency,name);
	m_pAnimations.push_back(m_currBitmap);
}

int Enemy::getCurrFrame()
{
	return m_currFrame;
}

int Enemy::getLastFrame()
{
	return m_lastFrame;
}

bool Enemy::getLeftFacingSide()
{
	return leftSided;
}

void Enemy::setCurrFrame(int frame)
{
	m_currFrame = frame;
	m_initFrame = frame;
}

void Enemy::setLastFrame(int frame)
{
	m_lastFrame = frame;
}

void Enemy::setLeftFacingSide(bool left)
{
	leftSided = left;
}

Bitmap * Enemy::getCurrAnimation()
{
	return m_pAnimations[m_currFrame];
}


Enemy::~Enemy()
{	
	m_currBitmap = nullptr;
	
	for (int i = 0; i < m_pAnimations.size(); i++)
	{
		delete m_pAnimations[i];
		m_pAnimations[i] = nullptr;
	}

	delete m_currBitmap;
}
