#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/DepthStencilState.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/DepthStencilStateManager.h"

namespace tktk
{
	void DepthStencilState::create(int id, const D3D11_DEPTH_STENCIL_DESC & depthStencilDesc)
	{
		if (id <= 0)
		{
			throw std::runtime_error("DepthStencilStateId Fraud Value");
		}
		DepthStencilStateManager::create(id, depthStencilDesc);
	}

	void DepthStencilState::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("DepthStencilStateId Fraud Value");
		}
		DepthStencilStateManager::erase(id);
	}

	DepthStencilStateData * DepthStencilState::getData(int id)
	{
		return DepthStencilStateManager::getData(id);
	}
}