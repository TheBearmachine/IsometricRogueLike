#include "GameState.h"
#include "Game.h"

void GameState::transition(GameState * from, GameState * to)
{
	if (!from || !to) return;
	from->exit();
	to->entry();
	*mCurrentGameState = to;
}
