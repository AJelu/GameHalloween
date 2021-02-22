#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;
using namespace std;

class Unit {
public:
	Unit(FloatRect rectangle);

	Image mImage;
	Texture mTexture;
	Sprite mSprite;
	FloatRect mRect;
	float m_Current_Frame; 
	float speed_x, speed_y;
	bool live; 
	bool on_Ground; //Position Unit on ground

	FloatRect GetRectangle();
	Sprite& GetSpriteUnit();
	virtual void Update(float& game_Time) = 0;
};

class Character :public Unit {
private:
	View camera;

	/* Motion control positions: */
	bool press_Hand_Hit, press_Food_Hit, press_Up, 
		press_Left, press_Right, press_Down;

	enum class CharacterStateLook { LOOK_RIGHT, LOOK_LEFT };
	CharacterStateLook stateLook;

	// character_Status_Game = 0: in game;
	// character_Status_Game = 1: game won;
	// character_Status_Game = 2 game over;
	int character_Status_Game;
	
	int character_Map_Level;

	int character_Life;
	float timer_character_is_dead;
	void CheckOfCharacterLive(float& game_time);

	void ControlMoveCharacter(float& game_time);
	void CreationFramesCharacter(float& game_time);
	void CreationCharacterAnimations();

	//Collision of a character with static elements of the world
	void Collision(int const& position); 

public:
	Character(FloatRect rectangle);

	View& GetCamera();
	View SetCameraCoordinates(const float& x, const float& y);

	void Update(float& game_time) override;
	
	void PressHandHit();
	void PressFoodHit();
	void MoveUp();
	void MoveLeft();
	void MoveRight();
	void MoveDown();

	void StopHandHit();
	void StopFoodHit();
	void StopUp();
	void StopLeft();
	void StopRight();
	void StopDown();

	bool GetPressMoveUp();
	bool GetPressLeft();
	bool GetPressRight();
	bool GetPressDown();
	bool GetPressHandHit();
	bool GetPressFoodHit();

	void LossOfLife(int const& life);
	int& GetCharacterLife();
	int& GetCharacterMapLevel();
	int& GetCharacterStatusGame();
};

class Enemy : public Unit {
private:
	static int flag_Level_Of_Rendering_Enemies;

	static const int ROW = 11, COL = 2;
	static int spawn_Enemy_Coordinates[ROW][COL];

	static const int FRAME = 4;
	static int random_Frame_List[FRAME];

	int enemy_Move_Direction;

	int random_Frame;

	float random_Direction_Timer;
	float random_Frame_Timer;

	bool enemy_Attacked;

	void ControlMoveEnemy(float& game_time);
	void ControlFramesEnemy(float& game_time);
	void CreationFramesEnemy(float& game_time);
	void CreationEnemyAnimations();

	void CleanEnemy(list<Enemy*>& enemies_list);
	void CreateEnemy(list<Enemy*>& enemies_list, int const& complexity);
	
public: 
	Enemy(FloatRect rectangle);

	void Update(float& game_time) override;
	void SetEnemyAttack();
	void CheckOfLive(list<Enemy*>& enemies_list);
	void LevelInitializationEnemy(list<Enemy *>& enemies_list, 
									int const& complexity,
									int const& character_map_level);
};