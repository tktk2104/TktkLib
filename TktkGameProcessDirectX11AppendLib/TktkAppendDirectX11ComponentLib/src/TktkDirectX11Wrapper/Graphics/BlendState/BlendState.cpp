#include "TktkDirectX11Wrapper/Graphics/BlendState/BlendState.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/BlendState/BlendStateManager.h"

namespace tktk
{
	void BlendState::createImpl(int id, const D3D11_BLEND_DESC & blendDesc)
	{
		if (id <= 0)
		{
			throw std::runtime_error("BlendStateId Fraud Value");
		}
		BlendStateManager::create(id, blendDesc);
	}

	void BlendState::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("BlendStateId Fraud Value");
		}
		BlendStateManager::erase(id);
	}

	BlendStateData * BlendState::getDataPtrImpl(int id)
	{
		return BlendStateManager::getDataPtr(id);
	}
}