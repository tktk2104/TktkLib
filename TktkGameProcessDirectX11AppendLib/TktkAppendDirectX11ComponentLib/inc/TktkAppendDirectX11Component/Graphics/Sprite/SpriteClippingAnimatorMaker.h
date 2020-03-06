#ifndef SPRITE_CLIPPING_ANIMATOR_MAKER_H_
#define SPRITE_CLIPPING_ANIMATOR_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SpriteClippingAnimator.h"

namespace tktk
{
	class SpriteClippingAnimatorMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static SpriteClippingAnimatorMaker& makeStart(GameObjectPtr user);

	private:

		// ���g�̃|�C���^
		static SpriteClippingAnimatorMaker m_self;

	private:

		// �v���C�x�[�g�R���X�g���N�^�B
		SpriteClippingAnimatorMaker() = default;
		SpriteClippingAnimatorMaker(const SpriteClippingAnimatorMaker& other) = default;
		SpriteClippingAnimatorMaker& operator = (const SpriteClippingAnimatorMaker& other) = default;

	public:

		// �쐬����
		CfpPtr<SpriteClippingAnimator> create();

		// �A�j���[�V�����̃R�}���Ƃ̃e�N�X�`���̃N���b�s���O�`��͈͂̍�����W��ݒ�
		SpriteClippingAnimatorMaker& animFrameTextureLeftTopPosArray(const std::vector<Vector2>& value);

		// �A�j���[�V�����P�R�}�ɂ����鎞�Ԃ�ݒ�
		SpriteClippingAnimatorMaker& animationIntervalSec(float value);

		// �A�j���[�V���������[�v�����邩��ݒ�
		SpriteClippingAnimatorMaker& isLoop(bool value);

		// �A�j���[�V�����̍Đ����x��ݒ�
		SpriteClippingAnimatorMaker& animSpeedRate(float value);

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		std::vector<Vector2> m_animFrameTextureLeftTopPosArray{  };
		float m_animationIntervalSec{ 1.0f };
		bool m_isLoop{ true };
		float m_animSpeedRate{ 1.0f };
	};
}
#endif // !SPRITE_CLIPPING_ANIMATOR_MAKER_H_
