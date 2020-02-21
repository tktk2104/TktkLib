#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Assets/TextureAssets/TextureAssets.h"
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"
#include "ReverseFlag.h"

namespace tktk
{
	// �X�v���C�g��`�悷��R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class SpriteDrawer
		: public ComponentBase
	{
	public:

		SpriteDrawer(
			int textureId,							// �\������e�N�X�`����Id
			int splitTextureIndex,					// �\������e�N�X�`���̕����ǂݍ��ݔԍ�
			float drawPriority,						// �`��D��x
			const Vector2& spriteCenterPosRate,		// �X�v���C�g�̒��S�ʒu�i���� 0.0�`1.0�j
			BlendMode blendMode,					// �`��̃u�����h���@�̎��
			float blendParam,						// �`��̃u�����h�Ɏg�p����l
			unsigned int reverseFlag,				// �`�悷��摜�𔽓]���邩
			bool useClipping,						// �ؔ����`����s�����H
			const Vector2& clippingLeftTopPos,		// �؂蔲��������W
			const Vector2& clippingRightBottomPos	// �؂蔲���E�����W
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// �e�N�X�`��ID���擾
		int getTextureId() const;
		// �e�N�X�`��ID�̍Đݒ�
		void setTextureId(int textureId);

		// �\������e�N�X�`���̕����ǂݍ��ݔԍ����擾
		int getSplitTextureIndex() const;
		// �\������e�N�X�`���̕����ǂݍ��ݔԍ����Đݒ�
		// -1����͂���Ɛ؂蔲�����ɕ`�悷��
		void setSplitTextureIndex(int splitTextureIndex);

		// �X�v���C�g�̒��S�ʒu�i���� 0.0�`1.0�j���擾
		const Vector2& getSpriteCenterPosRate() const;
		// �X�v���C�g�̒��S�ʒu�i���� 0.0�`1.0�j���Đݒ�
		void setSpriteCenterPosRate(const Vector2& spriteCenterPosRate = Vector2(0.5f, 0.5f));

		// �X�v���C�g��؂蔲���ĕ\������
		void useClipping(
			const Vector2& clippingLeftTopPos,		// �؂蔲��������W
			const Vector2& clippingRightBottomPos	// �؂蔲���E�����W
		);
		// �X�v���C�g��؂蔲���ĕ\������̂���߂�
		void unUseClipping();

		// �`��̃u�����h���@�̎�ނ��擾
		BlendMode getBlendMode() const;
		// �`��̃u�����h���@�̎�ނ��Đݒ�
		void setBlendMode(BlendMode blendMode);

		// �`��̃u�����h�Ɏg�p����l���擾
		float getBlendParam() const;
		// �`��̃u�����h�Ɏg�p����l���Đݒ�
		void setBlendParam(float blendParam);

		// �`�悷��摜�̔��]�t���O���Đݒ�
		void setReverseFlag(unsigned int reverseFlag);

		// �w�肵�������_�[�^�[�Q�b�g�ɕ`�悷��
		void useRenderTarget(int renderTargetId);
		// �����_�[�^�[�Q�b�g���g�p�����ɕ`�悷��
		void unUseRenderTarget();

	private:

		// ���g�̂Q�������W�R���|�[�l���g
		CfpPtr<Transform2D> m_transform2D;

		// �e�N�X�`�����\�[�X�̊Ǘ��N���X
		CfpPtr<TextureAssets> m_textureAssets;

		// �\������e�N�X�`����Id
		int m_textureId{ -1 };

		// �\������e�N�X�`���̕����ǂݍ��ݔԍ�
		int m_splitTextureIndex{ -1 };

		// �X�v���C�g�̒��S�ʒu�i���� 0.0�`1.0�j
		Vector2 m_spriteCenterPosRate{ Vector2(0.5f, 0.5f) };

		// �`��̃u�����h���@�̎��
		BlendMode m_blendMode;

		// �`��̃u�����h�Ɏg�p����l
		float m_blendParam;

		// ���]�t���O
		unsigned int m_reverseFlag{ NOT_REVERSE };

		// �e�N�X�`���̐ؔ������s����
		bool m_useClipping{ false };

		// �e�N�X�`���̐ؔ����Ɏg�p���鍶����W
		Vector2 m_clippingLeftTopPos{ Vector2::zero };

		// �e�N�X�`���̐ؔ����Ɏg�p����E�����W
		Vector2 m_clippingRightBottomPos{ Vector2::one };

		// �����_�[�^�[�Q�b�g�ɕ`�悷�邩
		bool m_useRenderTarget{ false };

		// �`�悷�郌���_�[�^�[�Q�b�g��Id
		int m_renderTargetId{ -1 };
	};
}
#endif // !SPRITE_DRAWER_H_