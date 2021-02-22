#include "Engine.h"

/* Updating the state of all game objects: */

void Engine::GeneralUpdate(float& game_time)
{
	UpdateUnit(game_time);
	UpdateMapObject(game_time);
	mAnimation.Update(game_time);
	mCharacter.Update(game_time);
}

void Engine::UpdateUnit(float& game_time)
{
	for (enemyIt = enemiesList.begin(); enemyIt != enemiesList.end(); enemyIt++)
		(*enemyIt)->Update(game_time);
}

void Engine::UpdateMapObject(float& game_time)
{
	mMapObject.CreationPumpkinAnimations(game_time);
	mMapObject.CreationPortalAnimations(game_time);
	for (objectIt = movingObjectList.begin(); objectIt != movingObjectList.end(); objectIt++)
		(*objectIt)->Update(game_time);
}