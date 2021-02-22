#include "Engine.h"

Engine::Engine() 
{
	CreateWindowMode();
	TextFonts();
	mSound.StartMusicPlay();
	DrawMenu();
	CreateCamera();
}

void Engine::Start()
{
	Clock clock;
	Event game;

	while (mWindow.isOpen()) {
		while (mWindow.pollEvent(game)) {
			if (game.type == Event::Closed) mWindow.close();
		}

		float game_time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
		clock.restart();

		game_time = game_time / GAME_SPEED; //Game speed
		if (game_time > LIMIT_GAME_TIMER) game_time = 0;
		
		if (!mMenu.GetIsMenu()) {
			Input();
			GeneralUpdate(game_time);
			GeneralDraw();
			GeneralSound();
			GeneralInteractions(game_time);
		}
	}
}

void Engine::CreateWindowMode()
{
	Vector2f resolution;
	resolution.x = float(VideoMode::getDesktopMode().width);
	resolution.y = float(VideoMode::getDesktopMode().height);

	mWindow.create(VideoMode(int(resolution.x), int(resolution.y)),
		"Halloween", Style::Fullscreen);

	mWindow.setFramerateLimit(60);
}

void Engine::CreateCamera()
{
	mCharacter.GetCamera().reset(FloatRect(0, 1060, 800, 640)); //Loading camera
	mCharacter.GetCamera().setSize(SET_CAMERA_WIDTH, SET_CAMERA_HEIGHT); //Start set camera
}

void Engine::RestartLevel() 
{ 
	if (mCharacter.live) mCharacter.mRect.left = SPAWN_RESTART_LEVEL_X, 
									mCharacter.mRect.top = SPAWN_RESTART_LEVEL_Y;
}