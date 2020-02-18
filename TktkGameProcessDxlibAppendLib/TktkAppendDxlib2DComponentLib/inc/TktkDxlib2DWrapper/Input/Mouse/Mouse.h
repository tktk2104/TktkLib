#ifndef MOUSE_H_
#define MOUSE_H_

#include <TktkMath/Vector2.h>
#include "../InputType.h"
#include "MouseButtonType.h"

namespace tktk
{
	class Mouse
	{
	public:

		static Vector2 getCursorPoint();

		// �J�[�\���̈ʒu���w����W�Ɉړ�������
		static void setCursorPoint(const Vector2& point);

		static void showCursor();

		// �Q�[���E�B���h�E�̒��Ɍ����ă}�E�X�J�[�\�����\���ɂ���
		static void hideCursor();

		// ������InputType��MouseButtonType�̗񋓌^�i�r�b�g�t���O�j
		static bool getState(int inputType, int mouseButtonType);

		// �c�����̃}�E�X�z�C�[���̕ω��ʂ��擾�iint�j
		static int getVerticalMouseWheel();

		// �c�����̃}�E�X�z�C�[���̕ω��ʂ��擾�ifloat�j
		static float getVerticalMouseWheelF();

		// �������̃}�E�X�z�C�[���̕ω��ʂ��擾�iint�j
		static int getHorizontalMouseWheel();

		// �E�������̃}�E�X�z�C�[���̕ω��ʂ��擾�ifloat�j
		static float getHorizontalMouseWheelF();
	};
}

#endif // !MOUSE_H_