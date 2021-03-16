#include "Map.h"

Map::MovingMapObject::MovingMapObject(FloatRect rectangle)
{
	objRect = rectangle;
	object_Speed_x = 0.06f;
	move_Timer = 0;
}

int Map::MovingMapObject::spawn_Moving_Object_Coordinates[LEVEL_COMPLEXITY][ROW][COL]
{
{ { 150,400 }, { 1100,250 } }, //Level 1
{ { 815,385 }, { 720,695 } }, //Level 2
{ { 470,310 }, { 715,580 } }, //Level 3
{ { 1240,800 }, { 190,300 } }  //Level 4
};

void Map::MovingMapObject::Update(float& game_time)
{
	ControlMovePumpkin(game_time);
	CreationPumpkinAnimations();
	CreationFramesPumpkin(game_time);
}

void Map::MovingMapObject::ControlMovePumpkin(float& game_time)
{
	move_Timer += game_time;
	if (move_Timer > 6000) {
		object_Speed_x *= -1;
		move_Timer = 0;
	}
	objRect.left += object_Speed_x * game_time;
	spritePumpkin.setPosition(objRect.left, objRect.top);
}

float& Map::MovingMapObject::GetObjectSpeed() { return object_Speed_x; }

void Map::MovingMapObject::CreationPumpkinAnimations()
{
	if (object_Speed_x < 0) spritePumpkin.setTextureRect(IntRect
		(159 * int(pumpkin_Current_Frame) + 159, 10, 153, 130));
	else spritePumpkin.setTextureRect(IntRect
		(156 * int(pumpkin_Current_Frame) + 156, 10, -153, 130));	
}

void Map::MovingMapObject::CreationFramesPumpkin(float& game_time)
{
	pumpkin_Current_Frame += 0.004f * game_time;
	if (pumpkin_Current_Frame > 2) pumpkin_Current_Frame = 0;
}

void Map::MovingMapObject::CleanMovingObject(list<Map::MovingMapObject*>& object_list)
{
	list<Map::MovingMapObject *>::iterator it;
	if (!object_list.empty()) {
		for (it = object_list.begin(); it != object_list.end();) {
			Map::MovingMapObject* e = *it;
			it = object_list.erase(it);
			delete e;

			if (object_list.empty()) break;
		}
	}
}

void Map::MovingMapObject::CreateMovingObject(const int& level, 
						list<Map::MovingMapObject *>& object_list)
{
	for (int i = 0; i < ROW; i++) {
		object_list.push_back(new MovingMapObject(FloatRect(
			float(spawn_Moving_Object_Coordinates[level][i][0]),
			float(spawn_Moving_Object_Coordinates[level][i][1]), 50.0, 50.0)));
	}
}

FloatRect Map::MovingMapObject::GetRectangle()
{
	return FloatRect(objRect.left, objRect.top, objRect.width, objRect.height);
}
