#ifndef KEY_BOARD_UPDATER_H_
#define KEY_BOARD_UPDATER_H_

#include <array>
#define DIRECTINPUT_VERSION     0x0800
#include <dinput.h>
#include "KeybordKeyType.h"
#include <Windows.h>
#undef min
#undef max

namespace tktk
{
	// �L�[�{�[�h�̓��͂����m����N���X
	class Keyboard
	{
	public:

		Keyboard(HINSTANCE hInstance, HWND handle);
		~Keyboard();

		Keyboard(const Keyboard& other) = delete;
		Keyboard& operator = (const Keyboard& other) = delete;

	public:

		void update();

	public:

		// �w��̃L�[��������Ă��邩�𔻒�
		bool isPush(KeybordKeyType keyType);

		// �w��̃L�[��������n�߂����𔻒�
		bool isTrigger(KeybordKeyType keyType);

	private:

		// �C���v�b�g
		LPDIRECTINPUT8 m_input;

		// �C���v�b�g�f�o�C�X
		LPDIRECTINPUTDEVICE8 m_inputDevice;

		// ���݂̃L�[���͏��
		std::array<unsigned char, 256U> m_curKeys;

		// �O�t���[���̃L�[���͏��
		std::array<unsigned char, 256U> m_preKeys;
	};
}
#endif // !KEY_BOARD_UPDATER_H_