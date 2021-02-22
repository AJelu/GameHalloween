#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;
using namespace std;

const int HEIGHT_MAP = 37;
const int WIDTH_MAP = 59;
extern String TileMap[HEIGHT_MAP]; //Map structure

class Map {
private:
	Texture textureBackground1, textureBackground2, 
		textureBackground3, textureBackground4;

	Texture textureIconCharacter;
	Texture textureGameWinner, textureGameOver;

	Sprite spriteBackground;
	Sprite spriteIconCharacter;
	Sprite spriteGameStatus;

public:
	Map();
	Sprite& GetSpriteBackground(int const& character_map_level);
	Sprite& GetSpriteIcon();
	Sprite& GetSpriteGameStatus(int const& player_won);

	static int flag_Level_Of_Rendering_Object; //Level randering object control

	class MapObject {
	protected:
		Sprite spritePumpkin;

		static const int LEVEL_COMPLEXITY = 4;

		float pumpkin_Current_Frame, portal_Current_Frame;

	private:
		Texture texturePumpkinGreen, texturePumpkinRed,
			texturePumpkinFrost, texturePumpkinOrange;

		Texture texturePortalGreen, texturePortalRed,
			texturePortalFrost, texturePortalOrange;

		Texture texturePotion;

		Sprite spritePortal;
		Sprite spritePotion;

		static const int PUMPKIN_SPAWN_X = 12, PUMPKIN_SPAWN_Y = 2;
		static int spawn_Pumpkin_Coordinates[LEVEL_COMPLEXITY][PUMPKIN_SPAWN_X][PUMPKIN_SPAWN_Y];

		static const int PORTAL_SPAWN_X = 1, PORTAL_SPAWN_Y = 2;
		static int spawn_Portal_Coordinates[LEVEL_COMPLEXITY][PORTAL_SPAWN_X][PORTAL_SPAWN_Y];

		static const int POTION_SPAWN_X = 1, POTION_SPAWN_Y = 2;
		static int spawn_Potion_Coordinates[LEVEL_COMPLEXITY][POTION_SPAWN_X][POTION_SPAWN_Y];

		void SpawnObjects(int const& level, int const& action);
	
	public:
		MapObject();
		Sprite& GetSpritePumpkin(int const& character_map_level);
		Sprite& GetSpritePortal(int const& character_map_level);
		Sprite& GetSpritePotion();

		void CreationPumpkinAnimations(float& game_time);
		void CreationPortalAnimations(float& game_time);

		void CreateObject(int const& level);
		void CleanObject(int const& level);
	};

	class MovingMapObject : public MapObject {
	private:
		FloatRect objRect;

		float move_Timer;
		float object_Speed_x;

		static const int ROW = 2, COL = 2;
		static int spawn_Moving_Object_Coordinates[LEVEL_COMPLEXITY][ROW][COL];

		void ControlMovePumpkin(float& game_time);
		void CreationPumpkinAnimations();
		void CreationFramesPumpkin(float& game_time);

	public:
		MovingMapObject(FloatRect rectangle);

		FloatRect GetRectangle();

		void Update(float& game_time);
		float& GetObjectSpeed();
		void CleanMovingObject(list<Map::MovingMapObject*>& object_list);
		void CreateMovingObject(int const& level, list<Map::MovingMapObject*>& object_list);
	};

	void InitializationLevelsStaticObjects(Map::MovingMapObject* object_point,
									list<Map::MovingMapObject*>& object_list,
									int const& character_map_level);
};