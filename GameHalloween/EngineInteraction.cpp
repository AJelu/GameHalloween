#include "Engine.h"

void Engine::GeneralInteractions(float& game_time)
{
	enemyPoint->CheckOfLive(enemiesList);
	InteractionOfObjects(game_time);
	InteractionOfUnits();
}

void Engine::InteractionOfObjects(float& game_time)
{
	for (objectIt = movingObjectList.begin(); objectIt != movingObjectList.end(); objectIt++) {
		if ((*objectIt)->GetRectangle().intersects(mCharacter.GetRectangle())) {
			Map::MovingMapObject* movePumpkin = *objectIt;
			if (mCharacter.mRect.top + mCharacter.mRect.height
				< movePumpkin->GetRectangle().top + movePumpkin->GetRectangle().height)
			{
				mCharacter.mRect.top = movePumpkin->GetRectangle().top - 
													mCharacter.mRect.height + 21;
				mCharacter.mRect.left += movePumpkin->GetObjectSpeed() * game_time;
				mCharacter.speed_y = 0;
				mCharacter.on_Ground = true;
			}
		}
	}
}

void Engine::InteractionOfUnits()
{
	for (enemyIt = enemiesList.begin(); enemyIt != enemiesList.end(); enemyIt++) {
		if ((*enemyIt)->GetRectangle().intersects(mCharacter.GetRectangle())) {
			if ((mCharacter.speed_y > 0) && (mCharacter.on_Ground == false)) {
				mSound.SoundEnemyDeath(); //<-Play sound Enemy
				mCharacter.speed_y = -0.4f;
				(*enemyIt)->live = false;
			}
			else if ((mCharacter.GetPressHandHit()) || (mCharacter.GetPressFoodHit())) {
				mSound.SoundEnemyDeath(); //<-Play sound Enemy
				(*enemyIt)->speed_y = -0.2f;
				(*enemyIt)->live = false;
			}
			else {
				(*enemyIt)->SetEnemyAttack();
				mSound.SoundEnemyAttack(); //<-Play sound Enemy
				if(mCharacter.GetCharacterLife() == 1) mSound.SoundMusicFinishPlay();
				mCharacter.LossOfLife(1);
				RestartLevel();
				mCharacter.live = false;
			}
		}
	}
}
