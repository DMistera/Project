#pragma once

#include "Model.h"
#include "Vector3.h"

class Bitmap : public Model {
public:
	Bitmap(float width, float height, Vector3 textureTopLeft, Vector3 textureBottomRight);
	Bitmap(float width, float height);
};