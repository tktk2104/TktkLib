#include "TktkDirectX11Wrapper/Graphics/Window/WindowUpdater.h"

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
	WindowUpdater::WindowUpdater(
		HINSTANCE hInstance,
		int nCmdShow,
		const std::string & windowName,
		const Vector2 & windowSize
	)
		: m_windowSize(windowSize)
	{
		// �E�B���h�E�N���X�𐶐�
		WNDCLASS wc{};
		wc.lpfnWndProc = WndProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = windowName.c_str();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		RegisterClass(&wc);

		// �E�B���h�E�T�C�Y���v�Z
		RECT rect{ 0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// �E�B���h�E�𐶐�
		m_hwnd = CreateWindow(
			windowName.c_str(),
			windowName.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			hInstance,
			NULL
		);

		if (m_hwnd == NULL)
		{
			throw std::runtime_error("CreateWindow error");
		}

		// �E�B���h�E���J��
		ShowWindow(m_hwnd, nCmdShow);

		// ����X�V
		UpdateWindow(m_hwnd);
	}

	WindowUpdater::~WindowUpdater()
	{
	}

	HWND WindowUpdater::getHWND() const
	{
		return m_hwnd;
	}

	const Vector2 & WindowUpdater::getWindowSize() const
	{
		return m_windowSize;
	}
}