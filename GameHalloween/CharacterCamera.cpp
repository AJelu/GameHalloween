#include "Unit.h"

View& Character::GetCamera() { return camera; }

View Character::SetCameraCoordinates(const float& x, const float& y)
{
	float tempX = x; float tempY = y;

	/* Control the edges over the field of view of the map: */
	if (x < 850) tempX = 850; //left edge
	if (x > 1080) tempX = 1080; //right edge
	if (y < 520) tempY = 520; //upper edge
	if (y > 725) tempY = 725; //lower edge

	camera.setCenter(tempX, tempY);
	return camera;
}