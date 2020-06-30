#ifndef MOUSE_UPDATER_H_
#define MOUSE_UPDATER_H_

#include <unordered_map>
#include <TktkMath/Structs/Vector2.h>
#include "MouseButtonType.h"

namespace tktk
{
	class Mouse
	{
	public:

		Mouse();
		~Mouse() = default;

		// �R�s�[�֎~
		Mouse(const Mouse& other) = delete;
		Mouse& operator = (const Mouse& other) = delete;

	public:

		void update();

	public:

		// �w��̃{�^����������Ă��邩
		bool isPush(MouseButtonType buttonType) const;

		// �w��̃{�^����������n�߂����𔻒�
		bool isTrigger(MouseButtonType buttonType) const;

		// �}�E�X�J�[�\���̍��W���擾����
		tktkMath::Vector2 mousePos() const;

	private:

		std::unordered_map<MouseButtonType, bool> m_curMouseButtonState;
		std::unordered_map<MouseButtonType, bool> m_preMouseButtonState;
	};
}
#endif // !MOUSE_UPDATER_H_
