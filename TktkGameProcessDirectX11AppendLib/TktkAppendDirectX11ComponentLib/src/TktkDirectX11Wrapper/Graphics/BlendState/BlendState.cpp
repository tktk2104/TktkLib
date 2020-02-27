#include "TktkDirectX11Wrapper/Graphics/BlendState/BlendState.h"

#include "TktkDirectX11Wrapper/Graphics/BlendState/BlendStateManager.h"

namespace tktk
{
	void BlendState::create(int id, const D3D11_BLEND_DESC & blendDesc)
	{
		BlendStateManager::create(id, blendDesc);
	}

	void BlendState::erase(int id)
	{
		BlendStateManager::erase(id);
	}

	BlendStateData * BlendState::getDataPtr(int id)
	{
		return BlendStateManager::getDataPtr(id);
	}
}