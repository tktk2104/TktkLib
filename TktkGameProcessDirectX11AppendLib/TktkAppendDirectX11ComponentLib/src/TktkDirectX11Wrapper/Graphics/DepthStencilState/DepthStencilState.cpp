#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/DepthStencilState.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/DepthStencilState/DepthStencilStateManager.h"

namespace tktk
{
	void DepthStencilState::createImpl(int id, const D3D11_DEPTH_STENCIL_DESC & depthStencilDesc)
	{
		if (id <= 0)
		{
			throw std::runtime_error("DepthStencilStateId Fraud Value");
		}
		DepthStencilStateManager::create(id, depthStencilDesc);
	}

	void DepthStencilState::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("DepthStencilStateId Fraud Value");
		}
		DepthStencilStateManager::erase(id);
	}

	DepthStencilStateData * DepthStencilState::getDataPtrImpl(int id)
	{
		return DepthStencilStateManager::getDataPtr(id);
	}
}