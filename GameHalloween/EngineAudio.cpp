#include "Engine.h"

void Engine::GeneralSound()
{
	if (mCharacter.live) {
		if (mCharacter.GetCharacterMapLevel() == 5) mSound.SoundMusicFinishPlay();
		else if (mCharacter.GetCharacterStatusGame() == 0) {
			if (mCharacter.GetPressFoodHit()) mSound.SoundCharacterKick();
			else if (mCharacter.GetPressHandHit()) mSound.SoundCharacterKick();
			else if (mCharacter.speed_y < 0) mSound.SoundCharacterJump();
			else if (mCharacter.GetPressDown()) mSound.SoundCharacterSit();
			else if ((mCharacter.GetPressRight() || mCharacter.GetPressLeft())
				&& mCharacter.speed_y == 0)
				mSound.SoundCharacterRunning();
			else {
				mSound.SoundCharacterRunningStop();
				mSound.SoundCharacterJumStop();
			}
		}
	}
	else mSound.SoundCharacterRunningStop();
}