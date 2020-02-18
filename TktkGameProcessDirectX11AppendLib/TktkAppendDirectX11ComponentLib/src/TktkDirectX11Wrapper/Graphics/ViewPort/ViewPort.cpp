#include "TktkDirectX11Wrapper/Graphics/ViewPort/ViewPort.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/ViewPort/ViewPortManager.h"

namespace tktk
{
	void ViewPort::create(int id, const Vector2 & position, const Vector2 & size)
	{
		if (id <= 0)
		{
			throw std::runtime_error("ViewPortId Fraud Value");
		}
		ViewPortManager::create(id, position, size);
	}

	void ViewPort::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("ViewPortId Fraud Value");
		}
		ViewPortManager::erase(id);
	}

	const ViewPortData & ViewPort::getData(int id)
	{
		return ViewPortManager::getData(id);
	}
}