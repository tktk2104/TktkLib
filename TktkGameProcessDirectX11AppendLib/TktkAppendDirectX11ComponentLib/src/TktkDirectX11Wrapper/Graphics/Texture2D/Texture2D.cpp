#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2D.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h"

namespace tktk
{
	void Texture2D::loadImpl(int id, const std::string & fileName)
	{
		if (id <= 0)
		{
			throw std::runtime_error("Texture2DId Fraud Value");
		}
		Texture2DManager::load(id, fileName);
	}

	void Texture2D::eraseImpl(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("Texture2DId Fraud Value");
		}
		Texture2DManager::erase(id);
	}

	const Texture2DData & Texture2D::getDataImpl(int id)
	{
		return Texture2DManager::getData(id);
	}
}