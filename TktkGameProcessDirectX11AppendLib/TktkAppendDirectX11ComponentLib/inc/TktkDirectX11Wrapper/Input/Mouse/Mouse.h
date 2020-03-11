#ifndef MOUSE_H_
#define MOUSE_H_

#include <TktkMath/Vector2.h>
#include "MouseButtonType.h"

namespace tktk
{
	// �uMouseManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Mouse
	{
	public:

		// �w��̃{�^����������Ă��邩�𔻒�
		static bool isPush(MouseButtonType button);

		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(MouseButtonType button);

		// �}�E�X�J�[�\���̍��W���擾����
		static Vector2 mousePos();
	};
}
#endif // !MOUSE_H_