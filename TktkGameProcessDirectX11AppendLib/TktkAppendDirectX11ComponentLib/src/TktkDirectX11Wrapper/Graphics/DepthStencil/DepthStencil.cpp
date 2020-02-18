#include "TktkDirectX11Wrapper/Graphics/DepthStencil/DepthStencil.h"

#include "TktkDirectX11Wrapper/Graphics/DepthStencil/DepthStencilManager.h"

namespace tktk
{
	void DepthStencil::create(int id, const Vector2 & useTextureSize)
	{
		if (id <= 0)
		{
			throw std::runtime_error("DepthStencilId Fraud Value");
		}
		DepthStencilManager::create(id, useTextureSize);
	}

	void DepthStencil::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("DepthStencilId Fraud Value");
		}
		DepthStencilManager::erase(id);
	}

	const DepthStencilData & DepthStencil::getData(int id)
	{
		return DepthStencilManager::getData(id);
	}
}