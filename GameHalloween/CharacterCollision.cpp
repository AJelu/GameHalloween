#include "Unit.h"
#include "Map.h"

void Character::Collision(int const& position)
{
	for (int i = int(mRect.top / 32); i < (mRect.top + mRect.height) / 32; i++) {
		for (int j = int(mRect.left / 32); j < (mRect.left + mRect.width) / 32; j++) {
			//Collision with border and with pumpkin
			if ((TileMap[i][j] == 'D') || (TileMap[i][j] == 'P')) {
				if ((speed_x > 0) && (position == 1)) mRect.left = j * 32 - mRect.width;
				if ((speed_x < 0) && (position == 1)) mRect.left = float(j * 32 + 32);
				if ((speed_y > 0) && (position == 2)) {
					mRect.top = i * 32 - mRect.height;
					speed_y = 0;
					on_Ground = true;
				}
				if ((speed_y < 0) && (position == 2)) {
					speed_y = 0;
					mRect.top = float(i * 32 + 32);
				}
			}

			//Jump to next level
			if (TileMap[i][j] == 'L') {
				TileMap[i][j] = ' ';
				character_Map_Level += 1;
				mRect.left = 100.0;
				mRect.top = 920.0;
			}

			//Collision with potion
			if (TileMap[i][j] == 'H') {
				TileMap[i][j] = ' ';
				character_Life += 1;
			}
		}
	}
}