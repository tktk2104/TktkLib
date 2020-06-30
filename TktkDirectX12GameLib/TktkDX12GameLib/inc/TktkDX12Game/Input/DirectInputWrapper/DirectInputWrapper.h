#ifndef DIRECT_INPUT_WRAPPER_H_
#define DIRECT_INPUT_WRAPPER_H_

#include <memory>
#include <Windows.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>
#include "DirectInputIncluder.h"
#include "Keyboard/KeybordKeyType.h"
#include "GamePad/GamePadBtnType.h"

namespace tktk
{
	class Keyboard;
	class GamePad;

	class DirectInputWrapper
	{
	public:

		DirectInputWrapper(HINSTANCE hInstance, HWND handle);
		~DirectInputWrapper();

	public:

		void update();

	public: /* �L�[�{�[�h�֘A�̏��� */

		// �w��̃L�[��������Ă��邩�𔻒�
		bool isPush(KeybordKeyType keyType);

		// �w��̃L�[��������n�߂����𔻒�
		bool isTrigger(KeybordKeyType keyType);

	public: /* �Q�[���p�b�h�֘A�̏��� */

		// ���X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		tktkMath::Vector2 getLstick() const;

		// �E�X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		tktkMath::Vector2 getRstick() const;

		// �w��̃{�^����������Ă��邩�𔻒�
		bool isPush(GamePadBtnType btnType) const;

		// �w��̃{�^����������n�߂����𔻒�
		bool isTrigger(GamePadBtnType btnType) const;

	private:

		// �C���v�b�g
		LPDIRECTINPUT8 m_input;

		// �L�[�{�[�h
		std::unique_ptr<Keyboard>	m_keyboard;

		// �Q�[���p�b�h
		std::unique_ptr<GamePad>	m_gamePad;
	};
}
#endif // !DIRECT_INPUT_WRAPPER_H_