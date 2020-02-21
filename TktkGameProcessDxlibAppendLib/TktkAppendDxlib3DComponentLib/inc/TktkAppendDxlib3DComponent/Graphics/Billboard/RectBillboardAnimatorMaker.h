#ifndef RECT_BILLBOARD_ANIMATOR_MAKER_H_
#define RECT_BILLBOARD_ANIMATOR_MAKER_H_

#include <vector>
#include "RectBillboardAnimator.h"

namespace tktk
{
	class RectBillboardAnimatorMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static RectBillboardAnimatorMaker& makeStart();

	public:

		// �쐬����
		RectBillboardAnimator* create();

		// �g�p����e�N�X�`����Id��ݒ肷��
		RectBillboardAnimatorMaker& textureId(int value);

		// �A�j���[�V�����Ɏg�p���镪���摜�ԍ���ݒ肷��
		template <int... Args>
		RectBillboardAnimatorMaker& splitTextureIndexList()
		{
			m_splitTextureIndexList = std::vector<int>({ Args... });
			return *this;
		};

		// �A�j���[�V�����Ŏg�p����Î~��P��������̎��Ԃ�ݒ肷��i�b�j
		RectBillboardAnimatorMaker& animationIntervalSec(float value);

		// �A�j���[�V���������[�v�����邩��ݒ肷��
		RectBillboardAnimatorMaker& loop(bool value);

		// �A�j���[�V�����̍Đ����x�{����ݒ肷��
		RectBillboardAnimatorMaker& animSpeedRate(float value);

	private:

		// ���g�̃|�C���^
		static RectBillboardAnimatorMaker m_self;

	private:

		int m_textureId{ -1 };
		std::vector<int> m_splitTextureIndexList;
		float m_animationIntervalSec{ 0.1f };
		bool m_loop{ false };
		float m_animSpeedRate{ 1.0f };
	};
}
#endif // !RECT_BILLBOARD_ANIMATOR_MAKER_H_