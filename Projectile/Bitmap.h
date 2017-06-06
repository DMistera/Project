#pragma once

#include "Model.h"
#include "Vector2.h"

class Bitmap : public Model {
public:
	Bitmap(float width, float height, Vector2 textureTopLeft, Vector2 textureBottomRight);
	Bitmap(float width, float height);
};