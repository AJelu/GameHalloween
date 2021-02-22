#include "Unit.h"

Unit::Unit(FloatRect rectangle)
{
	m_Current_Frame = 0;
	speed_x = 0.1f;
	speed_y = 0.1f;
	live = true;
	on_Ground = false;
	mRect = rectangle;
}

Sprite& Unit::GetSpriteUnit() { return mSprite; }

FloatRect Unit::GetRectangle()
{
	return FloatRect(mRect.left, mRect.top, mRect.width, mRect.height);
}