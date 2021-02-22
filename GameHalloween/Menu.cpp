#include "Menu.h"

Menu::Menu()
{
	textureMenuButton1.loadFromFile("game_resource/icon/button_play.png");
	textureMenuButton2.loadFromFile("game_resource/icon/button_option.png");
	textureMenuButton3.loadFromFile("game_resource/icon/button_exit.png");
	textureOptionMenu.loadFromFile("game_resource/background/option.png");
	textureMenu.loadFromFile("game_resource/background/menu.png");

	textureOptionButton1.loadFromFile("game_resource/icon/button_accept.png");
	textureOptionButton2.loadFromFile("game_resource/icon/button_menu.png");
	textureMiniOptionButtonON.loadFromFile("game_resource/icon/button_on.png");
	textureMiniOptionButtonOFF.loadFromFile("game_resource/icon/button_off.png");
	textureMiniOptionButton1.loadFromFile("game_resource/icon/button_1.png");
	textureMiniOptionButton2.loadFromFile("game_resource/icon/button_2.png");
	textureMiniOptionButton3.loadFromFile("game_resource/icon/button_3.png");
	textureMiniOptionButton4.loadFromFile("game_resource/icon/button_4.png");

	spriteMenu.setTexture(textureMenu);
	spriteMenu.setPosition(0, 0);

	spriteOptionMenu.setTexture(textureOptionMenu);

	is_Option = false;
	is_Menu = true;
	number_Menu = 0;
}

void Menu::SetCursorVisible(RenderWindow& window, bool visible)
{
	window.setMouseCursorVisible(visible);
}

int& Menu::GetNumberMenu() { return number_Menu; }

void Menu::SetNumberMenu(int const& state_menu) { number_Menu = state_menu; }

Sprite& Menu::GetSpriteButton(int const& number_button)
{
	switch (number_button) {
		case 1: {
			spriteMenuButton.setTexture(textureMenuButton1);
			spriteMenuButton.setPosition(100, 70);
			return spriteMenuButton;
		}
		case 2: {
			spriteMenuButton.setTexture(textureMenuButton2);
			spriteMenuButton.setPosition(100, 270);
			return spriteMenuButton;
		}
		case 3: {
			spriteMenuButton.setTexture(textureMenuButton3);
			spriteMenuButton.setPosition(100, 470);
			return spriteMenuButton;
		}
		case 4: {
			spriteOptionButton.setTexture(textureOptionButton1);
			spriteOptionButton.setPosition(800, 700);
			return spriteOptionButton;
		}
		case 5: {
			spriteOptionButton.setTexture(textureOptionButton2);
			spriteOptionButton.setPosition(1080, 700);
			return spriteOptionButton;
		}
		case 6: {
			spriteMiniOptionButton.setTexture(textureMiniOptionButtonON);
			spriteMiniOptionButton.setPosition(1050, 250);
			return spriteMiniOptionButton;
		}
		case 7: {
			spriteMiniOptionButton.setTexture(textureMiniOptionButtonOFF);
			spriteMiniOptionButton.setPosition(1250, 250);
			return spriteMiniOptionButton;
		}
		case 8: {
			spriteLevelMiniOptionButton.setTexture(textureMiniOptionButton1);
			spriteLevelMiniOptionButton.setPosition(1050, 425);
			return spriteLevelMiniOptionButton;
		}
		case 9: {
			spriteLevelMiniOptionButton.setTexture(textureMiniOptionButton2);
			spriteLevelMiniOptionButton.setPosition(1150, 425);
			return spriteLevelMiniOptionButton;
		}
		case 10: {
			spriteLevelMiniOptionButton.setTexture(textureMiniOptionButton3);
			spriteLevelMiniOptionButton.setPosition(1250, 425);
			return spriteLevelMiniOptionButton;
		}
		case 11: {
			spriteLevelMiniOptionButton.setTexture(textureMiniOptionButton4);
			spriteLevelMiniOptionButton.setPosition(1350, 425);
			return spriteLevelMiniOptionButton;
		}
	}
	return spriteMenu;
}

Sprite& Menu::GetSpriteMenu() { return spriteMenu; }

Sprite& Menu::GetSpriteOptionMenu() { return spriteOptionMenu; }

bool& Menu::GetIsMenu() { return is_Menu; }

bool& Menu::GetIsOption() { return is_Option; }

void Menu::SetIsMenu(bool state_menu) { is_Menu = state_menu; }

void Menu::SetIsOption(bool state_option) { is_Option = state_option; }