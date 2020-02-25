#ifndef SPRITE_ANIMATOR_MAKER_H_
#define SPRITE_ANIMATOR_MAKER_H_

#include <vector>
#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SpriteAnimator.h"

namespace tktk
{
	class SpriteAnimatorMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static SpriteAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<SpriteAnimator> create();

		// �g�p����e�N�X�`����Id��ݒ肷��
		SpriteAnimatorMaker& textureId(int value);

		// �A�j���[�V�����Ɏg�p���镪���摜�ԍ���ݒ肷��
		template <int... Args>
		SpriteAnimatorMaker& splitTextureIndexList()
		{
			m_splitTextureIndexList = std::vector<int>({ Args... });
			return *this;
		};

		// �A�j���[�V�����Ŏg�p����Î~��P��������̎��Ԃ�ݒ肷��i�b�j
		SpriteAnimatorMaker& animationIntervalSec(float value);

		// �A�j���[�V���������[�v�����邩��ݒ肷��
		SpriteAnimatorMaker& loop(bool value);

		// �A�j���[�V�����̍Đ����x�{����ݒ肷��
		SpriteAnimatorMaker& animSpeedRate(float value);

	private:

		// ���g�̃|�C���^
		static SpriteAnimatorMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		int m_textureId{ -1 };
		std::vector<int> m_splitTextureIndexList{ };
		float m_animationIntervalSec{ 0.1f };
		bool m_loop{ false };
		float m_animSpeedRate{ 1.0f };
	};
}
#endif // !SPRITE_ANIMATOR_MAKER_H_