#include "TktkDirectX11Wrapper/Graphics/DepthStencilView/DepthStencilView.h"

#include "TktkDirectX11Wrapper/Graphics/DepthStencilView/DepthStencilViewManager.h"

namespace tktk
{
	void DepthStencilView::create(int id, const Vector2 & useTextureSize)
	{
		if (id <= 0)
		{
			throw std::runtime_error("DepthStencilViewId Fraud Value");
		}
		DepthStencilViewManager::create(id, useTextureSize);
	}

	void DepthStencilView::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("DepthStencilViewId Fraud Value");
		}
		DepthStencilViewManager::erase(id);
	}

	const DepthStencilViewData & DepthStencilView::getData(int id)
	{
		return DepthStencilViewManager::getData(id);
	}
}