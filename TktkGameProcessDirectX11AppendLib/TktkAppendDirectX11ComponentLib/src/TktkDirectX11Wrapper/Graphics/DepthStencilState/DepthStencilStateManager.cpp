#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/DepthStencilStateManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<DepthStencilStateAssets> DepthStencilStateManager::m_assetsPtr;

	void DepthStencilStateManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::createClass<DepthStencilStateAssets>(true);

		{
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
			depthStencilDesc.DepthEnable = true;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.StencilEnable = false;

			create(SystemDepthStencilStateId::Basic, depthStencilDesc);
		}

		{
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
			depthStencilDesc.DepthEnable = false;
			depthStencilDesc.StencilEnable = false;

			create(SystemDepthStencilStateId::NotUseDepth, depthStencilDesc);
		}
	}

	void DepthStencilStateManager::clear()
	{
		m_assetsPtr->clear();
	}

	void DepthStencilStateManager::createImpl(int id, const D3D11_DEPTH_STENCIL_DESC & depthStencilDesc)
	{
		m_assetsPtr->create(id, depthStencilDesc);
	}

	void DepthStencilStateManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	DepthStencilStateData * DepthStencilStateManager::getDataPtrImpl(int id)
	{
		return m_assetsPtr->getDataPtr(id);
	}
}