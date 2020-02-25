#ifndef WINDOW_UPDATER_H_
#define WINDOW_UPDATER_H_

#include <string>
#include <TktkMath/Vector2.h>
#include "../../Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	// �E�B���h�E�̕\�����s���N���X
	class WindowUpdater
	{
	public:

		WindowUpdater(
			HINSTANCE hInstance,
			int nCmdShow,
			const std::string& windowName,
			const Vector2& windowSize
		);
		~WindowUpdater();

		WindowUpdater(const WindowUpdater& other) = delete;
		WindowUpdater& operator = (const WindowUpdater& other) = delete;

	public:

		// �E�B���h�E�n���h�����擾����
		HWND getHWND() const;

		// �E�B���h�E�T�C�Y���擾����
		const Vector2& getWindowSize() const;

	private:

		// �E�B���h�E�n���h��
		HWND m_hwnd;

		// �E�B���h�E�T�C�Y
		Vector2 m_windowSize;
	};
}
#endif // !WINDOW_UPDATER_H_