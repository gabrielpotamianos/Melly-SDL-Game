#include "Entity.h"
#include <iostream>

using namespace std;

Entity::Entity()
{
	m_x = 0;
	m_y = 0;
}

Entity::Entity(SDL_Renderer * renderer, string filename)
{

	m_x = 0;
	m_y = 0;

	m_currBitmap = new Bitmap(renderer, filename, m_x, m_y, true);

}

Entity::Entity(SDL_Renderer * renderer, string filename, int x, int y, bool transparency, string name)
{
	m_x = x;
	m_y = y;
	if (!name.empty())
		m_currBitmap = new Bitmap(renderer, filename, x, y, transparency, name);
	else
		m_currBitmap = new Bitmap(renderer, filename, x, y, transparency);
}

void Entity::left()
{
	m_x--;

}

void Entity::right()
{
	m_x++;
}

void Entity::up()
{
	m_y--;
}

void Entity::down()
{
	m_y++;
}

void Entity::draw(int x, int y,bool left)
{
	if (left)
		m_currBitmap->draw(m_x, m_y, left);
	else if (x && left || y && left)
		m_currBitmap->draw(x, y, left);
	else if (x || y)
		m_currBitmap->draw(x, y);
	else
		m_currBitmap->draw(m_x, m_y);
}

int Entity::getX()
{
	return m_x;
}

int Entity::getY()
{
	return m_y;
}

SDL_Rect * Entity::getRect()
{
	return m_currBitmap->getCollider();
}

void Entity::setX(int x)
{
	m_x = x;
}

void Entity::setY(int y)
{
	m_y = y;
}

void Entity::updateBitmap()
{
	m_currBitmap->setPos(m_x, m_y);
}


Entity::~Entity()
{
	delete m_currBitmap;
	m_currBitmap = nullptr;
}
