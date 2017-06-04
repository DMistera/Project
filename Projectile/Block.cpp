#include "Block.h"

Block::Block() : Sprite(
	new Texture("Resources//Textures//green.dds"),
	new TextureShader(),
	new Bitmap(200.0f, 200.0f)) {
}
