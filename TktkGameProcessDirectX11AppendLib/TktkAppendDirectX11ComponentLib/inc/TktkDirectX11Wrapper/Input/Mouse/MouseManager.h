#ifndef MOUSE_MANAGER_H_
#define MOUSE_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "MouseUpdater.h"
#include "MouseButtonType.h"

namespace tktk
{
	// �uMouseUpdater�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class MouseManager
	{
	public:

		// �uMouseUpdater�v�𐶐�
		static void setUp();

	public:

		// �w��̃{�^����������Ă��邩�𔻒�
		static bool isPush(MouseButtonType button);

		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(MouseButtonType button);

		// �}�E�X�J�[�\���̍��W���擾����
		static Vector2 mousePos();

	private:

		static CfpPtr<MouseUpdater> m_updaterPtr;
	};
}
#endif // !MOUSE_MANAGER_H_