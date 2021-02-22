#include "Map.h"

Map::MapObject::MapObject()
{
	texturePumpkinGreen.loadFromFile("game_resource/textures/pumpkin_Green.png");
	texturePumpkinRed.loadFromFile("game_resource/textures/pumpkin_Red.png");
	texturePumpkinFrost.loadFromFile("game_resource/textures/pumpkin_Frost.png");
	texturePumpkinOrange.loadFromFile("game_resource/textures/pumpkin_Orange.png");

	texturePortalGreen.loadFromFile("game_resource/textures/portal_Green.png");
	texturePortalRed.loadFromFile("game_resource/textures/portal_Red.png");
	texturePortalFrost.loadFromFile("game_resource/textures/portal_Frost.png");
	texturePortalOrange.loadFromFile("game_resource/textures/portal_Orange.png");

	texturePotion.loadFromFile("game_resource/textures/Potion_Life.png");
	spritePotion.setTexture(texturePotion);

	pumpkin_Current_Frame = 0;
	portal_Current_Frame = 0;
}

int Map::MapObject::spawn_Pumpkin_Coordinates[LEVEL_COMPLEXITY][PUMPKIN_SPAWN_X][PUMPKIN_SPAWN_Y]
{ //spawn coordinates Level 1:
	{{ 8,54 }, { 13,32 }, { 13,50 }, { 16,20 }, { 18,28 }, { 20,1 },
	 { 23,40 }, { 24,57 }, { 27,5 }, { 27,50 }, { 30,12 }, { 32,21 }},
  //spawn coordinates Level 2:
	{{ 10,21 }, { 14,2 },  { 14,55 }, { 15,15 }, { 17,42 }, { 22,8 },
	 { 22,51 }, { 26,12 }, { 27,17 }, { 29,34 }, { 33,27 }, { 33,47 }},
  //spawn coordinates Level 3:
	{{ 9,25 }, { 12,45 }, { 13,40 }, { 13,50 }, { 17,2 }, { 19,56 },
	 { 23,9 }, { 23,45 }, { 27,50 }, { 29,18 }, { 29,38 }, { 33,28 }},
  //spawn coordinates Level 4:
	{{ 32,16 }, { 24,14 }, { 20,6 }, { 14,1 }, { 11,24 }, { 8,55 },
	 { 21,24 }, { 24,32 }, { 10,38 }, { 17,55 }, { 16,43 }, { 16,47 }},
};

int Map::MapObject::spawn_Portal_Coordinates[LEVEL_COMPLEXITY][PORTAL_SPAWN_X][PORTAL_SPAWN_Y]
{
	{{ 10,55 }},
	{{ 2,55 }},
	{{ 2,1 }},
	{{ 1,35 }}
}; 

int Map::MapObject::spawn_Potion_Coordinates[LEVEL_COMPLEXITY][POTION_SPAWN_X][POTION_SPAWN_Y]
{//	  Level 1	   Level 2	   Level 3	   Level 4
	{{ 19,40 }}, {{ 10,2 }}, {{ 5,25 }}, {{ 7,11 }}
};

void Map::MapObject::CleanObject(int const& level) { SpawnObjects(level, 0); }

void Map::MapObject::CreateObject(int const& level) { SpawnObjects(level, 1); }

/* int action accepts (0 or 1) 0 = Clean Object; 1 = Create Object; */
void Map::MapObject::SpawnObjects(int const& level, int const& action)
{
	int respawn_X = 0, respawn_Y = 0;

	for (int i = 0; i < PUMPKIN_SPAWN_X; i++) {
		respawn_X = spawn_Pumpkin_Coordinates[level][i][0];
		respawn_Y = spawn_Pumpkin_Coordinates[level][i][1];
		if(action) TileMap[respawn_X][respawn_Y] = 'P';
		if(!action) TileMap[respawn_X][respawn_Y] = ' ';
	}
	
	for (int i = 0; i < POTION_SPAWN_X; i++) {
		respawn_X = spawn_Potion_Coordinates[level][i][0];
		respawn_Y = spawn_Potion_Coordinates[level][i][1];
		if (action) TileMap[respawn_X][respawn_Y] = 'H';
		if (!action) TileMap[respawn_X][respawn_Y] = ' ';
	}
	
	for (int i = 0; i < PORTAL_SPAWN_X; i++) {
		respawn_X = spawn_Portal_Coordinates[level][i][0];
		respawn_Y = spawn_Portal_Coordinates[level][i][1];
		if (action) TileMap[respawn_X][respawn_Y] = 'L';
	}
}

void Map::MapObject::CreationPumpkinAnimations(float& game_time)
{
	spritePumpkin.setTextureRect(IntRect(159 * int(pumpkin_Current_Frame) + 159, 10, 153, 130));
	pumpkin_Current_Frame += 0.004f * game_time;
	if (pumpkin_Current_Frame > 2) pumpkin_Current_Frame = 0;
}

void Map::MapObject::CreationPortalAnimations(float& game_time)
{
	spritePortal.setTextureRect(IntRect(170 * int(portal_Current_Frame) + 170, 0, 170, 173));
	portal_Current_Frame += 0.006f * game_time;
	if (portal_Current_Frame > 3) portal_Current_Frame = 0;
}

Sprite& Map::MapObject::GetSpritePumpkin(int const& character_map_level)
{
	switch (character_map_level) {
		case 1: spritePumpkin.setTexture(texturePumpkinGreen);
			return spritePumpkin;
		case 2: spritePumpkin.setTexture(texturePumpkinRed);
			return spritePumpkin;
		case 3: spritePumpkin.setTexture(texturePumpkinFrost);
			return spritePumpkin;
		case 4: spritePumpkin.setTexture(texturePumpkinOrange);
			return spritePumpkin;
	}
	return spritePumpkin;
}

Sprite& Map::MapObject::GetSpritePortal(int const& character_map_level)
{ 
	switch (character_map_level) {
		case 1: spritePortal.setTexture(texturePortalGreen);
			return spritePortal;
		case 2: spritePortal.setTexture(texturePortalRed);
			return spritePortal;
		case 3: spritePortal.setTexture(texturePortalFrost);
			return spritePortal;
		case 4: spritePortal.setTexture(texturePortalOrange);
			return spritePortal;
	}
	return spritePortal;
}

Sprite& Map::MapObject::GetSpritePotion() { return spritePotion; }
