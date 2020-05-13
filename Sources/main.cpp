#include "Game.h"
#include <time.h>

int main()
{
	srand(time(static_cast<unsigned>(0)));

	Game game;

	game.run();

	//system("pause");

	return 0;
}