#ifndef MOUSE_UPDATER_H_
#define MOUSE_UPDATER_H_

#include <unordered_map>
#include <TktkMath/Vector2.h>
#include "MouseButtonType.h"

namespace tktk
{
	class MouseUpdater
	{
	public:

		MouseUpdater();
		~MouseUpdater() = default;

		// �R�s�[�֎~
		MouseUpdater(const MouseUpdater& other) = delete;
		MouseUpdater& operator = (const MouseUpdater& other) = delete;

	public:

		void update();

	public:

		// �w��̃{�^����������Ă��邩
		bool isPush(MouseButtonType buttonType) const;

		// �w��̃{�^����������n�߂����𔻒�
		bool isTrigger(MouseButtonType buttonType) const;

		// �}�E�X�J�[�\���̍��W���擾����
		Vector2 mousePos() const;

	private:

		std::unordered_map<MouseButtonType, bool> m_curMouseButtonState;
		std::unordered_map<MouseButtonType, bool> m_preMouseButtonState;
	};
}
#endif // !MOUSE_UPDATER_H_
