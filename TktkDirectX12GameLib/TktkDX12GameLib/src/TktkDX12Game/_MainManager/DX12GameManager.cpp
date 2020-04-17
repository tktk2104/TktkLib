#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	DX12GameManager::DX12GameManager(
		const DX3DBaseObjectsInitParam& dx3dInitParam,
		const WindowInitParam& windowInitParam,
		const std::string& tktkLibResFolderPath
	)
		: m_window(windowInitParam)
		, m_dx3dBaseObjects(dx3dInitParam, m_window.getHWND(), windowInitParam.windowSize)
	{
	}

	void DX12GameManager::run()
	{
		MSG m_msg{};

		while (true)
		{
			if (m_msg.message == WM_QUIT)
			{
				break;
			}
			else if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
			{
				switch (m_msg.message)
				{
				case WM_MOUSEMOVE:
				case WM_LBUTTONDOWN:
				case WM_LBUTTONUP:
				case WM_LBUTTONDBLCLK:
				case WM_RBUTTONDOWN:
				case WM_RBUTTONUP:
				case WM_RBUTTONDBLCLK:
				case WM_MBUTTONDOWN:
				case WM_MBUTTONUP:
				case WM_MBUTTONDBLCLK:
				case WM_XBUTTONDOWN:
				case WM_XBUTTONUP:
				case WM_XBUTTONDBLCLK:
				case WM_MOUSEWHEEL:
				case WM_MOUSEHWHEEL:
				case WM_NCMOUSEMOVE:
				case WM_NCLBUTTONDOWN:
				case WM_NCLBUTTONUP:
				case WM_NCLBUTTONDBLCLK:
				case WM_NCRBUTTONDOWN:
				case WM_NCRBUTTONUP:
				case WM_NCRBUTTONDBLCLK:
				case WM_NCMBUTTONDOWN:
				case WM_NCMBUTTONUP:
				case WM_NCMBUTTONDBLCLK:
				case WM_NCXBUTTONDOWN:
				case WM_NCXBUTTONUP:
				case WM_NCXBUTTONDBLCLK:
				case WM_KEYFIRST:
				case WM_KEYUP:
				case WM_CHAR:
				case WM_DEADCHAR:
				case WM_SYSKEYDOWN:
				case WM_SYSKEYUP:
				case WM_SYSCHAR:
				case WM_SYSDEADCHAR:
				case WM_UNICHAR:

					m_dx3dBaseObjects.beginDraw();
					m_dx3dBaseObjects.endDraw();
					break;

				default:

					// èàóùÇ©Ç¡îÚÇŒÇµ
					break;
				}

				TranslateMessage(&m_msg);
				DispatchMessage(&m_msg);
			}
		}
	}
}