#include "Engine.h"

/* Control of button presses: */

void Engine::Input()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		mMenu.SetIsMenu(true);
		DrawMenu();
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) 
		mCharacter.MoveUp();
	else mCharacter.StopUp();

	if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		mCharacter.MoveDown();
	else mCharacter.StopDown();

	if (Keyboard::isKeyPressed(Keyboard::G))
		mCharacter.PressFoodHit();
	else if (Keyboard::isKeyPressed(Keyboard::T))
		mCharacter.PressHandHit();
	else {
		mCharacter.StopHandHit();
		mCharacter.StopFoodHit();

		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
			mCharacter.MoveLeft();
		else mCharacter.StopLeft();

		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
			mCharacter.MoveRight();
		else mCharacter.StopRight();
	}
}

