#ifndef MOUSE_BUTTON_TYPE_H_
#define MOUSE_BUTTON_TYPE_H_

namespace tktk
{
	// �}�E�X�̃{�^���̎��
	enum MouseButtonType
	{
		MOUSE_LEFT_BUTTON	= 1 << 0,	// ���}�E�X�{�^��
		MOUSE_RIGHT_BUTTON	= 1 << 1,	// �E�}�E�X�{�^��
		MOUSE_MIDDLE_BUTTON = 1 << 2	// �}�E�X�z�C�[����������
	};
}
#endif // !MOUSE_BUTTON_TYPE_H_