#pragma once

#include "Model.h"

class Bitmap : public Model {
public:
	Bitmap(float width, float height, Vector textureTopLeft, Vector textureBottomRight);
	Bitmap(float width, float height);
};