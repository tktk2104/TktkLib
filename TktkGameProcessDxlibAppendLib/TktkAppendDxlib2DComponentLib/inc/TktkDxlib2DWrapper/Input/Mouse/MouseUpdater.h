#ifndef MOUSE_UPDATER_H_
#define MOUSE_UPDATER_H_

#include <TktkMath/Vector2.h>

namespace tktk
{
	class MouseUpdater
	{
	public:

		MouseUpdater() = default;

	public:

		void update();

	public:

		Vector2 getCursorPoint();

		// �J�[�\���̈ʒu���w����W�Ɉړ�������
		void setCursorPoint(const Vector2& point);

		void showCursor();

		// �Q�[���E�B���h�E�̒��Ɍ����ă}�E�X�J�[�\�����\���ɂ���
		void hideCursor();

		// ������InputType��MouseButtonType�̗񋓌^�i�r�b�g�t���O�j
		bool getState(int inputType, int mouseButtonType);

		// �c�����̃}�E�X�z�C�[���̕ω��ʂ��擾�iint�j
		int getVerticalMouseWheel();

		// �c�����̃}�E�X�z�C�[���̕ω��ʂ��擾�ifloat�j
		float getVerticalMouseWheelF();

		// �������̃}�E�X�z�C�[���̕ω��ʂ��擾�iint�j
		int getHorizontalMouseWheel();

		// �E�������̃}�E�X�z�C�[���̕ω��ʂ��擾�ifloat�j
		float getHorizontalMouseWheelF();

	private:

		int m_curState;

		int m_preState;
	};
}
#endif // !MOUSE_UPDATER_H_
