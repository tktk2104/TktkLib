#include "TktkDX12Game/_MainManager/DX12GameManager.h"

#include <TktkDX12Wrapper/Graphics/Window/Window.h>
#include <TktkDX12Wrapper/Graphics/DX3D12/_DX3DBaseObjects/DX3DBaseObjects.h>

namespace tktk
{
	std::unique_ptr<Window>				DX12GameManager::m_window;
	std::unique_ptr<DX3DBaseObjects>	DX12GameManager::m_dx3dBaseObjects;

	void DX12GameManager::initialize(const DX3DBaseObjectsInitParam& dx3dInitParam, const WindowInitParam& windowInitParam, const std::string& tktkLibResFolderPath)
	{
		m_window = std::make_unique<Window>(windowInitParam);
		m_dx3dBaseObjects = std::make_unique<DX3DBaseObjects>(dx3dInitParam, m_window->getHWND(), windowInitParam.windowSize);
	}

	void DX12GameManager::run()
	{
		MSG msg{};

		while (true)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				switch (msg.message)
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

					m_dx3dBaseObjects->beginDraw();
					m_dx3dBaseObjects->endDraw();
					break;

				default:

					// èàóùÇ©Ç¡îÚÇŒÇµ
					break;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	void DX12GameManager::createIndexBuffer(unsigned int id, const std::vector<unsigned short>& indices)
	{
		m_dx3dBaseObjects->createIndexBuffer(id, indices);
	}

	void DX12GameManager::createVertexBufferImpl(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos)
	{
		m_dx3dBaseObjects->createVertexBuffer(id, vertexTypeSize, vertexDataCount, vertexDataTopPos);
	}

	void DX12GameManager::createConstantBufferImpl(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos)
	{
		m_dx3dBaseObjects->createConstantBuffer(id, constantBufferTypeSize, constantBufferDataTopPos);
	}
}