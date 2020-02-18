#include "TktkDirectX11Wrapper/Graphics/ViewPort/ViewPortManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>

namespace tktk
{
	CfpPtr<ViewPortAssets> ViewPortManager::m_assetsPtr;

	void ViewPortManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::addClass(true, new ViewPortAssets());
	}

	void ViewPortManager::create(int id, const Vector2 & position, const Vector2 & size)
	{
		m_assetsPtr->create(id, position, size);
	}

	void ViewPortManager::erase(int id)
	{
		m_assetsPtr->erase(id);
	}

	void ViewPortManager::clear()
	{
		m_assetsPtr->clear();
	}

	const ViewPortData & ViewPortManager::getData(int id)
	{
		return m_assetsPtr->getData(id);
	}
}