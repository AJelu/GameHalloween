#include <ctime>
#include "Unit.h"
#include "Map.h"

Enemy::Enemy(FloatRect rectangle) : Unit(rectangle)
{
	mTexture.loadFromFile("game_resource/unit/enemyHD.png");
	mSprite.setTexture(mTexture);

	srand(int(time(NULL)));
	enemy_Move_Direction = 0;
	random_Frame = 0;

	random_Direction_Timer = 0;
	random_Frame_Timer = 0;

	enemy_Attacked = false;
}

int Enemy::flag_Level_Of_Rendering_Enemies = 1;
int Enemy::spawn_Enemy_Coordinates[ROW][COL]
{
	{ 50,680 }, { 480,750 }, { 910,750 }, { 1340,750 }, { 480,450 }, 
	{ 910,1050 }, { 1340,450 }, { 480,1050 }, { 1340,1050 }, { 910,450 }, { 50,450 }
};

int Enemy::random_Frame_List[FRAME]{ 0, 164, 330, 500 };

void Enemy::Update(float& game_time)
{
	ControlMoveEnemy(game_time);
	CreationFramesEnemy(game_time);
	ControlFramesEnemy(game_time);
	CreationEnemyAnimations();
}

void Enemy::ControlMoveEnemy(float& game_time)
{
	/* enemy_Move_Direction = 0: horizontal movement; move_Direction = 1: vertical movement */
	random_Direction_Timer += game_time;
	if (random_Direction_Timer > 6500) {
		enemy_Move_Direction = rand() % 2;
		if (enemy_Move_Direction) speed_y *= -1;
		else speed_x *= -1;
		random_Direction_Timer = 0;
		enemy_Attacked = false;
	}
	if (enemy_Move_Direction) mRect.top += 0.6f * speed_y * game_time;
	else mRect.left += 0.6f * speed_x * game_time;
	mSprite.setPosition(mRect.left, mRect.top);
}

void Enemy::CreationFramesEnemy(float& game_time)
{
	m_Current_Frame += 0.001f * game_time;
	if (m_Current_Frame > 3) m_Current_Frame = 2;
}

void Enemy::ControlFramesEnemy(float& game_time)
{
	random_Frame_Timer += game_time;
	if (random_Frame_Timer > 10000) {
		random_Frame = random_Frame_List[rand() % 4];
		random_Frame_Timer = 0;
		m_Current_Frame = 0;
	}
}

void Enemy::CreationEnemyAnimations()
{
	if ((speed_y > 0 && speed_x < 0) || (speed_y < 0 && speed_x < 0))
		mSprite.setTextureRect(IntRect(182 * int(m_Current_Frame), random_Frame, 140, 155));
	if ((speed_y > 0 && speed_x > 0) || (speed_y < 0 && speed_x > 0))
		mSprite.setTextureRect(IntRect(182 * int(m_Current_Frame) 
										+ 182, random_Frame, -186, 155));
	if (enemy_Attacked) {
		if ((speed_y > 0 && speed_x < 0) || (speed_y < 0 && speed_x < 0))
			mSprite.setTextureRect(IntRect(0 * int(m_Current_Frame) + 264, 660, 264, 229));
		else if ((speed_y > 0 && speed_x > 0) || (speed_y < 0 && speed_x > 0))
			mSprite.setTextureRect(IntRect(264 * int(m_Current_Frame) + 264, 660, -264, 229));
	}
}

void Enemy::SetEnemyAttack() { enemy_Attacked = true; }

void Enemy::CheckOfLive(list<Enemy*>& enemies_list)
{
	list<Enemy*>::iterator it;
	for (it = enemies_list.begin(); it != enemies_list.end();) {
		if ((*it)->live == false) {
			Enemy* e = *it;
			it = enemies_list.erase(it);
			delete e;
		}
		else it++;
		if (enemies_list.empty()) break;
	}
}

void Enemy::LevelInitializationEnemy(list<Enemy *>& enemies_list, 
									int const& complexity,
									int const& character_map_level)
{
	//The difficulty is the default = 1; for each new level +1 enemy;
	if (character_map_level == 1 && flag_Level_Of_Rendering_Enemies == 1) {
		CreateEnemy(enemies_list, complexity + 3); //Spawn: 1+4 enemy; 
		flag_Level_Of_Rendering_Enemies = 2;
	}
	else if (character_map_level == 2 && flag_Level_Of_Rendering_Enemies == 2) {
		CleanEnemy(enemies_list);
		CreateEnemy(enemies_list, complexity + 4); //Spawn: 1+5 enemy;  
		flag_Level_Of_Rendering_Enemies = 3;
	}
	else if (character_map_level == 3 && flag_Level_Of_Rendering_Enemies == 3) {
		CleanEnemy(enemies_list);
		CreateEnemy(enemies_list, complexity + 5); //Spawn: 1+6 enemy; 
		flag_Level_Of_Rendering_Enemies = 4;
	}
	else if (character_map_level == 4 && flag_Level_Of_Rendering_Enemies == 4) {
		CleanEnemy(enemies_list);
		CreateEnemy(enemies_list, complexity + 6); //Spawn: 1+7 enemy;  
		flag_Level_Of_Rendering_Enemies = 5;
	}
}

void Enemy::CleanEnemy(list<Enemy *>& enemies_list)
{
	list<Enemy*>::iterator it;
	if (!enemies_list.empty()) {
		for (it = enemies_list.begin(); it != enemies_list.end();) {
			Enemy* e = *it;
			it = enemies_list.erase(it);
			delete e;
			if (enemies_list.empty()) break;
		}
	}
}

void Enemy::CreateEnemy(list<Enemy *>& enemies_list, int const& complexity)
{
	for (int i = 0; i < complexity; i++) 
		enemies_list.push_back(new Enemy(FloatRect(float(spawn_Enemy_Coordinates[i][0]), 
									float(spawn_Enemy_Coordinates[i][1]), 100.0, 100.0)));
}