#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu {
private:
	Texture textureMenuButton1, textureMenuButton2, textureMenuButton3, 
			 textureMenu, textureOptionMenu;

	Texture textureOptionButton1, textureOptionButton2,
			textureMiniOptionButtonON, textureMiniOptionButtonOFF,
			textureMiniOptionButton1, textureMiniOptionButton2,
			textureMiniOptionButton3, textureMiniOptionButton4;

	Sprite spriteMenuButton, spriteOptionButton, spriteMiniOptionButton, 
			spriteLevelMiniOptionButton, spriteMenu, spriteOptionMenu;

	bool is_Menu;
	bool is_Option;
	int number_Menu;

public:
	Menu();
	Sprite&	GetSpriteButton(int const& number_button);
	Sprite& GetSpriteMenu();
	Sprite& GetSpriteOptionMenu();

	void SetCursorVisible(RenderWindow& window, bool visible);
	
	void SetIsMenu(bool state_menu);
	void SetIsOption(bool state_option);
	void SetNumberMenu(int const& state_menu);

	int& GetNumberMenu();
	bool& GetIsMenu();
	bool& GetIsOption();
};