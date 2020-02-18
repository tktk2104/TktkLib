#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2D.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h"

namespace tktk
{
	void Texture2D::load(int id, const std::string & fileName)
	{
		if (id <= 0)
		{
			throw std::runtime_error("Texture2DId Fraud Value");
		}
		Texture2DManager::load(id, fileName);
	}

	void Texture2D::erase(int id)
	{
		if (id <= 0)
		{
			throw std::runtime_error("Texture2DId Fraud Value");
		}
		Texture2DManager::erase(id);
	}

	const Texture2DData & Texture2D::getData(int id)
	{
		return Texture2DManager::getData(id);
	}
}