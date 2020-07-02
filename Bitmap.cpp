#include "Bitmap.h"
#include <string>
#include "SDL.h"
#include "SDL_render.h"
#include <iostream>
#include <algorithm>
using namespace std;

Bitmap::Bitmap()
{
}

Bitmap::Bitmap(SDL_Renderer* renderer, string fileName, int x, int y, bool useTransparency,string name)
{
	if(!name.empty())
		this->name = name;

	//store the renderer for future configuring and drawing
	m_pRenderer = renderer;

	//create bitmap surface
	m_pbitmapSurface = SDL_LoadBMP(fileName.c_str());
	if (!m_pbitmapSurface)
	{
		//bitmap not loaded? output the error
		printf("SURFACE FOR BITMAP '%s' not loaded! \n", fileName.c_str());
		printf("%s\n", SDL_GetError());
	}
	else
	{
		//if we are to use the transparency, going to assume
		//the colour key is magenta(r=255,g=0,b=255)
		if (useTransparency)
		{
			Uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 255, 255);
			SDL_SetColorKey(m_pbitmapSurface, SDL_TRUE, colourKey);
		}
		//create the texture
		m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface);
		if (!m_pbitmapTexture)
		{
			//texture not loaded? output the error
			printf("TEXTURE FOR BITMAP '%s' not loaded! \n", fileName.c_str());
			printf("%s\n", SDL_GetError());
		}

		//store the position vals
		m_x = x;
		m_y = y;
	}
	getPixels(pixels, fileName);

}

Bitmap::~Bitmap()
{

	if (m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);
	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface);
	if (m_pRenderer)
		SDL_DestroyRenderer(m_pRenderer);
	delete m_collider;
	m_collider = nullptr;
	pixels.clear();

}

void Bitmap::draw(int x, int y,bool left)
{
	if(x||y)
		setPos(x, y);
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { m_x,m_y,m_pbitmapSurface->w,m_pbitmapSurface->h };
		if (!left)
			SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
		else
		{
			SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
			SDL_RenderCopyEx(m_pRenderer, m_pbitmapTexture, NULL, &destRect, 180, NULL, flip);
		}
		
		
	}
}

void Bitmap::setPos(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Bitmap::getPixels(vector<vector<bool>>& pxls,string filename)
{
	//the set up 

	SDL_Surface* m_pPixelSurface = SDL_LoadBMP(filename.c_str());
	SDL_Texture* m_pPixelTexture = SDL_CreateTexture(
		m_pRenderer,
		m_pPixelSurface->format->format,
		SDL_TEXTUREACCESS_STREAMING,
		m_pPixelSurface->w,
		m_pPixelSurface->h
	);
	if(!m_pPixelTexture)
	{
		std::cout << "TEXTURE ERROR!!" << " " << SDL_GetError();
	}
	Uint32* pixels = nullptr;
	int pitch;

	//lock texture
	SDL_LockTexture(m_pPixelTexture, NULL, (void**)&pixels, &pitch);


	//copy pixels address
	memcpy(pixels, m_pPixelSurface->pixels, m_pPixelSurface->pitch*m_pPixelSurface->h);

	pixels = nullptr;

	//set transparent colour for comparison
	Uint32 transparentColour = SDL_MapRGB(m_pPixelSurface->format,255,255,255);

	//determine the number of pixels
	int bytesPerPixel = m_pPixelSurface->format->BytesPerPixel;
	int numPixels = (pitch / bytesPerPixel)*m_pPixelSurface->h;

	// coord within the 2d bool matrix
	int column = 0, row = 0;

	vector<bool> adjacent;
	//setting the 2d matrix of bool with opaque pixels
	for (int i = 0; i <= numPixels; i++)
	{
		if (column == (numPixels / m_pPixelSurface->h))
		{
			//push the line to the bool matrix and clear it after
			pxls.push_back(adjacent);
			adjacent.clear();

			//increase row and set column back to 0;
			row++;
			column = 0;
		}
		
		//compare pixels and push it to the temporary vector
		if (getpixel(m_pPixelSurface,column,row) != transparentColour)
			adjacent.push_back(true);
		else adjacent.push_back(false);
		column++;
	}


	//clean up
	SDL_UnlockTexture(m_pPixelTexture);
	adjacent.clear();
	SDL_DestroyTexture(m_pPixelTexture);
	SDL_FreeSurface(m_pPixelSurface);


}

void Bitmap::flipPixels()
{
	for (auto i = pixels.begin(); i != pixels.end(); i++)
	{
		std::reverse(i->begin(), i->end());
	}
	pixelsFlipped = !pixelsFlipped;
}

void Bitmap::displayPixels()
{
	for (auto i : pixels)
	{
		for (auto j : i)
			std::cout << j << " ";
		std::cout << endl;
	}
}

string Bitmap::getName()
{
	return name;
}

Uint32 Bitmap::getpixel(SDL_Surface * surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}

}


SDL_Rect * Bitmap::getCollider()
{
		*m_collider = { m_x,m_y,m_pbitmapSurface->w,m_pbitmapSurface->h };
		return m_collider;
}


