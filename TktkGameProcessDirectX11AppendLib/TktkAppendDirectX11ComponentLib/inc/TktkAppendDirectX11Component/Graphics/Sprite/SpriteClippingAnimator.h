#ifndef SPRITE_CLIPPING_ANIMATOR_H_
#define SPRITE_CLIPPING_ANIMATOR_H_

#include <vector>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "SpriteClippingDrawer.h"

namespace tktk
{
	class SpriteClippingAnimator
		: public ComponentBase
	{
	public:

		SpriteClippingAnimator(
			const std::vector<Vector2>& animationFrameTexturePosArray,
			float animationIntervalSec,
			bool isLoop,
			float animSpeedRate
		);

	public:

		void start();
		void update();

	public:

		// �A�j���[�V�������I�����������擾
		bool isEndAnimation() const;

		// �A�j���[�V�����̃R�}���Ƃ̃e�N�X�`���̃N���b�s���O�`��͈͂̍�����W���Đݒ�
		void setAnimFrameTextureLeftTopPosArray(const std::vector<Vector2>& posArray);

		// �A�j���[�V�����̃R�}���Ƃ̃e�N�X�`���̃N���b�s���O�`��͈͂̍�����W���擾
		const std::vector<Vector2>& getAnimFrameTextureLeftTopPosArray() const;

		// �A�j���[�V�����̍Đ����x���Đݒ�
		void setAnimSpeedRate(float animSpeedRate);

		// �A�j���[�V�����̍Đ����x���擾
		float getAnimSpeedRate() const;

		// �A�j���[�V���������[�v�����邩���Đݒ�
		void setIsLoop(bool isLoop);

		// �A�j���[�V�����̃��[�v�t���O���擾
		bool getIsLoop() const;

	private:

		std::vector<Vector2> m_animFrameTextureLeftTopPosArray{  };
		float m_animSpeedRate{ 1.0f };
		float m_animationTimer{ 0.0f };
		float m_animationTotalTime{ 0.0f };
		float m_animationIntervalSec{ 1.0f };
		bool m_isLoop{ true };

		CfpPtr<SpriteClippingDrawer> m_spriteClippingDrawer{  };
	};
}
#endif // !SPRITE_CLIPPING_ANIMATOR_H_