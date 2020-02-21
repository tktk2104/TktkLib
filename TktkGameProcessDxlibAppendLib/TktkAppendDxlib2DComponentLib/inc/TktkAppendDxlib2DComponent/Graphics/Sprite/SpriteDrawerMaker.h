#ifndef SPRITE_DRAWER_MAKER_H_
#define SPRITE_DRAWER_MAKER_H_

#include "SpriteDrawer.h"

namespace tktk
{
	// SpriteDrawer�̃C���X�^���X���쐬����\����
	struct SpriteDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static SpriteDrawerMaker& makeStart();

	public:

		// �쐬����
		SpriteDrawer* create();

		// �\������e�N�X�`����Id��ݒ肷��
		SpriteDrawerMaker& textureId(int value);

		// �\������e�N�X�`���̕����ǂݍ��ݔԍ���ݒ肷��
		SpriteDrawerMaker& splitTextureIndex(int value = -1);

		// �`��D��x��ݒ肷��
		SpriteDrawerMaker& drawPriority(float value);

		// �X�v���C�g�̒��S�ʒu��ݒ肷��i���� 0.0�`1.0�j
		SpriteDrawerMaker& spriteCenterPosRate(const Vector2& value = Vector2(0.5f, 0.5f));

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		SpriteDrawerMaker& blendMode(BlendMode value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		SpriteDrawerMaker& blendParam(float value = 1.0f);

		// �\������e�N�X�`���̔��]�t���O��ݒ肷��
		SpriteDrawerMaker& reverseFlag(ReverseFlag value);

		// �\������e�N�X�`���̐ؔ����`��͈͂�ݒ肷��
		SpriteDrawerMaker& useClipping(
			const Vector2& clippingLeftTopPos,		// �؂蔲��������W
			const Vector2& clippingRightBottomPos	// �؂蔲���E�����W
		);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		SpriteDrawerMaker& renderTargetId(int value);

	private:

		// ���g�̃|�C���^
		static SpriteDrawerMaker m_self;

	private:

		int m_textureId{ -1 };
		int m_splitTextureIndex{ -1 };
		float m_drawPriority{ 0 };
		Vector2 m_spriteCenterPosRate{ Vector2(0.5f, 0.5f) };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		ReverseFlag m_reverseFlag{ ReverseFlag::NOT_REVERSE };
		bool m_useClipping{ false };
		Vector2 m_clippingLeftTopPos{ Vector2::zero };
		Vector2 m_clippingRightBottomPos{ Vector2::one };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_