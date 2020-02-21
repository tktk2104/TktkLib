#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "ScreenUpdater.h"

namespace tktk
{
	class ScreenManager
	{
	public:

		static void setUp(
			const Vector2& gameScreenSize,
			bool fullScreen
		);

		// �f�B�X�v���C�̑傫�����擾
		static const Vector2& getDisplaySize();

		// �Q�[���X�N���[���̑傫�����擾
		static const Vector2& getGameScreenSize();

		// ���^�[�{�b�N�X�i�t���X�N���[�����̉�ʂ̗]���̃T�C�Y�j�̑傫�����擾
		static const Vector2& getLetterBoxSize();

		// ��ʂ̔w�i�F��ݒ肷��
		static void backgroundColor(const Color& color);

	private:

		static CfpPtr<ScreenUpdater> m_screenUpdater;
	};
}
#endif // !SCREEN_MANAGER_H_