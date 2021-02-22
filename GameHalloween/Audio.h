#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class Sounds {
private:
	SoundBuffer musicGame, musicFinishGame;
	SoundBuffer musicCharacterJump, musicCharacterSit, 
				musicCharacterRunning, musicCharacterKick;

	SoundBuffer musicEnemyAttack, musicEnemyDeath;

	Sound soundGamePlay, soundFinishGamePlay;
	Sound soundCharacterJump, soundCharacterSit, 
			soundCharacterKick, soundCharacterRunning;

	Sound soundEnemyAttack, soundEnemyDeath;

	int state_running_Character, state_jump_Character;

public:
	Sounds();

	void StartMusicPlay();
	void StopMusicPlay();
	void SoundMusicFinishPlay();

	void SoundCharacterJump();
	void SoundCharacterJumStop();
	void SoundCharacterSit();
	void SoundCharacterRunning();
	void SoundCharacterRunningStop();
	void SoundCharacterKick();

	void SoundEnemyAttack();
	void SoundEnemyDeath();
};
