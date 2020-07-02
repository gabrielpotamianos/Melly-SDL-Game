#include "Level.h"
#include <iostream>

using namespace std;

Level::Level()
{
}

Level::Level(SDL_Renderer * renderer, int x, int y)
{
	loadLevel(renderer,1,x,y);
}

void Level::loadLevel(SDL_Renderer * m_renderer,int index,int x,int y)
{
	switch (index)
	{
	case 1:
	{
		//desiging level
		level.clear();
		solidObjects.clear();

		if(monsterNO>1)
			monsters.clear();
		else {
			monster = nullptr;
		}
		monsterNO = 0;

		read.open("level.txt");
		if (read.is_open())
		{
			string row;
			while (getline(read, row))
				level.push_back(row);
			read.close();
		}
		else std::cout << "unable to open the file " << endl;
		//SET LEVEL COLUMNS
		levelColumns = 25;



		lvl_x = x;
		lvl_y = y;

		m_blockHeight = 20;
		m_blockWidth = 20;

		for (int i = 0; i < level.size(); i++)
			for (int j = 0; j < levelColumns; j++)
			{
				if (level[i][j] == 'w')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/forest/midTile.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true);
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;
				}
				else if (level[i][j] == 'l')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/forest/leftTile.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true);
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;
				}
				else if (level[i][j] == 'r')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/forest/rightTile.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true);
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;
				}
				else if (level[i][j] == 'm')
				{
					monsterNO++;
					if (monsterNO == 2)
						monsters.push_back(monster);
					monster = new Enemy(m_renderer, "assets/monsterWalk1.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");
					monster->draw(left);
					solidObjects.push_back(monster->getCurrAnimation());

					monster->addFrame(m_renderer, "assets/monsterWalk2.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");
					monster->addFrame(m_renderer, "assets/monsterWalk3.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");
					monster->addFrame(m_renderer, "assets/monsterWalk4.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");

					if (monsterNO >= 2)
						monsters.push_back(monster);
				}
				else if (level[i][j] == 'd')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/door.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true,"door");
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;

				}
			}

		break;
	}
	case 2:
	{
		//desiging level
		level.clear();
		solidObjects.clear();
		if (monsterNO > 1)
			monsters.clear();
		else monster = nullptr;
		monsterNO = 0;

		read.open("level2.txt");
		if (read.is_open())
		{
			string row;
			while (getline(read, row))
				level.push_back(row);
			read.close();
		}
		else std::cout << "unable to open the file " << endl;
		//SET LEVEL COLUMNS
		levelColumns = 25;



		lvl_x = x;
		lvl_y = y;

		m_blockHeight = 20;
		m_blockWidth = 20;

		for (int i = 0; i < level.size(); i++)
			for (int j = 0; j < levelColumns; j++)
			{
				if (level[i][j] == 'w')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/forest/midTile.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true);
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;
				}
				else if (level[i][j] == 'l')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/forest/leftTile.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true);
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;
				}
				else if (level[i][j] == 'r')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/forest/rightTile.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true);
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;
				}
				else if (level[i][j] == 'm')
				{
					monsterNO++;
					if (monsterNO == 2)
						monsters.push_back(monster);
					monster = new Enemy(m_renderer, "assets/monsterWalk1.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");
					monster->draw(left);
					solidObjects.push_back(monster->getCurrAnimation());

					monster->addFrame(m_renderer, "assets/monsterWalk2.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");
					monster->addFrame(m_renderer, "assets/monsterWalk3.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");
					monster->addFrame(m_renderer, "assets/monsterWalk4.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");

					if (monsterNO >= 2)
						monsters.push_back(monster);
				}
				else if (level[i][j] == 'd')
				{
					SDL_ClearError();
					Bitmap* temp = new Bitmap(m_renderer, "assets/door.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true,"door");
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;

				}
			}

		break;
	}
	case 3:
	{
		//desiging level
		level.clear();
		solidObjects.clear();
		if (monsterNO > 1)
			monsters.clear();
		else monster = nullptr;

		monsterNO = 0;
		read.open("level3.txt");
		if (read.is_open())
		{
			string row;
			while (getline(read, row))
				level.push_back(row);
			read.close();
		}
		else std::cout << "unable to open the file " << endl;
		//SET LEVEL COLUMNS
		levelColumns = 25;



		lvl_x = x;
		lvl_y = y;

		m_blockHeight = 20;
		m_blockWidth = 20;

		for (int i = 0; i < level.size(); i++)
			for (int j = 0; j < levelColumns; j++)
			{
				if (level[i][j] == 'w')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/forest/midTile.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true);
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;
				}
				else if (level[i][j] == 'l')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/forest/leftTile.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true);
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;
				}
				else if (level[i][j] == 'r')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/forest/rightTile.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true);
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;
				}
				else if (level[i][j] == 'm')
				{
					monsterNO++;
					if (monsterNO == 2)
						monsters.push_back(monster);
					monster = new Enemy(m_renderer, "assets/monsterWalk1.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");
					monster->draw(left);
					solidObjects.push_back(monster->getCurrAnimation());

					monster->addFrame(m_renderer, "assets/monsterWalk2.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");
					monster->addFrame(m_renderer, "assets/monsterWalk3.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");
					monster->addFrame(m_renderer, "assets/monsterWalk4.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true, "monster");

					if (monsterNO >= 2)
						monsters.push_back(monster);
				}
				else if (level[i][j] == 'd')
				{
					Bitmap* temp = new Bitmap(m_renderer, "assets/door.bmp", lvl_x + m_blockWidth * j, lvl_y + m_blockHeight * i, true,"door");
					temp->draw();
					solidObjects.push_back(temp);
					temp = nullptr;
					delete temp;

				}
			}

		break;
	}
	default:
		break;
	}
}

void Level::levelDraw()
{
	int index = 0;
	if (monsterNO > 0)
	{
		for (auto& i : solidObjects)
		{
			if (i->getName() == "monster")
			{
				if (monsterNO >= 2)
				{
					monsters[index]->draw(monsters[index]->getLeftFacingSide());
					index++;
				}
				else if (monsterNO < 2)
				{
					monster->draw(monster->getLeftFacingSide());
				}
			}
			else	i->draw();
		}
	}
	else
		for (auto & i : solidObjects)
			i->draw();
}

void Level::monsterPatrol()
{
	if (monsterNO > 0)
	{
		if (monsterNO >= 2)
		{
			for (auto i : monsters)
			{
				// because the monster width is doubled comparing to the tile one
				if (level[i->getY() / m_blockHeight + 1][i->getX() / m_blockWidth + 2] == '.')
					i->setLeftFacingSide(true);
				else if (level[i->getY() / m_blockHeight + 1][i->getX() / m_blockWidth] == '.')
					i->setLeftFacingSide(false);
				if (i->getLeftFacingSide())
					i->left();
				else i->right();
				i->updateBitmap();
			}
		}
		else if (monsterNO < 2)
		{
			if (level[monster->getY() / m_blockHeight + 1][monster->getX() / m_blockWidth + 2] == '.')
				monster->setLeftFacingSide(true);
			else if (level[monster->getY() / m_blockHeight + 1][monster->getX() / m_blockWidth] == '.')
				monster->setLeftFacingSide(false);
			if (monster->getLeftFacingSide())
				monster->left();
			else monster->right();
			monster->updateBitmap();

		}
	}
}


Level::~Level()
{

	level.clear();
	solidObjects.clear();
	if (monsterNO >= 2)
	{
		for (auto i : monsters)
		{
			delete i;
			i = nullptr;
		} 
		monsters.clear();
	}
	else {
		delete monster;
		monster = nullptr;

	}
}
