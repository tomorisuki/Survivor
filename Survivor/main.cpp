#include "Game.h"


int main()
{
	//获取Game
	Game& game = Game::GetInstance();
	game.Run();

	return 0;
}