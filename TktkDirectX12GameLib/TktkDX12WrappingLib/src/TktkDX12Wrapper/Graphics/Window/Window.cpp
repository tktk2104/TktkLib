#include "TktkDX12Wrapper/Graphics/Window/Window.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

namespace tktk
{
	Window::Window(const WindowInitParam& initParam)
		: m_windowSize(initParam.windowSize)
	{
		// �E�B���h�E�N���X�𐶐�
		WNDCLASS wc{};
		wc.lpfnWndProc = WndProc;
		wc.hInstance = initParam.hInstance;
		wc.lpszClassName = initParam.windowName.c_str();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		RegisterClass(&wc);

		// �E�B���h�E�T�C�Y���v�Z
		RECT rect{ 0, 0, static_cast<int>(initParam.windowSize.x), static_cast<int>(initParam.windowSize.y) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// �E�B���h�E�𐶐�
		m_hwnd = CreateWindow(
			initParam.windowName.c_str(),
			initParam.windowName.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			initParam.hInstance,
			NULL
		);

		if (m_hwnd == NULL)
		{
			throw std::runtime_error("CreateWindow error");
		}

		// �E�B���h�E���J��
		ShowWindow(m_hwnd, initParam.nCmdShow);

		// ����X�V
		UpdateWindow(m_hwnd);
	}

	HWND Window::getHWND() const
	{
		return m_hwnd;
	}

	const tktkMath::Vector2& Window::getWindowSize() const
	{
		return m_windowSize;
	}
}