#ifndef SCREEN_UPDATER_H_
#define SCREEN_UPDATER_H_

#include <memory>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include "../RenderTarget/RenderTargetUpdater.h"

namespace tktk
{
	class ScreenUpdater
	{
	public:

		ScreenUpdater(
			const Vector2& gameScreenSize,
			bool fullScreen
		);

	public:

		void awake();
		void start();
		void onDestroy();
		void update();
		void draw();
		void frameEnd();
		float getUpdatePriority();
		float getDrawPriority();

	public:

		// �f�B�X�v���C�̑傫�����擾
		const Vector2& getDisplaySize() const;

		// �Q�[���X�N���[���̑傫�����擾
		const Vector2& getGameScreenSize() const;

		// ���^�[�{�b�N�X�i�t���X�N���[�����̉�ʂ̗]���̃T�C�Y�j�̑傫�����擾
		const Vector2& getLetterBoxSize() const;

		// ��ʂ̔w�i�F��ݒ肷��
		void backgroundColor(const Color& color);

	private:

		void calculateLetterBoxSize();

	private:

		// �f�B�X�v���C�̑傫��
		Vector2 m_displaySize;
		// �Q�[���X�N���[���̑傫��
		Vector2 m_gameScreenSize;
		// ���^�[�{�b�N�X�i�t���X�N���[�����̉�ʂ̗]���̃T�C�Y�j�̑傫��
		Vector2 m_letterBoxSize{ Vector2::zero };

		bool m_fullScreen;
	};
}
#endif // !SCREEN_UPDATER_H_
