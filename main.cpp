#include "SDL.h"
#include "GameCore.h"
#include "Entity.h"
#undef main
int main()
{
	GameCore game = GameCore();
	game.gameLoop();
	return 0;
}