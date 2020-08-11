#ifndef SPRITE_CONSTANT_BUFFER_DATA_H_
#define SPRITE_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// �X�v���C�g�`��Ɏg�p����萔�o�b�t�@���
	struct SpriteConstantBufferData
	{
		// ���[���h�s��ihsls�̎d�l��Afloat4x3�j
		float				worldMatrix[12]		{};

		// �u�����h���[�g
		tktkMath::Color		blendRate			{ 1.0f, 1.0f, 1.0f, 1.0f };

		// �e�N�X�`��UV�̃I�t�Z�b�g�l
		tktkMath::Vector2	textureUvOffset		{ 0.0f, 0.0f };

		// �e�N�X�`��UV�ɏ�Z����l
		tktkMath::Vector2	textureUvMulRate	{ 0.0f, 0.0f };

		// �e�N�X�`���̃T�C�Y�i�s�N�Z���j
		tktkMath::Vector2	textureSize			{ tktkMath::Vector2_v::one };

		// �X�v���C�g�̒��S�_�i�����j
		tktkMath::Vector2	spriteCenterRate	{ 0.0f, 0.0f };

		// �X�N���[���T�C�Y
		tktkMath::Vector2	screenSize			{ 640.0f, 480.0f };

		// �p�f�B���O
		float				pad[2]				{};
	};
}
#endif // !SPRITE_CONSTANT_BUFFER_DATA_H_