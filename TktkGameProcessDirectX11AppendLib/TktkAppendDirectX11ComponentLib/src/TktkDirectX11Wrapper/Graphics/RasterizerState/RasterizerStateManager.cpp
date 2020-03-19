#include "TktkDirectX11Wrapper/Graphics/RasterizerState/RasterizerStateManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<RasterizerStateAssets> RasterizerStateManager::m_assetsPtr;

	void RasterizerStateManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::createClass<RasterizerStateAssets>(true);
		
		{
			D3D11_RASTERIZER_DESC desc{};
			desc.FillMode = D3D11_FILL_SOLID;
			desc.CullMode = D3D11_CULL_BACK;
			desc.FrontCounterClockwise = FALSE;	// TODO : FALSE‚Å—Ç‚¢‚Ì‚©Šm”F‚·‚é

			create(SystemRasterizerStateId::Basic, desc);
		}

		{
			D3D11_RASTERIZER_DESC desc{};
			desc.FillMode = D3D11_FILL_WIREFRAME;
			desc.CullMode = D3D11_CULL_NONE;
			desc.FrontCounterClockwise = TRUE;

			create(SystemRasterizerStateId::WireFrame, desc);
		}
	}

	void RasterizerStateManager::clear()
	{
		m_assetsPtr->clear();
	}

	void RasterizerStateManager::createImpl(int id, const D3D11_RASTERIZER_DESC & desc)
	{
		m_assetsPtr->create(id, desc);
	}

	void RasterizerStateManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	const RasterizerStateData & RasterizerStateManager::getDataImpl(int id)
	{
		return m_assetsPtr->getData(id);
	}
}