#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Animations {
private:
	Texture textureEnemyDead;

	Sprite spriteAnimationEnemyDead;

	bool use_EnemyDeathAnimationSprite;
	float animation_EnemyDeath_Current_Frame;

	void CreationEnemyDeathAnimation();
	void CreationFramesEnemyDeathAnimation(float& game_time);

public:
	Animations();
	void Update(float& game_time);
	
	Sprite& GetSpriteAnimationEnemyDead();

	bool GetStartEnemyDeathAnimationSprite();
	void SetUseEnemyDeathAnimationSprite(bool sprite);
};