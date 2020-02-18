#ifndef SPRITE_CONSTANT_BUFFER_DATA_H_
#define SPRITE_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>

namespace tktk
{
	// �f�t�H���g�̃X�v���C�g�`��̒萔�o�b�t�@�̌`��
	struct SpriteConstantBufferData
	{
		Vector2 texturePosition{ Vector2::zero };

		Vector2 textureSize{ Vector2::zero };

		Vector2 size{ Vector2::one };

		Vector2 position{ Vector2::zero };

		Vector2 scaleRate{ Vector2::one };

		float	angleDeg{ 0.0f };

		float	padding{ 0.0f };

		Color	color{ Color::white };

		Vector2 center{ Vector2::zero };

		Vector2 screen{ 640.0f, 480.0f };
	};
}
#endif // !SPRITE_CONSTANT_BUFFER_DATA_H_