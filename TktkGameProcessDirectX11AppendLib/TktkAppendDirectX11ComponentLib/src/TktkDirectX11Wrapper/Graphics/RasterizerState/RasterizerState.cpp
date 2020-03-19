#include "TktkDirectX11Wrapper/Graphics/RasterizerState/RasterizerState.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/RasterizerState/RasterizerStateManager.h"

namespace tktk
{
	void RasterizerState::createImpl(int id, const D3D11_RASTERIZER_DESC & desc)
	{
		if (id <= 0)
		{
			throw std::runtime_error("RasterizerStateId Fraud Value");
		}
		RasterizerStateManager::create(id, desc);
	}

	void RasterizerState::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("RasterizerStateId Fraud Value");
		}
		RasterizerStateManager::erase(id);
	}

	const RasterizerStateData & RasterizerState::getDataImpl(int id)
	{
		return RasterizerStateManager::getData(id);
	}
}