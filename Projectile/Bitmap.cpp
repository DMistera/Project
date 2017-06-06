#include "Bitmap.h"

Bitmap::Bitmap(float width, float height, Vector2 textureTopLeft, Vector2 textureBottomRight) : Model(
	new D3DXVECTOR3[4] { D3DXVECTOR3(width/2, height/2, 0.0f) , D3DXVECTOR3(width/2, -height/2, 0.0f) , D3DXVECTOR3(-width/2, -height/2, 0.0f) , D3DXVECTOR3(-width/2, height/2, 0.0f) },
	new unsigned long[6] {0 , 1, 2, 3, 0, 2},
	new D3DXVECTOR2[4] { 
		D3DXVECTOR2(textureBottomRight.getX(), textureTopLeft.getY()) ,
		D3DXVECTOR2(textureBottomRight.getX(), textureBottomRight.getY()) ,
		D3DXVECTOR2(textureTopLeft.getX(), textureBottomRight.getY()) ,
		D3DXVECTOR2(textureTopLeft.getX(), textureTopLeft.getY()) },
	4, 6) {

}

Bitmap::Bitmap(float width, float height) : Bitmap(width, height, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f)) {

}

