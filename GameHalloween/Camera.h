#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class CameraControl {
private:
	View camera; //������ ������

public:
	View getCharacterCoordinates(float x, float y);
	View getCamera();
};

