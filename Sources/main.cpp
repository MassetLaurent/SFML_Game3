#include "Game.h"
#include <time.h>

int main()
{
	srand(time(static_cast<unsigned>(NULL)));

	Game game;

	game.run();

	//system("pause");

	return 0;
}