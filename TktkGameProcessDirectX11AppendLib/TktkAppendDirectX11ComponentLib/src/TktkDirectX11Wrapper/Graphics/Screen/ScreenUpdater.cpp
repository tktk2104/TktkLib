#include "TktkDirectX11Wrapper/Graphics/Screen/ScreenUpdater.h"

#include <stdexcept>
#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <TktkComponentFramework/RunFuncType.h>
#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/DepthStencil/DepthStencil.h"
#include "TktkDirectX11Wrapper/Graphics/RenderTarget/RenderTarget.h"

namespace tktk
{
	ScreenUpdater::ScreenUpdater(bool fullScreen)
		: m_fullScreen(fullScreen)
	{
		// DirectX�f�o�C�X�ADirectX�R���e�L�X�g�A�X���b�v�`�F�[���̐���
		DXGI_SWAP_CHAIN_DESC scd{};
		scd.BufferCount = 1;
		scd.BufferDesc.Width = static_cast<int>(Window::getWindowSize().x);
		scd.BufferDesc.Height = static_cast<int>(Window::getWindowSize().y);
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = Window::getHWND();
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.Windowed = (!fullScreen);

		D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_11_0;

		D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			0,
			&fl,
			1,
			D3D11_SDK_VERSION,
			&scd,
			&m_swapChainPtr,
			&m_devicePtr,
			NULL,
			&m_deviceContextPtr
		);
	}

	ScreenUpdater::~ScreenUpdater()
	{
		if (m_deviceContextPtr != nullptr)
		{
			m_deviceContextPtr->Release();
		}
		if (m_devicePtr != nullptr)
		{
			m_devicePtr->Release();
		}
		if (m_swapChainPtr != nullptr)
		{
			m_swapChainPtr->Release();
		}
	}

	void ScreenUpdater::start()
	{
		const RenderTargetData & renderTargetData = RenderTarget::getData(SYSTEM_RENDER_TARGET_BACK_BUFFER);
		ID3D11RenderTargetView * backBuffer = renderTargetData.getViewPtr();
		const DepthStencilData & depthStencilData = DepthStencil::getData(SYSTEM_DEPTH_STENCIL_BASIC);
		m_deviceContextPtr->OMSetRenderTargets(1, &backBuffer, depthStencilData.getViewPtr());
	}

	void ScreenUpdater::frameBegin()
	{
		ComponentFrameworkProcessor::setIsRunFuncAll(true);

		if (m_msg.message == WM_QUIT)
		{
			ComponentFrameworkProcessor::exitGame();
			ComponentFrameworkProcessor::setIsRunFuncAll(false);
			ComponentFrameworkProcessor::setIsRunFunc<RUN_FUNC_frameBegin>(true);
			ComponentFrameworkProcessor::setIsRunFunc<RUN_FUNC_isDestroy>(true);
		}
		else if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			switch (m_msg.message)
			{
			case WM_MOUSEMOVE:
			case WM_NCMOUSEMOVE:

				break;

			default:

				ComponentFrameworkProcessor::setIsRunFuncAll(false);
				ComponentFrameworkProcessor::setIsRunFunc<RUN_FUNC_frameBegin>(true);
				break;
			}

			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
	}

	void ScreenUpdater::draw()
	{
		// �o�b�N�o�b�t�@���N���A
		float clearColor[4] = { m_backGroundColor.r, m_backGroundColor.g, m_backGroundColor.b, m_backGroundColor.a };
		const RenderTargetData & renderTargetData = RenderTarget::getData(SYSTEM_RENDER_TARGET_BACK_BUFFER);
		m_deviceContextPtr->ClearRenderTargetView(renderTargetData.getViewPtr(), clearColor);

		// �f�v�X�o�b�t�@���N���A
		const DepthStencilData& depthStencilData = DepthStencil::getData(SYSTEM_DEPTH_STENCIL_BASIC);
		m_deviceContextPtr->ClearDepthStencilView(depthStencilData.getViewPtr(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void ScreenUpdater::frameEnd()
	{
		// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@������
		m_swapChainPtr->Present(1, 0);
	}

	float ScreenUpdater::getDrawPriority()
	{
		return -10000.0f;
	}

	IDXGISwapChain * ScreenUpdater::getSwapChainPtr() const
	{
		return m_swapChainPtr;
	}

	ID3D11Device * ScreenUpdater::getDevicePtr() const
	{
		return m_devicePtr;
	}

	ID3D11DeviceContext * ScreenUpdater::getDeviceContextPtr() const
	{
		return m_deviceContextPtr;
	}

	void ScreenUpdater::setBackgroundColor(const Color & color)
	{
		m_backGroundColor = color;
	}
}