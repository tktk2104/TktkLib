#ifndef SPRITE_CONSTANT_BUFFER_DATA_H_
#define SPRITE_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>

namespace tktk
{
	// デフォルトのスプライト描画の定数バッファの形式
	struct SpriteConstantBufferData
	{
		Vector2 textureUvOffset{ 0.0f, 0.0f };

		Vector2 textureUvMulRate{ 0.0f, 0.0f };

		Vector2 textureSize{ Vector2::one };

		Vector2 spritePosition{ Vector2::zero };

		Vector2 spriteScaleRate{ Vector2::one };

		float	spriteAngleDeg{ 0.0f };

		float	padding{ 0.0f };

		Color	blendRate{ 1.0f, 1.0f, 1.0f, 1.0f };

		Vector2 spriteCenterRate{ 0.0f, 0.0f };

		Vector2 screenSize{ 640.0f, 480.0f };
	};
}
#endif // !SPRITE_CONSTANT_BUFFER_DATA_H_