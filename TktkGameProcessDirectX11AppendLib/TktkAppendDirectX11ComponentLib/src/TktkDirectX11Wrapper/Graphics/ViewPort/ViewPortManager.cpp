#include "TktkDirectX11Wrapper/Graphics/ViewPort/ViewPortManager.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include "TktkDirectX11Wrapper/Graphics/Window/Window.h"
#include "TktkDirectX11Wrapper/Graphics/Screen/Screen.h"

namespace tktk
{
	CfpPtr<ViewPortAssets> ViewPortManager::m_assetsPtr;

	void ViewPortManager::setUp()
	{
		m_assetsPtr = ComponentFrameworkProcessor::createClass<ViewPortAssets>(true);
		create(SystemViewPortId::Default, Vector2::zero, Window::getWindowSize());
	}

	void ViewPortManager::clear()
	{
		m_assetsPtr->clear();
	}

	void ViewPortManager::createImpl(int id, const Vector2 & position, const Vector2 & size)
	{
		m_assetsPtr->create(id, position, size);
	}

	void ViewPortManager::eraseImpl(int id)
	{
		m_assetsPtr->erase(id);
	}

	const ViewPortData & ViewPortManager::getDataImpl(int id)
	{
		return m_assetsPtr->getData(id);
	}
}