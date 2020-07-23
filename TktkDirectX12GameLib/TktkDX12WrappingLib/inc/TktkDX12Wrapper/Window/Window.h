#ifndef WINDOW_H_
#define WINDOW_H_

#include <Windows.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>
#include "WindowInitParam.h"

namespace tktk
{
	// �Q�[���̃E�B���h�E���Ǘ�����N���X
	class Window
	{
	public:

		explicit Window(const WindowInitParam& initParam);
		~Window() = default;

		// �R�s�[�֎~
		Window(const Window& other) = delete;
		Window& operator = (const Window& other) = delete;

	public:

		// �E�B���h�E�n���h�����擾����
		HWND getHWND() const;

		// �E�B���h�E�T�C�Y���擾����
		const tktkMath::Vector2& getWindowSize() const;

	private:

		// �E�B���h�E�n���h��
		HWND m_hwnd{ nullptr };

		// �E�B���h�E�T�C�Y
		tktkMath::Vector2 m_windowSize{ };
	};
}
#endif // !WINDOW_H_