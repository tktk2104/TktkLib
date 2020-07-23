#ifndef SPRITE_MATERIAL_INIT_PARAM_H_
#define SPRITE_MATERIAL_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkDX12Wrapper/Resource/Buffer/BufferType.h>

namespace tktk
{
	// �X�v���C�g�}�e���A�������Ƃ��ɕK�v�ȏ��
	struct SpriteMaterialInitParam
	{
		// ���f�B�X�N���v�^�q�[�v��ID
		unsigned int		createDescriptorHeapId;

		// �`�悷��o�b�t�@�[�̎��
		BufferType			srvBufferType;

		// �`�悷��o�b�t�@�[��ID
		unsigned int		useBufferId;

		// �u�����h�l
		tktkMath::Color		blendRate		{ 1.0f, 1.0f, 1.0f, 1.0f };

		// �e�N�X�`��UV�̃I�t�Z�b�g
		tktkMath::Vector2	textureUvOffset	{ 0.0f, 0.0f };

		// �e�N�X�`��UV�ɏ�Z����l
		tktkMath::Vector2	textureUvMulRate{ 1.0f, 1.0f };

		// �X�v���C�g�̒��S�_�i�����j
		tktkMath::Vector2	spriteCenterRate{ 0.5f, 0.5f };
	};
}
#endif // !SPRITE_MATERIAL_INIT_PARAM_H_