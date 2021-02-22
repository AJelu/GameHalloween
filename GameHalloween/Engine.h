#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Settings.h"
#include "Menu.h"
#include "Map.h"
#include "Unit.h"
#include "InteractionAnimations.h"
#include "Audio.h"

/*
	Engine includes the following files:
		EngineAudio.cpp : contains general sound settings
		Engine.cpp : contains general game settings
		EngineDraw.cpp : draws all objects in the game
		EngineInput.cpp : sets the dependence of button presses
		EngineInteraction.cpp : contains the interaction of dynamic objects
		EngineUpdate.cpp : updates all objects in the game

	also:
		TextFonts.cpp : connects the font
*/

using namespace std;
using namespace sf;

class Engine {
private:
	RenderWindow mWindow;
	
	Sounds mSound;

	Font mFont;

	Menu mMenu;

	Map mMap; 
	Map::MapObject mMapObject;

	Map::MovingMapObject* objectPoint;
	list<Map::MovingMapObject*> movingObjectList;
	list<Map::Map::MovingMapObject*>::iterator objectIt;

	Enemy* enemyPoint;
	list<Enemy*> enemiesList;
	list<Enemy*>::iterator enemyIt;

	Animations mAnimation;

	/* Spawn: x:(80.0), y:(930.0), character's physical points : w(50.0), h(210.0) */
	Character mCharacter{ FloatRect(80.0, 930.0, 50.0, 210.0) };

	

	void TextFonts();

	void CreateWindowMode();
	void CreateCamera();

	void Input();
	void GeneralUpdate(float& game_time);
	void UpdateUnit(float& game_time);
	void UpdateMapObject(float& game_time);

	void GeneralSound(); //Interaction with sounds

	void GeneralDraw();
	void DrawMenu();
	void DrawOption();
	void DrawMapInitialization(); //Render of Map's background
	void DrawUnitsInitialization(); //Render of enemy's unit
	void DrawObjectsInitialization(); //Render of all map object
	void DrawCharacter(); //Render Hero
	void DrawIconCharacter(); //Render Hero's status icon
	void DrawStatusGame(); //Render a win or lose status icon

	void GeneralInteractions(float& game_time);
	void InteractionOfObjects(float& game_time);
	void InteractionOfUnits();

	void RestartLevel();

public:
	Engine();

	void Start();
};
