#include "Map.h"

String TileMap[HEIGHT_MAP]{
		"DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
        	"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"D                                                         D",
		"DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD"
};

Map::Map()
{
	textureBackground1.loadFromFile("game_resource/background/background_1.png");
	textureBackground2.loadFromFile("game_resource/background/background_2.png");
	textureBackground3.loadFromFile("game_resource/background/background_3.png");
	textureBackground4.loadFromFile("game_resource/background/background_4.png");
	textureIconCharacter.loadFromFile("game_resource/textures/Char_icon.png");
	textureGameWinner.loadFromFile("game_resource/background/game_win.png");
	textureGameOver.loadFromFile("game_resource/background/game_over.png");

	spriteIconCharacter.setTexture(textureIconCharacter);
}

int Map::flag_Level_Of_Rendering_Object = 0;

Sprite& Map::GetSpriteBackground(int const& character_map_level)
{
	switch (character_map_level) {
		case 1: spriteBackground.setTexture(textureBackground1); 
			return spriteBackground;
		case 2: spriteBackground.setTexture(textureBackground2); 
			return spriteBackground;
		case 3: spriteBackground.setTexture(textureBackground3); 
			return spriteBackground;
		case 4: spriteBackground.setTexture(textureBackground4); 
			return spriteBackground;
	}
	return spriteBackground; 
}

Sprite& Map::GetSpriteIcon() { return spriteIconCharacter; }

Sprite& Map::GetSpriteGameStatus(int const& player_won)
{
	if (player_won == 1) spriteGameStatus.setTexture(textureGameWinner);
	else if (player_won == 2) spriteGameStatus.setTexture(textureGameOver);
	return spriteGameStatus;
}

void Map::InitializationLevelsStaticObjects(Map::MovingMapObject* object_point,
											list<Map::MovingMapObject*>& object_list,
											int const& character_map_level)
{
	if (character_map_level == 1 && flag_Level_Of_Rendering_Object == 0) {
		object_point->CreateObject(0);
		object_point->CreateMovingObject(0, object_list);
		flag_Level_Of_Rendering_Object = 1;
	}
	else if (character_map_level == 2 && flag_Level_Of_Rendering_Object == 1) {
		object_point->CleanObject(0);
		object_point->CleanMovingObject(object_list);
		object_point->CreateObject(1);
		object_point->CreateMovingObject(1, object_list);
		flag_Level_Of_Rendering_Object = 2;
	}
	else if (character_map_level == 3 && flag_Level_Of_Rendering_Object == 2) {
		object_point->CleanObject(1);
		object_point->CleanMovingObject(object_list);
		object_point->CreateObject(2);
		object_point->CreateMovingObject(2, object_list);
		flag_Level_Of_Rendering_Object = 3;
	}
	else if (character_map_level == 4 && flag_Level_Of_Rendering_Object == 3) {
		object_point->CleanObject(2);
		object_point->CleanMovingObject(object_list);
		object_point->CreateObject(3);
		object_point->CreateMovingObject(3, object_list);
		flag_Level_Of_Rendering_Object = 4;
	}
	else if (character_map_level == 5 && flag_Level_Of_Rendering_Object == 4) {
		object_point->CleanObject(3);
		object_point->CleanMovingObject(object_list);
	}
}
