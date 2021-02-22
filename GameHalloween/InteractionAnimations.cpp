#include "InteractionAnimations.h"

Animations::Animations()
{
	textureEnemyDead.loadFromFile("game_resource/animation/enemy_dead.png");
	spriteAnimationEnemyDead.setTexture(textureEnemyDead);

	animation_EnemyDeath_Current_Frame = 0;
	use_EnemyDeathAnimationSprite = false;
}

void Animations::Update(float& game_time)
{
	CreationEnemyDeathAnimation();
	CreationFramesEnemyDeathAnimation(game_time);
}

void Animations::CreationEnemyDeathAnimation()
{
	spriteAnimationEnemyDead.setTextureRect(IntRect(
		132 * int(animation_EnemyDeath_Current_Frame) + 132, 0, 132, 132));
}

void Animations::CreationFramesEnemyDeathAnimation(float& game_time)
{
	animation_EnemyDeath_Current_Frame += 0.0025f * game_time;
	if (animation_EnemyDeath_Current_Frame > 4) {
		animation_EnemyDeath_Current_Frame = 0;
		use_EnemyDeathAnimationSprite = false;
	}
}

Sprite& Animations::GetSpriteAnimationEnemyDead() { return spriteAnimationEnemyDead; }

bool Animations::GetStartEnemyDeathAnimationSprite() { return use_EnemyDeathAnimationSprite; }

void Animations::SetUseEnemyDeathAnimationSprite(bool sprite) 
{ 
	use_EnemyDeathAnimationSprite = sprite; 
}