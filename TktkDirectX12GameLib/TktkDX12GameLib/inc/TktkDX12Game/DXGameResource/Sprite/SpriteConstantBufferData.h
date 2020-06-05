#ifndef SPRITE_CONSTANT_BUFFER_DATA_H_
#define SPRITE_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	struct SpriteConstantBufferData
	{
		float				worldMatrix[12]		{};

		tktkMath::Color		blendRate			{ 1.0f, 1.0f, 1.0f, 1.0f };

		tktkMath::Vector2	textureUvOffset		{ 0.0f, 0.0f };

		tktkMath::Vector2	textureUvMulRate	{ 0.0f, 0.0f };

		tktkMath::Vector2	textureSize			{ tktkMath::vec2One };

		tktkMath::Vector2	spriteCenterRate	{ 0.0f, 0.0f };

		tktkMath::Vector2	screenSize			{ 640.0f, 480.0f };

		float				pad[2]				{};
	};
}
#endif // !SPRITE_CONSTANT_BUFFER_DATA_H_