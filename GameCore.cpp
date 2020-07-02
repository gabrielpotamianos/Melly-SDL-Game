#include "GameCore.h"
#include <stdio.h>
#include <iostream>

GameCore::GameCore()
{
	//default values
	m_pWindow = nullptr;
	m_pRenderer = nullptr;

	//window init
	m_pWindow = SDL_CreateWindow(
		"AE2 Assessment",				//title
		200,							//X coord
		150,							//Y coord
		512,							//Width, pixels
		256,							//Height, piexels
		0								//flag
	);
	
	if (!m_pWindow)
		printf(" WINDOW ERROR ! %s\n", SDL_GetError());

	//renderer
	m_pRenderer = SDL_CreateRenderer(
		m_pWindow,						//window reference
		-1,								//render driver
		0								//flag
	);
	if (!m_pRenderer)
		printf(" RENDERER ERROR ! %s\n", SDL_GetError());


	m_pHero = new Hero(m_pRenderer, "assets/idle1.bmp",20,150,true);
	m_pHero->addFrame(m_pRenderer, "assets/idle2.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/walk1.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/walk2.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/walk3.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/walk4.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/jump.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/fall.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/hurt1.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/hurt2.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/hurt3.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/dead1.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/dead2.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/dead3.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/dead4.bmp");
	m_pHero->addFrame(m_pRenderer, "assets/attack.bmp");
	background = new Bitmap(m_pRenderer, "assets/background.bmp", 0, 0, false);

	m_level = new Level(m_pRenderer, 00, 0);

}

void GameCore::draw(bool left)
{
	//set colour to clear the screen (not necesarry when background images included)
	SDL_SetRenderDrawColor(
		m_pRenderer,
		0,
		0,
		0,
		255
	);

	//clear the renderer
	SDL_RenderClear(m_pRenderer);
	background->draw();
	//draw on the renderer
	m_pHero->draw(left);
	m_level->levelDraw();

	//display on the screen the renderer
	SDL_RenderPresent(m_pRenderer);
}

void GameCore::gameLoop()
{
	float inputLimit = 0;
	bool noInput = true;
	bool jump = true;
	bool gravity = true;


	while (!inp->KeyIsPressed(KEY_ESCAPE) )
	{
		inputLimit += .1f;
		//starting timer for capping frames
		m_timer->startTimer();

		//get input
		inp->update();

		//limitating input due to its rapidity
		if (inputLimit > .05f)
		{
			checkBoundery();

			if (gravity)
			{	//first appy gravity if the case
				if (!checkCollision(m_level->solidObjects, m_pHero->getCurrAnimation(), 0, 0, +1, 0) && !m_pHero->getJumpState())
				{
						m_pHero->fall();
						m_pHero->setCurrJump(1);
						rightAvail = true;
						leftAvail = true;

				}

				//falling to the right (push to the left)
				else if (!left && checkCollision(m_level->solidObjects, m_pHero->getCurrAnimation(), 0, 2, 0, 0) && !checkCollision(m_level->solidObjects, m_pHero->getCurrAnimation(), -2, 0, 1, 0))
				{
					rightAvail = false;
					leftAvail = true;
					m_pHero->left();
				}

				//falling to the left (push to the right)
				else  if (left && checkCollision(m_level->solidObjects, m_pHero->getCurrAnimation(), -2, 0, 0, 0) && !checkCollision(m_level->solidObjects, m_pHero->getCurrAnimation(), 0, 2, 1, 0))
				{
					rightAvail = true;
					leftAvail = false;
					m_pHero->right();
				}

				//on the ground
				else if (checkCollision(m_level->solidObjects, m_pHero->getCurrAnimation(), 0, 0, +1, 0) && !m_pHero->getJumpState())
				{

					m_pHero->setCurrJump(0);
					jump = true;
					upAvail = true;
				}
			}
			//walk left
			if (inp->KeyIsPressed(KEY_LEFT)&& leftAvail)
			{
				if (!left) 
					m_pHero->setX(m_pHero->getX() - 4);
				else if (!checkCollision(m_level->solidObjects, m_pHero->getCurrAnimation(), 0, -1, -2, 0))
					m_pHero->left();

				rightAvail = true;
				left = true;
				noInput = false;

			}

			//walk right
			else if (inp->KeyIsPressed(KEY_RIGHT)&& rightAvail)
			{
				if (left) 
					m_pHero->setX(m_pHero->getX() + 4);

				else if (!checkCollision(m_level->solidObjects, m_pHero->getCurrAnimation(), 0, +1, -2, 0))
					m_pHero->right();	
				leftAvail = true;
				left = false;
				noInput = false;


			}

			//as long as he hasnt reached the max jump continue jumping +platforms
			if (inp->KeyIsPressed(KEY_UP) && upAvail || m_pHero->getJumpState() && upAvail)
			{
				//check if it is a platform by checking 60 pixels above + curr jump
				if(!checkCollision(m_level->solidObjects, m_pHero->getCurrAnimation(), 0, 0, -60+m_pHero->getCurrJump(), 0, true) )
				{
					m_pHero->jump();
					rightAvail = true;
					leftAvail = true;

				}
				else if (!checkCollision(m_level->solidObjects, m_pHero->getCurrAnimation(), 0, 0, -3, 0,true) && jump)
					m_pHero->jump();
				else {
					m_pHero->setCurrJump(30);
					m_pHero->setJumpState(false);

				}

				noInput = false;
			}

			//dead  HAS TO BE A EVEN NUMBER
			if (m_pHero->getY()== (SDL_GetWindowSurface(m_pWindow)->h - m_pHero->getCurrAnimation()->getCollider()->h) || inp->KeyIsPressed(KEY_R))
			{
				if (m_pHero->getLastFrame() != DEAD)
				{
					m_pHero->setCurrFrame(HURT);
					m_pHero->setLastFrame(DEAD);
				}
				if (m_pHero->getCurrFrame() < DEAD)
					m_pHero->dead();
				if (m_pHero->getCurrFrame() == DEAD)
					inp->setKey(KEY_ESCAPE, true);
				gravity = false;
			}

			inputLimit = 0;
			m_level->monsterPatrol();

		}
		//drawing
		draw(left);

		//capping frames to 60(approximately)
		m_timer->capeFPS();
		noInput = true;

	}
}

void GameCore::checkBoundery()
{
	if (SDL_GetWindowSurface(m_pWindow)->w - m_pHero->getCurrAnimation()->getCollider()->w <= m_pHero->getX())
	{
		rightAvail = false;
		leftAvail = true;
		m_pHero->setX(SDL_GetWindowSurface(m_pWindow)->w - m_pHero->getCurrAnimation()->getCollider()->w);
	}
	if (m_pHero->getCurrAnimation()->getCollider()->x < 0)
	{
		leftAvail = false;
		rightAvail = true;
		m_pHero->setX(0);
	}
	if (m_pHero->getCurrAnimation()->getCollider()->y < -4)
	{
		upAvail = false;
		m_pHero->setCurrJump(30);
		m_pHero->setJumpState(false);

	}
}

bool GameCore::checkCollision(vector<Bitmap*> a, Bitmap* hero, int left , int right , int down , int up, bool ignoreMonster)
{
	bool collision = false;
	vector<Bitmap*> closestRects;
	
	
	//search within a radius from the hero the collision objects and storing them into the closest rects vector
	for (auto i:a)
	{
		SDL_Rect temporary = *i->getCollider();
		SDL_Rect player = *hero->getCollider();
		//calculating distance between objects
		float distance = sqrt(abs(player.x - temporary.x) + abs(player.y - temporary.y));

		//the objects which distance is less than 7 add to vector
		if (distance <=8 )
			closestRects.push_back(i);
	}


	//add them into a vector( for less checks a frame)
	for (auto& bitmap : closestRects)
	{
		//player rectangle + current bitmap rectangle
		SDL_Rect player = *hero->getCollider();
		player = { player.x + left + right,player.y + up + down, player.w,player.h };
		SDL_Rect bitmapRect = *bitmap->getCollider();

		float colBottom, colTop, colLeft, colRight;

		//collision check between bounding boxes
		if (SDL_HasIntersection(&bitmapRect, &player))
		{
			//gathering the collision rectangle
			colBottom = min((player.y + player.h), (bitmapRect.y + bitmapRect.h));
			colTop = max((player.y), (bitmapRect.y));
			colLeft = max((player.x), (bitmapRect.x));
			colRight = min((player.x + player.w), (bitmapRect.x + bitmapRect.w));

			//comparing the pixels
			for (int i = colTop; i < colBottom; i++)
			{
				for (int j = colLeft; j < colRight; j++)
				{
					float x = j - player.x,
						y = i - player.y,
						bX = j - bitmapRect.x,
						bY = i - bitmapRect.y;
					if (bitmap->pixels[bY][bX] && hero->pixels[y][x])
					{
						if (bitmap->getName() == "monster" && m_pHero->getLastFrame() != DEAD && !ignoreMonster)
							inp->setKey(KEY_ESCAPE, true);
						else if (bitmap->getName() == "door")
						{
							levelIndex++;
							if(levelIndex<4)
								m_level->loadLevel(m_pRenderer,levelIndex, 0, 0);
							else if(levelIndex>3)
								inp->setKey(KEY_ESCAPE, true);
							m_pHero->setX(20);
							m_pHero->setY(150);
						}
						return true;
					}


				}
			}


		}
	}
	return collision;

}




GameCore::~GameCore()
{
	delete m_pHero;
	m_pHero = nullptr;

	delete m_timer;
	m_timer = nullptr;

	delete m_level;
	m_level = nullptr;

	delete inp;
	inp = nullptr;

	delete background;
	background = nullptr;
	if (m_pTexture)
		SDL_DestroyTexture(m_pTexture);
	if (m_pRenderer)
		SDL_DestroyRenderer(m_pRenderer);
	if (m_pWindow)
		SDL_DestroyWindow(m_pWindow);



}
