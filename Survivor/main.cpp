#include "Game.h"


int main()
{
	//ªÒ»°Game
	Game& game = Game::GetInstance();
	game.Run();

	return 0;
}