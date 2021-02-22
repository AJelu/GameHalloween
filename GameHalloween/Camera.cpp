#include "Camera.h"

View CameraControl::getCharacterCoordinates(float x, float y)
{
	camera.setCenter(x + 100, y); //следим за игроком передавая его координаты
	return camera;
}

View CameraControl::getCamera() { return camera; }
