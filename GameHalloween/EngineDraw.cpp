#include "Engine.h"

/* Rendering of all objects: */

void Engine::GeneralDraw()
{
	mWindow.clear(Color::Black);
	mWindow.setVerticalSyncEnabled(true); //work with monitor frequency
	mWindow.draw(mMap.GetSpriteBackground(mCharacter.GetCharacterMapLevel()));
	DrawMapInitialization();
	DrawObjectsInitialization();
	DrawUnitsInitialization();
	DrawCharacter();
	DrawIconCharacter();
	mWindow.setView(mCharacter.GetCamera());
	DrawStatusGame();
	mWindow.display();
}

void Engine::DrawMapInitialization()
{
	/*  MAP definition: 
	'D' - border of map; 'P' - Pumpkin; 'L' - go to new level(portal); 'H' - potion;  */
	for (int i = 0; i < HEIGHT_MAP; i++) {
		for (int j = 0; j < WIDTH_MAP; j++) {
			if (TileMap[i][j] == 'D') continue;
			if (TileMap[i][j] == 'P') {
				mMapObject.GetSpritePumpkin(mCharacter.GetCharacterMapLevel()).
							setPosition(float(j * 32 - 15), float(i * 32 - 32));
				mWindow.draw(mMapObject.GetSpritePumpkin(mCharacter.GetCharacterMapLevel()));
			}
			if (TileMap[i][j] == 'L') {
				mMapObject.GetSpritePortal(mCharacter.GetCharacterMapLevel()).
							setPosition(float(j * 32), float(i * 32));
				mWindow.draw(mMapObject.GetSpritePortal(mCharacter.GetCharacterMapLevel()));
			}
			if (TileMap[i][j] == 'H') {
				mMapObject.GetSpritePotion().setPosition(float(j * 32), float(i * 32));
				mWindow.draw(mMapObject.GetSpritePotion());
			}
			if (TileMap[i][j] == ' ') continue;
		}
	}
}

void Engine::DrawObjectsInitialization()
{
	mMap.InitializationLevelsStaticObjects(objectPoint, movingObjectList, 
											mCharacter.GetCharacterMapLevel());
	for (objectIt = movingObjectList.begin(); objectIt != movingObjectList.end(); objectIt++)
		mWindow.draw((*objectIt)->GetSpritePumpkin(mCharacter.GetCharacterMapLevel()));
}

void Engine::DrawUnitsInitialization()
{
	enemyPoint->LevelInitializationEnemy(enemiesList, GAME_COMPLEXITY,
											mCharacter.GetCharacterMapLevel());
	for (enemyIt = enemiesList.begin(); enemyIt != enemiesList.end(); enemyIt++)
		if ((*enemyIt)->live == false) {
			mAnimation.SetUseEnemyDeathAnimationSprite(true);
			mAnimation.GetSpriteAnimationEnemyDead().setPosition((*enemyIt)->mRect.left,
																(*enemyIt)->mRect.top);
		}
		else mWindow.draw((*enemyIt)->GetSpriteUnit());
	if (mAnimation.GetStartEnemyDeathAnimationSprite()) 
		mWindow.draw(mAnimation.GetSpriteAnimationEnemyDead());
}

void Engine::DrawCharacter()
{
	if(mCharacter.live && mCharacter.GetCharacterStatusGame() != 1) 
		mWindow.draw(mCharacter.GetSpriteUnit());
}

void Engine::DrawIconCharacter()
{
	Text mTextHP(to_string(mCharacter.GetCharacterLife()), mFont, 24);
	mTextHP.setStyle(Text::Bold);
	mTextHP.setFillColor(Color::Black);
	mTextHP.setPosition(mCharacter.GetCamera().getCenter().x - 700,
						mCharacter.GetCamera().getCenter().y - 408);

	Text mTextLevel("Level", mFont, 19);
	mTextLevel.setStyle(Text::Bold);
	mTextLevel.setFillColor(Color::Black);
	mTextLevel.setPosition(mCharacter.GetCamera().getCenter().x - 780,
							mCharacter.GetCamera().getCenter().y - 494);

	Text mTextNumberLevel(to_string(mCharacter.GetCharacterMapLevel()), mFont, 19);
	mTextNumberLevel.setStyle(Text::Bold);
	mTextNumberLevel.setFillColor(Color::Black);
	mTextNumberLevel.setPosition(mCharacter.GetCamera().getCenter().x - 730,
									mCharacter.GetCamera().getCenter().y - 494);

	mMap.GetSpriteIcon().setPosition(mCharacter.GetCamera().getCenter().x - 800,
									mCharacter.GetCamera().getCenter().y - 500);
	mWindow.draw(mMap.GetSpriteIcon());
	mWindow.draw(mTextHP);
	mWindow.draw(mTextLevel);
	mWindow.draw(mTextNumberLevel);
}

void Engine::DrawStatusGame()
{
	if (mCharacter.GetCharacterStatusGame() == 1) mWindow.draw(mMap.GetSpriteGameStatus(1));
	else if (mCharacter.GetCharacterStatusGame() == 2) mWindow.draw(mMap.GetSpriteGameStatus(2));
}

void Engine::DrawMenu()
{
	Text mTextAboutGame(
		"Author: Lelyuk Olexandr       mail: leluk.olexandr@gmail.com       demo version: 1.0", 
		mFont, 27);
	mTextAboutGame.setStyle(Text::Bold);
	mTextAboutGame.setFillColor(Color::White);
	mTextAboutGame.setPosition(350, 1000);
	mWindow.setView(mWindow.getDefaultView());

	Event press;
	while (mMenu.GetIsMenu()) {

		mMenu.SetCursorVisible(mWindow, true);

		if (IntRect(100,70,370,150).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(1);
		if (IntRect(100,270,370,150).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(2);
		if (IntRect(100,470,370,150).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(3);

		while (mWindow.pollEvent(press)) {
			switch (press.type) {
				case Event::Closed:break;
				case Event::MouseButtonReleased: {
					if (press.mouseButton.button == Mouse::Left)
						if (mMenu.GetNumberMenu() == 1) {
							mMenu.SetIsMenu(false);
							mMenu.SetCursorVisible(mWindow, false);
						}
						else if (mMenu.GetNumberMenu() == 2) {
							mMenu.SetIsOption(true);
							DrawOption();
						}
						else if (mMenu.GetNumberMenu() == 3) {
							mMenu.SetIsMenu(false);
							mWindow.close();
						}
				}
				default: {
					mMenu.SetNumberMenu(0);
					break;
				}
			}
		}

		mWindow.draw(mMenu.GetSpriteMenu());
		mWindow.draw(mMenu.GetSpriteButton(1));
		mWindow.draw(mMenu.GetSpriteButton(2));
		mWindow.draw(mMenu.GetSpriteButton(3));
		mWindow.draw(mTextAboutGame);
		mWindow.display();
	}
}

void Engine::DrawOption()
{
	Text mTextOptionMusicGame("MUSIC", mFont, 80);
	mTextOptionMusicGame.setStyle(Text::Bold);
	mTextOptionMusicGame.setFillColor(Color::Black);
	mTextOptionMusicGame.setPosition(600, 238);

	Text mTextOptionDifficultyGame("DIFFICULTY", mFont, 80);
	mTextOptionDifficultyGame.setStyle(Text::Bold);
	mTextOptionDifficultyGame.setFillColor(Color::Black);
	mTextOptionDifficultyGame.setPosition(600, 418);

	Text controlMessage("CONTROL  (W):UP  (D):RIGHT  (S):DOWN  (A):LEFT  (T)/(G):KICK",
		mFont, 30);
	controlMessage.setStyle(Text::Bold);
	controlMessage.setFillColor(Color::Black);
	controlMessage.setPosition(642, 598);

	Event press;
	while (mMenu.GetIsOption()) {
		if (IntRect(800,700,250,100).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(4);
		if (IntRect(1080,700,250,100).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(5);
		if (IntRect(1050,250,150,90).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(6);
		if (IntRect(1250,250,150,90).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(7);
		if (IntRect(1050,425,72,90).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(8);
		if (IntRect(1150,425,72,90).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(9);
		if (IntRect(1250,425,72,90).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(10);
		if (IntRect(1350,425,72,90).contains(Mouse::getPosition(mWindow))) 
			mMenu.SetNumberMenu(11);

		while (mWindow.pollEvent(press)) {
			switch (press.type) {
				case Event::Closed:break;
				case Event::MouseButtonReleased: {
					if (press.mouseButton.button == Mouse::Left) {
						//4 and 5 button does nothing (just closing window)
						if (mMenu.GetNumberMenu() == 4) mMenu.SetIsOption(false); 
						if (mMenu.GetNumberMenu() == 5) mMenu.SetIsOption(false);
						if (mMenu.GetNumberMenu() == 6) mSound.StartMusicPlay();
						if (mMenu.GetNumberMenu() == 7) mSound.StopMusicPlay();
						if (mMenu.GetNumberMenu() == 8) GAME_COMPLEXITY = 1;
						if (mMenu.GetNumberMenu() == 9) GAME_COMPLEXITY = 2;
						if (mMenu.GetNumberMenu() == 10) GAME_COMPLEXITY = 3;
						if (mMenu.GetNumberMenu() == 11) GAME_COMPLEXITY = 4;
					}
				}
				default: {
					mMenu.SetNumberMenu(0);
					break;
				}
			}
		}
		
		mWindow.draw(mMenu.GetSpriteOptionMenu());
		mWindow.draw(mMenu.GetSpriteButton(4));
		mWindow.draw(mMenu.GetSpriteButton(5));
		mWindow.draw(mMenu.GetSpriteButton(6));
		mWindow.draw(mMenu.GetSpriteButton(7));
		mWindow.draw(mMenu.GetSpriteButton(8));
		mWindow.draw(mMenu.GetSpriteButton(9));
		mWindow.draw(mMenu.GetSpriteButton(10));
		mWindow.draw(mMenu.GetSpriteButton(11));
		mWindow.draw(controlMessage);
		mWindow.draw(mTextOptionMusicGame);
		mWindow.draw(mTextOptionDifficultyGame);
		mWindow.display();
	}
}