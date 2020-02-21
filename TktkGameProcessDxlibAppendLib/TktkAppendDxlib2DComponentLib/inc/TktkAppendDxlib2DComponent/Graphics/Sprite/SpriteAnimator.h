#ifndef SPRITE_ANIMATOR_H_
#define SPRITE_ANIMATOR_H_

#include <vector>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "SpriteDrawer.h"

namespace tktk
{
	// SpritesDrawer�̉摜���A�j���[�V����������
	// �y�O��R���|�[�l���g�FSprite2dDrawer�z
	class SpriteAnimator
		: public ComponentBase
	{
	public:

		SpriteAnimator(
			int textureId,									// �A�j���[�V�����Ŏg�p����摜�̎��
			const std::vector<int>& splitTextureIndexList,	// �A�j���[�V�����Ŏg�p����摜�����ԍ��̔z��
			float animationIntervalSec,						// �A�j���[�V�����ŉ摜���؂�ւ��Ԋu�i�b�j
			bool isLoop,									// �A�j���[�V���������[�v�����邩�H
			float animSpeedRate								// �A�j���[�V�����̍Đ��{��
		);

	public:

		// <PolymorphismFunc>
		void start();
		void update();

	public:

		// �A�j���[�V�������I�����������擾
		bool isEndAnimation() const;

		// �A�j���[�V�����Ŏg�p����摜�̎�ނ��Đݒ�
		void setTextureId(int textureId);

		// �A�j���[�V�����Ŏg�p����摜�̎�ނ��擾
		int getTextureId() const;

		// �A�j���[�V�����Ɏg�p���镪���摜�ԍ��̃��X�g���Đݒ�
		void setSplitTextureIndexList(const std::vector<int>& splitTextureIndexList);

		// �A�j���[�V�����Ɏg�p���镪���摜�ԍ��̃��X�g���Đݒ�
		template <int... Args>
		void setSplitTextureIndexList()
		{
			setSplitTextureIndexList(std::vector<int>({ Args... }));
		};

		// �A�j���[�V�����Ɏg�p���镪���摜�ԍ��̃��X�g��ݒ�
		const std::vector<int>& getSplitTextureIndexList() const;

		// �A�j���[�V�����̍Đ����x���Đݒ�
		void setAnimSpeedRate(float animSpeedRate);

		// �A�j���[�V�����̍Đ����x���擾
		float getAnimSpeedRate() const;

		// �A�j���[�V���������[�v�����邩���Đݒ�
		void setIsLoop(bool isLoop);

		// �A�j���[�V�����̃��[�v�t���O���擾
		bool getIsLoop() const;

	private:

		// ���g�̂Q�����`��R���|�[�l���g
		CfpPtr<SpriteDrawer> m_spriteDrawer;

		// �g�p����e�N�X�`����Id
		int m_textureId{ -1 };

		// �A�j���[�V�����Ɏg�p���镪���摜�ԍ��̃��X�g
		std::vector<int> m_splitTextureIndexList;

		// �A�j���[�V�����̍Đ����x�{��
		float m_animSpeedRate{ 1.0f };

		// �A�j���[�V�����̌o�ߎ��ԁi�b�j
		float m_animationTimer{ 0.0f };

		// �A�j���[�V�����̍��v���ԁi�b�j
		float m_animationTotalTime{ 0.0f };

		// �A�j���[�V�����Ŏg�p����Î~��P��������̎��ԁi�b�j
		float m_animationIntervalSec;

		// �A�j���[�V�����̃��[�v�t���O
		bool m_isLoop;
	};
}
#endif // !SPRITE_ANIMATOR_H_