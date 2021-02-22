#include <iostream>
#include "Unit.h"

/* 
	Character has additional files: 
	CharacterCollision.cpp : includes interaction with map boundaries and statistical objects;

	CharacterCamera.cpp : includes the character's camera and her interaction with the 
								boundaries of the map;
*/

Character::Character(FloatRect rectangle) : Unit(rectangle)
{
	mTexture.loadFromFile("game_resource/unit/character_zombie_sheetHD.png");
	mSprite.setTexture(mTexture);

	timer_character_is_dead = 0;
	character_Status_Game = 0;
	character_Map_Level = 1;
	character_Life = 3;

	press_Hand_Hit = false;
	press_Food_Hit = false;
	press_Up = false;
	press_Left = false;
	press_Right = false;
	press_Down = false;

	stateLook = CharacterStateLook::LOOK_RIGHT;
}

void Character::Update(float& game_time)
{
	CheckOfCharacterLive(game_time);
	ControlMoveCharacter(game_time);
	CreationFramesCharacter(game_time);
	CreationCharacterAnimations();
	SetCameraCoordinates(mRect.left, mRect.top);
}

void Character::CheckOfCharacterLive(float& game_time)
{
	if (!live) {
		if (!character_Life) character_Status_Game = 2;
		else {
			timer_character_is_dead += game_time;
			if (timer_character_is_dead > 6500) {
				live = true;
				timer_character_is_dead = 0;
			}
		}
	}
	else if (character_Life && character_Map_Level == 5) character_Status_Game = 1;
}

int& Character::GetCharacterMapLevel() { return character_Map_Level; }

int& Character::GetCharacterStatusGame() { return character_Status_Game; }

void Character::LossOfLife(int const& life) { character_Life -= life; }

void Character::ControlMoveCharacter(float& game_time)
{
	if (live && character_Status_Game != 1) {
		if (live) mRect.left += speed_x * game_time;
		Collision(1); //Collision on the ground

		if (!on_Ground) speed_y = speed_y + 0.0005f * game_time;
		mRect.top += speed_y * game_time;
		on_Ground = false;
		Collision(2); //Collision on the fly

		mSprite.setPosition(mRect.left, mRect.top);
		speed_x = 0;
	}
}

void Character::CreationFramesCharacter(float& game_time)
{
	m_Current_Frame += 0.005f * game_time;
	if (m_Current_Frame > 7) m_Current_Frame = 0;
}

void Character::CreationCharacterAnimations()
{
	if (live && character_Status_Game != 1) {
		if (press_Hand_Hit) {
			if (stateLook == CharacterStateLook::LOOK_RIGHT)
				mSprite.setTextureRect(IntRect(10, 820, 175, 205));
			else mSprite.setTextureRect(IntRect(182, 820, -175, 205));
		}
		else if (press_Food_Hit) {
			if (stateLook == CharacterStateLook::LOOK_RIGHT)
				mSprite.setTextureRect(IntRect(960, 295, 182, 216));
			else mSprite.setTextureRect(IntRect(1142, 295, -182, 216));
		}
		else if (press_Up) {
			if (stateLook == CharacterStateLook::LOOK_RIGHT)
				mSprite.setTextureRect(IntRect(208, 45, 164, 209));
			else mSprite.setTextureRect(IntRect(371, 45, -164, 209));
		}
		else if (press_Left) {
			mSprite.setTextureRect(IntRect(192 * int(m_Current_Frame) + 192, 1070, -165, 205));
			stateLook = CharacterStateLook::LOOK_LEFT;
		}
		else if (press_Right) {
			mSprite.setTextureRect(IntRect(192 * int(m_Current_Frame) + 192, 1070, 155, 208));
			stateLook = CharacterStateLook::LOOK_RIGHT;
		}
		else if (press_Down) mSprite.setTextureRect(IntRect(576, 34, 165, 205));
		else {
			if (!press_Up && speed_y > 0)
				mSprite.setTextureRect(IntRect(1555, 40, 156, 210));
			else if (stateLook == CharacterStateLook::LOOK_RIGHT)
				mSprite.setTextureRect(IntRect(30, 50, 133, 206));
			else mSprite.setTextureRect(IntRect(164, 50, -133, 206));
		}
	}
	else mSprite.setTextureRect(IntRect(770, 51, 188, 199));
}

void Character::PressHandHit() { press_Hand_Hit = true; }

void Character::PressFoodHit() { press_Food_Hit = true; }

void Character::MoveUp()
{
	if (on_Ground) {
		speed_y = -0.54f;
		on_Ground = false;
		press_Up = true;
	}
}

void Character::MoveLeft() { press_Left = true; speed_x = -0.1f; }

void Character::MoveRight() { press_Right = true; speed_x = 0.1f; }

void Character::MoveDown() { press_Down = true; }

void Character::StopHandHit() { press_Hand_Hit = false; }

void Character::StopFoodHit() { press_Food_Hit = false; }

void Character::StopUp() { press_Up = false; }

void Character::StopLeft() { press_Left = false; }

void Character::StopRight() { press_Right = false; }

void Character::StopDown() { press_Down = false; }


bool Character::GetPressMoveUp() { return press_Up; }

bool Character::GetPressLeft() { return press_Left; }

bool Character::GetPressRight() { return press_Right; }

bool Character::GetPressDown() { return press_Down; }

bool Character::GetPressHandHit() { return press_Hand_Hit; }

bool Character::GetPressFoodHit() { return press_Food_Hit; }

int& Character::GetCharacterLife() { return character_Life; }