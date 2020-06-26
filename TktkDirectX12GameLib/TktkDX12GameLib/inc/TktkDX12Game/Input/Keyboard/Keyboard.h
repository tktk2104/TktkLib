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
	// キーボードの入力を検知するクラス
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

		// 指定のキーが押されているかを判定
		bool isPush(KeybordKeyType keyType);

		// 指定のキーが押され始めたかを判定
		bool isTrigger(KeybordKeyType keyType);

	private:

		// インプット
		LPDIRECTINPUT8 m_input;

		// インプットデバイス
		LPDIRECTINPUTDEVICE8 m_inputDevice;

		// 現在のキー入力情報
		std::array<unsigned char, 256U> m_curKeys;

		// 前フレームのキー入力情報
		std::array<unsigned char, 256U> m_preKeys;
	};
}
#endif // !KEY_BOARD_UPDATER_H_