#ifndef SCREEN_H_
#define SCREEN_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>

namespace tktk
{
	class Screen
	{
	public:

		// �f�B�X�v���C�̑傫�����擾
		static const Vector2& getDisplaySize();

		// �Q�[���X�N���[���̑傫�����擾
		static const Vector2& getGameScreenSize();

		// ���^�[�{�b�N�X�i�t���X�N���[�����̉�ʂ̗]���̃T�C�Y�j�̑傫�����擾
		static const Vector2& getLetterBoxSize();

		// ��ʂ̔w�i�F��ݒ肷��
		static void backgroundColor(const Color& color);
	};
}
#endif // !SCREEN_H_