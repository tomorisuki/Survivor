/**
 * @file        main.cpp
 * @brief       主程序入口
 * @author      tomorisuki
 * @version     1.0.0
 * @date        2026-06-01
 */




#include "Game.h"



int main()
{
	//Get Game
	Game& game = Game::GetInstance();
	game.Run();

	return 0;
}