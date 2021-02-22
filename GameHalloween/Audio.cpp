#include "Audio.h"

Sounds::Sounds()
{
	musicGame.loadFromFile("game_resource/music/Music.ogg");
	musicFinishGame.loadFromFile("game_resource/music/Finish_game.ogg");
	musicCharacterJump.loadFromFile("game_resource/music/Character_jump.ogg");
	musicCharacterSit.loadFromFile("game_resource/music/Character_sit.ogg");
	musicCharacterKick.loadFromFile("game_resource/music/Character_kick.ogg");
	musicCharacterRunning.loadFromFile("game_resource/music/Character_running.ogg");
	musicEnemyAttack.loadFromFile("game_resource/music/Enemy_attack.ogg");
	musicEnemyDeath.loadFromFile("game_resource/music/Enemy_death.ogg");

	soundGamePlay.setBuffer(musicGame);
	soundGamePlay.setVolume(40);
	soundGamePlay.setLoop(true);

	soundFinishGamePlay.setBuffer(musicFinishGame);
	soundFinishGamePlay.setVolume(40);

	soundCharacterJump.setBuffer(musicCharacterJump);
	soundCharacterSit.setBuffer(musicCharacterSit);
	soundCharacterKick.setBuffer(musicCharacterKick);
	soundCharacterRunning.setBuffer(musicCharacterRunning);
	soundEnemyAttack.setBuffer(musicEnemyAttack);
	soundEnemyDeath.setBuffer(musicEnemyDeath);

	// state_running_Character = 0: flag for off play sound run
	// state_running_Character = 1: flag for on play sound run
	state_running_Character = 1;

	// state_jump_Character = 0: flag for off play sound jump
	// state_jump_Character = 1: flag for on play sound jump
	state_jump_Character = 1;
}

void Sounds::StartMusicPlay() { soundGamePlay.play(); }

void Sounds::StopMusicPlay() { soundGamePlay.stop(); }

void Sounds::SoundMusicFinishPlay() { soundFinishGamePlay.play(); }

void Sounds::SoundCharacterJump() 
{ 
	if (state_jump_Character) {
		state_jump_Character = 0;
		soundCharacterJump.play();
	}
}

void Sounds::SoundCharacterJumStop()
{
	soundCharacterRunning.stop();
	state_jump_Character = 1;
}

void Sounds::SoundCharacterSit() { soundCharacterSit.play(); }

void Sounds::SoundCharacterRunning()
{ 
	if (state_running_Character) {
		state_running_Character = 0;
		soundCharacterRunning.play();
		soundCharacterRunning.setLoop(true);
	}
}

void Sounds::SoundCharacterRunningStop()
{ 
	soundCharacterRunning.stop();
	soundCharacterRunning.setLoop(false);
	state_running_Character = 1;
}

void Sounds::SoundCharacterKick() { soundCharacterKick.play(); }

void Sounds::SoundEnemyAttack() { soundEnemyAttack.play(); }

void Sounds::SoundEnemyDeath() { soundEnemyDeath.play(); }