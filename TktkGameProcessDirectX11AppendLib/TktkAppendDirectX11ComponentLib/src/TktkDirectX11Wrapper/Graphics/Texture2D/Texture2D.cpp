#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2D.h"

#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Texture2D/Texture2DManager.h"

namespace tktk
{
	void Texture2D::createImpl(int id, Texture2DBindFlag bindFlag, const std::vector<unsigned char>& textureData, unsigned int width, unsigned int height, unsigned int mipCount, unsigned int arraySize, DXGI_FORMAT format, Texture2DUsage usage, Texture2DCpuAccessFlag cpuAccessFlag, bool isCubeMap)
	{
		if (id <= 0)
		{
			throw std::runtime_error("Texture2DId Fraud Value");
		}
		Texture2DManager::create(id, bindFlag, textureData, width, height, mipCount, arraySize, format, usage, cpuAccessFlag, isCubeMap);
	}

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